import { writable } from 'svelte/store';
import { encode, decodeMultiStream } from '@msgpack/msgpack';

import Joi from 'joi';


export type arduinoModes = 'Regular' | 'Augmented';
// check that packet is of length 4, containing 10 bit ints
const PACKET_VALIDATOR = Joi.array().length(4).items(
  Joi.number().integer().min(0)
);

// Taken from https://advancedweb.hu/how-to-add-timeout-to-a-promise-in-javascript/
const timeout = (prom: Promise<IteratorResult<unknown, any>>, time: number, exception: any): Promise<any> => {
  let timer;
  return Promise.race([
    prom,
    new Promise((_r, rej) => timer = setTimeout(rej, time, exception))
  ]).finally(() => clearTimeout(timer));
}

export type setModeProgress = 'timeout' | 'invalid-response' | 'ioerror';
export type SetModeCallback = (progress: setModeProgress) => void;


export class ArduinoInterface {
  private writeStream: WritableStream;
  private readDecoded: AsyncGenerator;

  constructor(
    read: ReadableStream<Uint8Array>,
    write: WritableStream<Uint8Array>,
  ) {
    this.readDecoded = decodeMultiStream(read);
    this.writeStream = write;
  }

  public async setMode(mode: arduinoModes, callback: SetModeCallback) {
    const timeoutError = Symbol();
    let nextMessage = this.readDecoded.next();
    let message;

    for (let i = 0; i < 10; i++) {
      await this.write(mode);
      try {
        message = await timeout(nextMessage, 1000, timeoutError);
      } catch (e) {
        console.log(e)
        if (e == timeoutError) {
          callback('timeout')
        } else {
          callback('ioerror');
        }
        continue
      }
      let result = PACKET_VALIDATOR.validate(message.value);
      if (result.error) {
        callback('invalid-response');
        console.log("invalid:", message.value)
        nextMessage = this.readDecoded.next()
      } else {
        break;
      }
    }
  }

  public async run() {
    for await (const item of this.readDecoded) {
      console.log(
        PACKET_VALIDATOR.validate(item)
      )
    }
  }

  private async write(val: string) {
    console.log("Writing", JSON.stringify(val))
    let buffer = new TextEncoder().encode(val);
    let writer = this.writeStream.getWriter();
    return writer.ready.then(
      () => writer.write(buffer)
    ).then(() => writer.releaseLock())
  }
}
