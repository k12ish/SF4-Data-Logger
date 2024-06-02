<script lang="ts">
	import { Section, Social } from 'flowbite-svelte-blocks';
	import { Button, Dropdown, DropdownItem, Spinner, Card } from 'flowbite-svelte';
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
	import { heartPyDataset } from 'lib/data.ts';

	let ard: ArduinoInterface;

	async function gotArduino(event: CustomEvent) {
		ard = event.detail.ard;
	}

	// Define some data
	let data: { x: number; y: number }[] = heartPyDataset;
	let view: { x: number; y: number }[] = data;
	let max_view = 5000;
	let view_factor = 1;

	let isRecording = false;

	let dropdownMode: arduinoModes = 'IDLE';
	let dropdownSideText = '';
	let dropdownOpen = false;

	function updateTickFormatter() {
		const now = Date.now();
		tickFormatter = function (micros: number) {
			return new Date(now + micros / 1000).toLocaleTimeString();
		};
	}

	let tickFormatter: (_: number) => string;

	onMount(updateTickFormatter);

	async function dropdownClick(mode: arduinoModes) {
		dropdownOpen = false;
		let errnum: number = 0;
		if (mode == dropdownMode) {
			return;
		}
		dropdownSideText = 'Connecting';
		dropdownMode = mode;
		await ard.setMode(mode, (val, details) => {
			console.log(val, details);
			errnum += 1;
			if (val == 'invalid-response') {
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

	let pyodide: any;
	let pyodide_loaded: boolean = false;
	onMount(async () => {
		//@ts-ignore: we use a script tag for this!
		pyodide = await loadPyodide();
		await pyodide.loadPackage('micropip');
		const micropip = pyodide.pyimport('micropip');
		await micropip.install('neurokit2');
		await pyodide.runPython(`
print('hello world')`);
		pyodide_loaded = true;
	});

	const dropdownMapping: { name: string; code: arduinoModes }[] = [
		{ code: 'IDLE', name: 'Idle' },
		{ code: 'LALL', name: 'Left Arm, Left Leg' },
		{ code: 'RALL', name: 'Right Arm, Left Leg' },
		{ code: 'LARA', name: 'Left Arm, Right Arm' }
	];

	async function plot(context: arduinoModes) {
		const divisor = Math.pow(2, 16);
		let prev_modulus = -(2 ** 15);
		let quotient = 0;

		data = [{ x: 0, y: 500 }];
		view = data;

		while (true) {
			let i = 0;
			for (const arr of await ard.batchRead(10)) {
				let [y, modulus] = arr;
				if (modulus < prev_modulus) {
					quotient += 1;
				}
				prev_modulus = modulus;
				const x = modulus + divisor * quotient;

				if (i % view_factor === 0) {
					view.push({ x, y });
				}
				data.push({ x, y });
				i += 1;
			}
			if (dropdownMode != context) {
				return;
			}
			view = view.slice(Math.max(view.length - max_view, 0));
			data = data.slice(Math.max(data.length - max_view * view_factor, 0));
		}
	}

	function recordClick() {
		dropdownOpen = false;
		isRecording = true;
		view_factor = 10;
		view = data.filter((_, idx) => idx % view_factor == 0);
	}
	function stopClick() {
		isRecording = false;
		view_factor = 1;
		dropdownClick('IDLE');
	}

	let imgUrl = undefined;
	async function analyseClick() {
		dropdownSideText = 'Loading Variables';
		await new Promise((r) => setTimeout(r, 1));
		let measurements = new Int16Array(data.length);
		data.forEach((item, index) => {
			measurements[index] = item.y;
		});
		// @ts-ignore
		document.defaultView.measurements = measurements;
		// @ts-ignore
		document.defaultView.sampleRate = (1e6 * data.length) / (data[data.length - 1].x - data[0].x);
		await pyodide.runPython(`
from js import measurements, sampleRate
from scipy.stats import describe
import numpy as np
import matplotlib.pyplot as plt
import neurokit2 as nk
`);
		dropdownSideText = 'Running Analysis';
		await new Promise((r) => setTimeout(r, 1));
		await pyodide.runPython(`
data = np.asarray(measurements.to_py())
signals, info = nk.ecg_process(data, sampleRate)
nk.ecg_plot(signals, info)
plt.tight_layout()
fig = plt.gcf()
fig.set_size_inches(20, 12, forward=True)
plt.tight_layout()
fig.savefig("figure1.png", dpi=400)
`);
		let file = pyodide.FS.readFile('figure1.png'); // Uint8Array
		imgUrl = URL.createObjectURL(new Blob([file], { type: 'image/png' }));
		dropdownSideText = '';
	}
</script>

<svelte:head>
	<script async src="https://cdn.jsdelivr.net/pyodide/v0.21.3/full/pyodide.js"></script>
</svelte:head>

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
	{#if dropdownMode != 'IDLE'}
		<Button
			color="light"
			on:click={() => {
				isRecording ? stopClick() : recordClick();
			}}
		>
			{#if isRecording}
				<StopSolid />
			{:else}
				<PlayOutline />
			{/if}
		</Button>
	{:else}
		<Button outline color="green" disabled={!pyodide_loaded} on:click={analyseClick}>Analyse</Button
		>
	{/if}
</Navbar>

<div class="chart-container mx-auto rounded border p-8">
	<LayerCake data={view} x="x" y="y">
		<Svg>
			<AxisX ticks={6} format={tickFormatter} />
			<AxisY ticks={4} />
			<Line />
		</Svg>
	</LayerCake>
</div>

{#if data.length > 10}
	<Social>
		<div class="flex flex-col items-center justify-center">
			<dt class="mb-1 text-3xl font-semibold md:text-4xl">{data.length}</dt>
			<dd class="font-light text-gray-500 dark:text-gray-400">Datapoints</dd>
		</div>
		<div class="flex flex-col items-center justify-center">
			<dt class="mb-1 text-3xl font-semibold md:text-4xl">
				{(1e-6 * (data[data.length - 1].x - data[0].x)).toFixed(2)}s
			</dt>
			<dd class="font-light text-gray-500 dark:text-gray-400">Total Duration</dd>
		</div>
		<div class="flex flex-col items-center justify-center">
			<dt class="mb-1 text-3xl font-semibold md:text-4xl">
				{((1e6 * data.length) / (data[data.length - 1].x - data[0].x)).toFixed(2)}Hz
			</dt>
			<dd class="font-light text-gray-500 dark:text-gray-400">Sampling Frequency</dd>
		</div>
	</Social>
{/if}

<div class="container mx-auto px-4">
	{#if imgUrl}
		<img class="w-full" src={imgUrl} alt="Generated Plot" />
	{/if}
</div>

<PopupModal on:gotArduino={gotArduino} />

<style>
	/*
	 The wrapper div needs to have an explicit width and height in CSS. */
	.chart-container {
		width: 96%;
		height: calc(80vh - 1px);
	}
</style>
