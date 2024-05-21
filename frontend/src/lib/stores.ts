import { writable } from 'svelte/store';
import { encode, decodeMultiStream } from '@msgpack/msgpack';


export class ArduinoInterface {
  public constructor(
    private reader: ReadableStream<Uint8Array>,
    private writer: WritableStream<Uint8Array>,
  ) { }

  public setSerial(
    reader: ReadableStream<Uint8Array>,
    writer: WritableStream<Uint8Array>,
  ) {
    // reader = reader;
    reader.getReader()
    writer = writer;
  }

  public async readToCompletion() {
    for await (const item of decodeMultiStream(this.reader)) {
      console.log(item)
    }
  }
  public async write(value: any) {
    const buffer = encode(value);
    this.writer.getWriter().write(buffer);
  }

}

// const emptyStream = new ReadableStream({
//   start(controller) {
//     controller.close();
//   },
// });

// let ard = new ArduinoInterface(new ReadableStream(), new WritableStream());


function CreateSerialPortWrapper() {
  const { set, update, subscribe } = writable(null);

  async function readToCompletion(stream: ReadableStream<Uint8Array>) {
    for await (const item of decodeMultiStream(stream)) {
      update(() => item)
    }
  }

  return {
    subscribe,
  }
}



// type PizzaStore = {
//   ingredients: string[];
//   ovenTime: number;
//   status: 'idle' | 'preparing' | 'baking' | 'ready';
// };

// function createPizzaStore() {
//   const { set, update, subscribe } = writable<PizzaStore>({
//     ingredients: [],
//     ovenTime: 0,
//     status: "idle"
//   });

//   function addIngredient(ingredient: string) {
//     if (ingredient === 'pineapple') {
//       throw new Error('Step away from the pizza');
//     }

//     update((store) => ({
//       ...store,
//       ingredients: [...store.ingredients, ingredient],
//     }));
//   }

//   return {
//     subscribe,
//     addIngredient,
//   };
// }

// const pizzaStore = createPizzaStore();

// export default pizzaStore;

export async function* asyncIterableFromStream<T>(stream: ReadableStream<T>): AsyncIterable<T> {
  const reader = stream.getReader();

  try {
    while (true) {
      const { done, value } = await reader.read();
      if (done) {
        return;
      }
      yield value;
    }
  } finally {
    reader.releaseLock();
  }
}
