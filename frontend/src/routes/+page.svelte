<script>
	import Navbar from './../components/Navbar.svelte';
	import Landing from './../components/Landing.svelte';
	import { landingPage } from '../lib/stores.js';

	landingPage.subscribe(async (val) => {
		if (!val) {
			// user clicked "get started"
			if (!('serial' in navigator)) {
				alert('Use a browser that supports WebSerial!');
			}
			try {
			  // limit the set of selectable ports to only USB devices with Arduino's USB vendor ID
				const filter = { usbVendorId: 0x2A03 }; 
				const port = await navigator.serial.requestPort({ filters: [filter] });
				// Continue connecting to the device attached to |port|.
			} catch (e) {
				// The prompt has been dismissed without selecting a device.
			}
		}
	});

	async () => {
		//
		// const port = await navigator.serial.requestPort();
		// const notSupported = document.getElementById('notSupported');
	};
</script>

<Navbar />

<div class="container mx-auto" class:hidden={!$landingPage}>
	<Landing />
</div>
