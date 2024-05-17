<script lang="ts">
	import { onMount } from 'svelte';
	import PopupModal from 'components/PopupModal.svelte';
	let data = '';

	let popupModalComponent;
	// onMount(() => setTimeout(() => (port = popupModalComponent.launch()), 400));

	import { LayerCake, Svg } from 'layercake';
	import Line from 'components/EKG/Line.svelte';
	import AxisX from 'components/EKG/AxisX.svelte';
	import AxisY from 'components/EKG/AxisY.svelte';

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

	// Define some data
	let points = [
		{ x: 0, y: 0 },
		{ x: 5, y: 10 },
		{ x: 10, y: 20 },
		{ x: 15, y: 30 },
		{ x: 20, y: 40 }
	];

	let idx = 0;
	function getRandomInt(min: number, max: number): number {
		min = Math.ceil(min);
		max = Math.floor(max);
		return Math.floor(Math.random() * (max - min + 1)) + min;
	}

	setInterval(() => {
		const i = getRandomInt(0, points.length - 1);
		points[i].y = Math.random() * 20;
		points = points;
	}, 100);
</script>

<div class="chart-container">
	<LayerCake data={points} x="x" y="y">
		<Svg>
			<AxisX />
			<AxisY ticks={4} />
			<Line />
		</Svg>
	</LayerCake>
</div>

<div class="relative mx-auto mt-24 max-w-2xl">
	<div class="rounded-md bg-gray-900 p-4 text-white">
		<div class="overflow-x-auto">
			<pre id="code" class="text-gray-300">{data}</pre>
		</div>
	</div>
</div>

<PopupModal bind:this={popupModalComponent} />

<style>
	/*
    The wrapper div needs to have an explicit width and height in CSS.
    It can also be a flexbox child or CSS grid element.
    The point being it needs dimensions since the <LayerCake> element will
    expand to fill it.
  */
	.chart-container {
		width: 100%;
		height: 300px;
	}
</style>
