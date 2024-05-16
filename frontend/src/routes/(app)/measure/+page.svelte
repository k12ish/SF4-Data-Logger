<script>
	import { Button, Modal } from 'flowbite-svelte';
	import { onMount } from 'svelte';
	let defaultModal = false;
	let data = '';

	async function onClick() {
		defaultModal = false;
		let port = await getArduinoPort();
		console.log(port);
		await port.open({ baudRate: 115_200 });
		const reader = port.readable.getReader();

		// Listen to data coming from the serial device.
		while (true) {
			const { value, done } = await reader.read();
			if (done) {
				// Allow the serial port to be closed later.
				reader.releaseLock();
				break;
			}
			// value is a Uint8Array.
			console.log(value);
			data = data + '\n' + value.join();
		}
	}

	async function getArduinoPort() {
		// if (!('serial' in navigator)) {
		// 	alert('Use a browser that supports WebSerial!');
		// }
		try {
			// limit selectable ports to only USB devices with Arduino's USB vendor ID
			const filter = { usbVendorId: 0x2a03 };
			const port = await navigator.serial.requestPort({ filters: [filter] });
			// Continue connecting to the device attached to |port|.
			return port;
		} catch (e) {
			// The prompt has been dismissed without selecting a device.
			return null;
		}
	}
	onMount(() => setTimeout(() => (defaultModal = true), 200));
</script>

<Modal title="Connect your Arduino!" bind:open={defaultModal} dismissable={false}>
	<div class="flex w-full justify-center">
		<img src="/arduino-connect.png" alt="Arduino Connecting over USB to Laptop" />
	</div>
	<svelte:fragment slot="footer">
		<div class="flex w-full justify-center">
			<Button on:click={() => onClick()}>Done!</Button>
		</div>
	</svelte:fragment>
</Modal>

<div class="relative mx-auto mt-24 max-w-2xl">
	<div class="rounded-md bg-gray-900 p-4 text-white">
		<div class="overflow-x-auto">
			<pre id="code" class="text-gray-300">{data}</pre>
		</div>
	</div>
</div>
