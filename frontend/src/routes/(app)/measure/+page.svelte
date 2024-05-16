<script>
	import { onMount } from 'svelte';
	import PopupModal from 'components/PopupModal.svelte';
	let data = '';

	let popupModalComponent;
	onMount(() => setTimeout(() => popupModalComponent.launch(), 400));

</script>

<div class="relative mx-auto mt-24 max-w-2xl">
	<div class="rounded-md bg-gray-900 p-4 text-white">
		<div class="overflow-x-auto">
			<pre id="code" class="text-gray-300">{data}</pre>
		</div>
	</div>
</div>

<PopupModal bind:this={popupModalComponent} />
