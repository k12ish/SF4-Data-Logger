import { writable } from 'svelte/store';
import { encode, decodeMultiStream } from '@msgpack/msgpack';


export class ArduinoInterface {
  private writeStream = new WritableStream();
  private readDecoded = decodeMultiStream(new ReadableStream());

  public async readStream() {
    console.log('Waiting..')
    for await (const item of this.readDecoded) {
      console.log('cout', item)
    }
    console.log('No More Waiting.')
  }

  public async updateStreams(
    read: ReadableStream<Uint8Array>,
    write: WritableStream<Uint8Array>,
  ) {
    this.readDecoded.return();
    this.readDecoded = decodeMultiStream(read);
    this.writeStream = write;
    
    console.log("writing `hello`")
    await this.write("hello");
    console.log("fin `hello`")

    console.log("next")
    console.log(await this.readDecoded.next())
    console.log(await this.readDecoded.next())
    console.log("fin `next`")

  }

  public async write(val: any) {
    let buffer = encode(val, { sortKeys: true });
    let writer = this.writeStream.getWriter();
    return writer.ready.then(
      () => writer.write(buffer)
    ).then(() => writer.releaseLock())
  }
}
