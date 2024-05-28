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

	let ard: ArduinoInterface;

	async function gotArduino(event: CustomEvent) {
		ard = event.detail.ard;
		await ard.run();
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

<PopupModal on:gotArduino={gotArduino} />

<style>
	/* The wrapper div needs to have an explicit width and height in CSS. */
	.chart-container {
		width: 96%;
		height: calc(70vh - 1px);
	}
</style>
