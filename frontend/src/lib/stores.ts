import { writable } from 'svelte/store';
import { encode, decodeMultiStream } from '@msgpack/msgpack';

import Joi from 'joi';

// check that packet is of length 4, containing 10 bit ints
const PACKET_VALIDATOR = Joi.array().length(4).items(
  Joi.number().integer().min(0).max(2 ** 10 - 1)
);

// Taken from https://advancedweb.hu/how-to-add-timeout-to-a-promise-in-javascript/
const timeout = (prom: Promise<IteratorResult<unknown, any>>, time: number, exception: any): Promise<any> => {
	let timer;
	return Promise.race([
		prom,
		new Promise((_r, rej) => timer = setTimeout(rej, time, exception))
	]).finally(() => clearTimeout(timer));
}

type setModeProgress = 'timeout' | 'invalid-response' | 'done';
type SetModeCallback = (progress: setModeProgress) => void;


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

  public async setMode(callback: SetModeCallback) {
    const timeoutError = Symbol();
    let nextMessage = this.readDecoded.next();
    let message;

    while (true) {
      await this.write("i");
      try {
        message = await timeout(nextMessage, 1000, timeoutError);
      } catch (e) {
        e === timeoutError ? callback('timeout') : console.log(e);
        continue
      }
      let result = PACKET_VALIDATOR.validate(message.value);
      if (result.error) {
        console.log("error:", result)
        nextMessage = this.readDecoded.next()
      } else {
        break;
      }
    }
  }

  public async run() {
    await this.setMode(console.log);
    for await (const item of this.readDecoded) {
      console.log(
        PACKET_VALIDATOR.validate(item)
      )
    }
  }

  private async write(val: any) {
    let buffer = encode(val, { sortKeys: true });
    let writer = this.writeStream.getWriter();
    return writer.ready.then(
      () => writer.write(buffer)
    ).then(() => writer.releaseLock())
  }
}
