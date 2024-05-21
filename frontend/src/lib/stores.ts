import { writable } from 'svelte/store';
import { encode, decodeMultiStream } from '@msgpack/msgpack';


export class ArduinoInterface {
  private readDecoded: AsyncGenerator<any>;

  public constructor(
    readStream: ReadableStream<Uint8Array>,
    private writeStream: WritableStream<Uint8Array>,
  ) {
    this.readDecoded = decodeMultiStream(readStream);
  }

  public async readToCompletion() {
    for await (const item of this.readDecoded) {
      this.write(item);
    }
  }

  public setSerial(
    read: ReadableStream<Uint8Array>,
    write: WritableStream<Uint8Array>,
  ) {
    this.readDecoded.return("complete");
    this.readDecoded = decodeMultiStream(read);
    this.writeStream = write;
  }

  public write(val: any) {
    let buffer = encode(val, { sortKeys: true });
    let writer = this.writeStream.getWriter();
    writer.ready.then(
      () => writer.write(buffer)
    ).then(() => writer.releaseLock())
  }

}
