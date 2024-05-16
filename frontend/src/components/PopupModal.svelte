<script>
	import { Button, Modal } from 'flowbite-svelte';
	import { fade } from 'svelte/transition';
	import ArduinoConnect from 'lib/arduino-connect.png';
	import ArduinoUno from 'lib/ArduinoUno.svg.png';

	let popupStage = 'hidden';

	export function launch() {
		popupStage = 'visible-first';
	}

	async function onClick() {
		// TODO: better visible-second stage
		popupStage = 'visible-second';
		let port = await getArduinoPort();
		popupStage = 'hidden';
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
			// data = data + '\n' + value.join();
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
</script>

{#if popupStage != 'hidden'}
	<div transition:fade>
		<Modal title="Connect your Arduino!" open={popupStage != 'hidden'} dismissable={false}>
			<div class="flex w-full justify-center">
				<img src={ArduinoUno} alt="Arduino Connecting over USB to Laptop" />
			</div>
			<svelte:fragment slot="footer">
				<div class="flex w-full justify-center">
					<Button on:click={() => onClick()}>Done!</Button>
				</div>
			</svelte:fragment>
		</Modal>
	</div>
{/if}
