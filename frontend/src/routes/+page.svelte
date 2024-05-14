<script>
	import Navbar from './../components/Navbar.svelte';
	import { landingPage } from '../lib/stores.js'
	landingPage.subscribe(
		(val) => console.log(val)
	)

	async () => {
		console.log("serial" in navigator)
		// const port = await navigator.serial.requestPort();
		// const port = await navigator.serial.requestPort();
		// const notSupported = document.getElementById('notSupported');
	};
</script>

<Navbar />
