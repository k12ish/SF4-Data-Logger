import { writable } from 'svelte/store';
import { encode, decodeMultiStream } from '@msgpack/msgpack';

import Joi from 'joi';

// check that packet is of length 4, containing 10 bit ints
const PACKET_VALIDATOR = Joi.array().length(4).items(
  Joi.number().integer().min(0).max(2 ** 10 - 1)
);

export class ArduinoInterface {
  private writeStream = new WritableStream();
  private readDecoded = decodeMultiStream(new ReadableStream());

  public async updateStreams(
    read: ReadableStream<Uint8Array>,
    write: WritableStream<Uint8Array>,
  ) {
    this.readDecoded.return();
    this.readDecoded = decodeMultiStream(read);
    this.writeStream = write;

    while (true) {
      // JS issue: we have to request the nextSymbol BEFORE we write bytes
      // otherwise we loose the first response packet!!
      let nextSymbol = this.readDecoded.next();
      await this.write("hello");
      let result = PACKET_VALIDATOR.validate((await nextSymbol).value);
      if (!result.error) { break }
    }

    for await (const item of this.readDecoded) {
      console.log(
        PACKET_VALIDATOR.validate(item)
      )
    }
    console.log('No More Waiting.')
  }

  public async write(val: any) {
    let buffer = encode(val, { sortKeys: true });
    let writer = this.writeStream.getWriter();
    return writer.ready.then(
      () => writer.write(buffer)
    ).then(() => writer.releaseLock())
  }
}
