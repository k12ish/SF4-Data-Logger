<script lang="ts">
	import { Spinner, Button, Modal, Heading, P, A } from 'flowbite-svelte';
	import { fade } from 'svelte/transition';
	import { onMount } from 'svelte';
	import ConnectDevice from 'lib/assets/undraw_monitor_iqpq.svg';
	import FailWarning from 'lib/assets/undraw_warning_re_eoyh.svg';
	import { createEventDispatcher } from 'svelte';
	import { ArduinoInterface } from 'lib/stores.ts';

	onMount(() => setTimeout(() => launch(), 400));
	const dispatch = createEventDispatcher();

	let popupStage:
		| 'hidden'
		| 'visible-first'
		| 'visible-second'
		| 'failed-incapable'
		| 'failed-rejected' = 'hidden';

	function launch() {
		if (!('serial' in navigator)) {
			popupStage = 'failed-incapable';
			return;
		}
		popupStage = 'visible-first';
	}

	async function onClick() {
		popupStage = 'visible-second';
		let port = await getArduinoPort();
		if (port?.readable == null || port?.writable == null) {
			return (popupStage = 'failed-rejected');
		}
		let ard = new ArduinoInterface(port.readable, port.writable);
		setTimeout(() => {
			popupStage = 'hidden';
		}, 300);
		dispatch('gotArduino', { ard });
	}

	async function getArduinoPort() {
		try {
			// limit selectable ports to only USB devices with Arduino's USB vendor ID
			const filter = { usbVendorId: 0x2a03 };
			const port = await navigator.serial.requestPort({ filters: [filter] });
			await port.open({ baudRate: 115_200 });
			// Continue connecting to the device attached to |port|.
			return port;
		} catch (e) {
			// The prompt has been dismissed without selecting a device.
			return null;
		}
	}
</script>

{#if popupStage != 'hidden'}
	<div transition:fade>
		<Modal open={popupStage !== 'hidden'} dismissable={false}>
			{#if popupStage == 'visible-first' || popupStage == 'visible-second'}
				<Heading tag="h2" customSize="text-4xl font-bold ">Connect your Arduino!</Heading>
				<img src={ConnectDevice} class="m-auto max-h-[50vh]" alt="Connect your Arduino" />
				<P class="my-4 text-gray-500"
					>Connect your Arduino Uno from the <A
						href="https://docs.arduino.cc/tutorials/uno-rev3/intro-to-board/">USB-B</A
					> port located on the side of the Board
				</P>
			{:else if popupStage == 'failed-incapable'}
				<Heading tag="h2" customSize="text-4xl font-bold ">Browser Not Supported :(</Heading>
				<img src={FailWarning} class="m-auto max-h-[50vh]" alt="Failed to connect Arduino" />
				<P class="my-4 text-gray-500"
					>Your browser doesn't allow access to external devices because it doesn't support the <A
						href="https://developer.mozilla.org/en-US/docs/Web/API/Web_Serial_API#browser_compatibility"
						>WebSerial Protocol</A
					>. Maybe try Chrome?
				</P>
			{:else if popupStage == 'failed-rejected'}
				<Heading tag="h2" customSize="text-4xl font-bold ">Failed to Connect :(</Heading>
				<img src={FailWarning} class="m-auto max-h-[50vh]" alt="Failed to connect Arduino" />
			{/if}
			<svelte:fragment slot="footer">
				<div class="flex w-full justify-end">
					{#if popupStage == 'visible-first'}
						<Button on:click={onClick}>Done!</Button>
					{:else if popupStage == 'visible-second'}
						<Button>
							<Spinner class="me-3" size="4" color="white" />
							Almost there ...
						</Button>
					{:else}
						<Button color="red" href="/">Exit</Button>
					{/if}
				</div>
			</svelte:fragment>
		</Modal>
	</div>
{/if}
