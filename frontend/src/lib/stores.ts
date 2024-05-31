import { decodeMultiStream } from '@msgpack/msgpack';

import Joi from 'joi';


export type arduinoModes = 'IDLE' | 'LALL' | 'RALL' | 'LARA';

// check that packet is of length 2, containing 10 bit ints
const DATA_VALIDATOR = Joi.array().length(2).items(
  Joi.number().integer()
);

// Taken from https://advancedweb.hu/how-to-add-timeout-to-a-promise-in-javascript/
const timeout = (prom: Promise<IteratorResult<unknown, any>>, time: number, exception: any): Promise<any> => {
  let timer: any;
  return Promise.race([
    prom,
    new Promise((_r, rej) => timer = setTimeout(rej, time, exception))
  ]).finally(() => clearTimeout(timer));

}


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

  public async setMode(mode: arduinoModes,
    callback: (progress: 'timeout' | 'invalid-response' | 'ioerror') => void) {
    const timeoutError = Symbol();
    let nextMessage = this.readDecoded.next();
    let message;

    for (let i = 0; i < 1_000; i++) {
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
      if (message.value !== mode) {
        callback('invalid-response');
        console.log("invalid:", message.value)
        nextMessage = this.readDecoded.next()
      } else {
        break;
      }
    }
  }

  /**
  * Reads items for a minimum number of milliseconds.
  */
  public async batchRead(millis: number): Promise<Array<any>> {
    // read repeatedly from this.readDecoded for `millis` number of ms
    let items: Array<any> = [];
    const endTime = Date.now() + millis;

    while (Date.now() < endTime) {
      const message = await this.readDecoded.next();
      if (message.done) { break; }
      const parse = DATA_VALIDATOR.validate(message.value)
      if (!parse.error) { items.push(parse.value) }
    }
    return items
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
