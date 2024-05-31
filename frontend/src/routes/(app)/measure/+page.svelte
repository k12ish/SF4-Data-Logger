<script lang="ts">
	import { Button, Dropdown, DropdownItem, Spinner } from 'flowbite-svelte';
	import { ChevronDownOutline, PlayOutline, StopSolid } from 'flowbite-svelte-icons';

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
		// await ard.run();
	}

	// Define some data
	let points = [
		{ x: 0, y: 0 },
		{ x: 5, y: 10 },
		{ x: 10, y: 20 },
		{ x: 15, y: 30 },
		{ x: 20, y: 40 }
	];

	// function getRandomInt(min: number, max: number): number {
	// 	return Math.floor(Math.random() * (max - min + 1)) + min;
	// }

	// setInterval(() => {
	// 	const i = getRandomInt(0, points.length - 1);
	// 	points[i].y = Math.random() * 20;
	// 	points = points;
	// }, 100);

	let selectedDropdown: arduinoModes = 'IDLE';
	let dropdownSideText = '';
	let dropdownOpen = false;

	async function dropdownClick(mode: arduinoModes) {
		dropdownOpen = false;
		let errnum: number = 0;
		if (mode == selectedDropdown) {
			return;
		}
		dropdownSideText = 'Connecting';
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
		selectedDropdown = mode;
		dropdownSideText = '';
	}

	const dropdownMapping: { name: string; code: arduinoModes }[] = [
		{ code: 'IDLE', name: 'Idle' },
		{ code: 'LALL', name: 'Left Arm, Left Leg' },
		{ code: 'RALL', name: 'Right Arm, Left Leg' },
		{ code: 'LARA', name: 'Left Arm, Right Arm' }
	];
</script>

<Navbar>
	{#if dropdownSideText}
		<span class="self-center px-2"> {dropdownSideText} <Spinner size="4" /> </span>
	{/if}
	<Button on:click={() => (dropdownOpen = true)}>
		Measurement Mode {dropdownMapping.find((item) => item.code === selectedDropdown)?.name ||
			'Not Found'}
		<ChevronDownOutline class="ms-2 h-6 w-6 text-white dark:text-white" />
	</Button>
	<Dropdown open={dropdownOpen}>
		{#each dropdownMapping as mode}
			<DropdownItem on:click={() => dropdownClick(mode.code)}>{mode.name}</DropdownItem>
		{/each}
	</Dropdown>
	<div class="px-2" />
	<Button
		color="light"
		on:click={async () => {
			while (true) {
				console.log(await ard.batchRead(1000));
			}
		}}
	>
		<PlayOutline />
	</Button>
</Navbar>

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
