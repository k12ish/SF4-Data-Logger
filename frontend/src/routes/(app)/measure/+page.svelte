<script lang="ts">
	import { Button, Dropdown, DropdownItem, Spinner } from 'flowbite-svelte';
	import { ChevronDownOutline, PlayOutline, StopSolid } from 'flowbite-svelte-icons';

	import { onMount } from 'svelte';

	import Navbar from 'components/Navbar.svelte';
	import PopupModal from 'components/PopupModal.svelte';

	import { LayerCake, Svg } from 'layercake';
	import Line from 'components/EKG/Line.svelte';
	import AxisX from 'components/EKG/AxisX.svelte';
	import AxisY from 'components/EKG/AxisY.svelte';

	import { ArduinoInterface } from 'lib/stores.ts';
	import type { arduinoModes } from 'lib/stores.ts';

	let ard: ArduinoInterface;

	async function gotArduino(event: CustomEvent) {
		ard = event.detail.ard;
	}

	// Define some data
	let points = [{ x: 0, y: 0 }];

	// setInterval(() => {
	// 	const i = getRandomInt(0, points.length - 1);
	// 	points[i].y = Math.random() * 20;
	// 	points = points;
	// }, 100);

	let isRecording = false;

	let dropdownMode: arduinoModes = 'IDLE';
	let dropdownSideText = '';
	let dropdownOpen = false;

	async function dropdownClick(mode: arduinoModes) {
		dropdownOpen = false;
		let errnum: number = 0;
		if (mode == dropdownMode) {
			return;
		}
		dropdownSideText = 'Connecting';
		dropdownMode = mode;
		await ard.setMode(mode, (val) => {
			errnum += 1;
			if (val == 'timeout') {
				dropdownSideText = 'Response Timeout';
			} else if (val == 'invalid-response') {
				dropdownSideText = 'Invalid Response';
			} else if (val == 'ioerror') {
				dropdownSideText = 'I/O Error';
			}
			if (errnum > 1) {
				dropdownSideText += '(' + errnum + ')';
			}
		});
		dropdownSideText = '';
		if (dropdownMode != 'IDLE') {
			await plot(dropdownMode);
		}
	}

	const dropdownMapping: { name: string; code: arduinoModes }[] = [
		{ code: 'IDLE', name: 'Idle' },
		{ code: 'LALL', name: 'Left Arm, Left Leg' },
		{ code: 'RALL', name: 'Right Arm, Left Leg' },
		{ code: 'LARA', name: 'Left Arm, Right Arm' }
	];

	async function plot(context: arduinoModes) {
		const reference = Date.now() * 1_000;
		const divisor = Math.pow(2, 16);
		let prev_modulus = -(2 ** 15);
		let quotient = 0;

		points = [{x: reference, y:0}]

		while (true) {
			for (const arr of await ard.batchRead(10)) {
				let [y, modulus] = arr;
				if (modulus < prev_modulus) {
					quotient += 1;
				}
				prev_modulus = modulus;
				const x = reference + modulus + divisor * quotient;
				points.push({ x, y });
			}
			points = points.slice(Math.max(points.length - 5000, 1));
			if (dropdownMode != context) {
				return;
			}
		}
	}

	function recordClick() {
		dropdownOpen = false;
		isRecording = true;
	}
	function stopClick() {}
</script>

<Navbar>
	{#if dropdownSideText}
		<span class="self-center px-2"> {dropdownSideText} <Spinner size="4" /> </span>
	{/if}
	<Button on:click={() => (dropdownOpen = !dropdownOpen)} disabled={isRecording}>
		{dropdownMapping.find((item) => item.code === dropdownMode)?.name || 'Not Found'}
		<ChevronDownOutline class="ms-2 h-6 w-6 text-white dark:text-white" />
		<Dropdown open={dropdownOpen}>
			{#each dropdownMapping as mode}
				<DropdownItem on:click={() => dropdownClick(mode.code)}>{mode.name}</DropdownItem>
			{/each}
		</Dropdown>
	</Button>
	<div class="px-2" />
	<Button
		color="light"
		enable={dropdownMode != 'IDLE'}
		on:click={() => {
			isRecording ? recordClick() : stopClick();
		}}
	>
		{#if isRecording}
			<StopSolid />
		{:else}
			<PlayOutline />
		{/if}
	</Button>
</Navbar>

<div class="chart-container mx-auto rounded border p-8">
	<LayerCake data={points} x="x" y="y">
		<Svg>
			<AxisX ticks={6} format={(t) => new Date(t / 1000).toLocaleTimeString()} />
			<AxisY ticks={4} />
			<Line />
		</Svg>
	</LayerCake>
</div>

<div class="mx-auto p-8">
	{#if points.length > 10}
	{points.length} Measurements
	<br />
	{(1e-6 * (points[points.length - 1].x - points[0].x)).toFixed(4)}s Duration
	<br />
	{((1e6 * points.length) / (points[points.length - 1].x - points[0].x)).toFixed(2)}Hz Frequency
	{/if}
</div>

<PopupModal on:gotArduino={gotArduino} />

<style>
	/* The wrapper div needs to have an explicit width and height in CSS. */
	.chart-container {
		width: 96%;
		height: calc(80vh - 1px);
	}
</style>
