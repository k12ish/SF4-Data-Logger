<script>
	import Navbar from './../components/Navbar.svelte';
	import Landing from './../components/Landing.svelte';
	import { landingPage } from '../lib/stores.js';

	landingPage.subscribe(async (val) => {
		if (!val) {
			// user clicked "get started"
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
			}
		}
	});

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

<Navbar />

<div class="container mx-auto" class:hidden={!$landingPage}>
	<Landing />
</div>
