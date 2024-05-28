<script>
	import { Navbar, NavBrand, Button } from 'flowbite-svelte';
</script>

<Navbar class="my-4">
	<NavBrand href="/">
		<span class="self-center whitespace-nowrap text-2xl font-semibold dark:text-white"
			>SF4 Data Logger</span
		>
	</NavBrand>

	<div class="flex md:order-2">
		<slot>
			<Button size="sm" href="/measure">Get started</Button>
		</slot>
	</div>

</Navbar>
