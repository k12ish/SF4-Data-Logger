<script lang="ts">
	import PopupModal from 'components/PopupModal.svelte';
	import { Button } from 'flowbite-svelte';
	import { encode } from '@msgpack/msgpack';
	import { decodeMultiStream } from '@msgpack/msgpack';
	let data = '';

	import { LayerCake, Svg } from 'layercake';
	import Line from 'components/EKG/Line.svelte';
	import AxisX from 'components/EKG/AxisX.svelte';
	import AxisY from 'components/EKG/AxisY.svelte';

	import { onMount } from 'svelte';
	import { ArduinoInterface } from 'lib/stores.ts';

	let ard = new ArduinoInterface();

	async function readPort(event: any) {
		let port: SerialPort = event.detail.port;
		await port.open({ baudRate: 115_200 });
		// @ts-ignore: lets pretend everything is readable/writable...
		await ard.updateStreams(port.readable, port.writable);
	}

	// Define some data
	let points = [
		{ x: 0, y: 0 },
		{ x: 5, y: 10 },
		{ x: 10, y: 20 },
		{ x: 15, y: 30 },
		{ x: 20, y: 40 }
	];

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

<div class="chart-container mx-auto rounded border p-8">
	<LayerCake data={points} x="x" y="y">
		<Svg>
			<AxisX />
			<AxisY ticks={4} />
			<Line />
		</Svg>
	</LayerCake>
</div>

<Button on:click={() => ard.updateStreams(new ReadableStream(), new WritableStream())}>
	Default
</Button>

<PopupModal on:gotPort={readPort} />

<style>
	/* The wrapper div needs to have an explicit width and height in CSS. */
	.chart-container {
		width: 96%;
		height: calc(70vh - 1px);
	}
</style>
