import { writable } from 'svelte/store';
import { encode, decodeMultiStream } from '@msgpack/msgpack';

import Joi from 'joi';

// check that packet is of length 4, containing 10 bit ints
const PACKET_VALIDATOR = Joi.array().length(4).items(
  Joi.number().integer().min(0).max(2 ** 10 - 1)
);

export class ArduinoInterface {
  private writeStream: WritableStream;
  // private readDecoded = decodeMultiStream(new ReadableStream());
  private readDecoded: AsyncGenerator;

  constructor(
    read: ReadableStream<Uint8Array>,
    write: WritableStream<Uint8Array>,
  ) {
    this.readDecoded = decodeMultiStream(read);
    this.writeStream = write;
  }

  public async run() {
    while (true) {
      // HACK: omfg these lines have caused me so much pain
      // for some reason, `readDecoded` likes to take it's time?
      let nextSymbol = this.readDecoded.next();
      console.log("next() called")
      await new Promise(resolve => setTimeout(resolve, 3000));
      await this.write("i");
      console.log("write() called")

      let result = PACKET_VALIDATOR.validate((await nextSymbol).value);
      console.log("Yay, the code worked!")
      if (!result.error) { break }
    }

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
