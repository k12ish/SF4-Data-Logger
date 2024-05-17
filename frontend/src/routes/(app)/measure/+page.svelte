<script>
	import { onMount } from 'svelte';
	import PopupModal from 'components/PopupModal.svelte';
	let data = '';

	let popupModalComponent;
	let port;

	// async function readPort() {
	// 	console.log(port);
	// 	await port.open({ baudRate: 115_200 });
	// 	const reader = port.readable.getReader();

	// 	// Listen to data coming from the serial device.
	// 	while (true) {
	// 		const { value, done } = await reader.read();
	// 		if (done) {
	// 			// Allow the serial port to be closed later.
	// 			reader.releaseLock();
	// 			break;
	// 		}
	// 		// value is a Uint8Array.
	// 		console.log(value);
	// 		// data = data + '\n' + value.join();
	// }
	
	onMount(() => setTimeout(() => (port = popupModalComponent.launch()), 400));

</script>

<div class="relative mx-auto mt-24 max-w-2xl">
	<div class="rounded-md bg-gray-900 p-4 text-white">
		<div class="overflow-x-auto">
			<pre id="code" class="text-gray-300">{data}</pre>
		</div>
	</div>
</div>

<PopupModal bind:this={popupModalComponent} />
