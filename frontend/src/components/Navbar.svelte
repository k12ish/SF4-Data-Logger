<script>
	import { Navbar, NavBrand, Button } from 'flowbite-svelte';
	export let showGetStarted = true;
</script>

<Navbar class="m-4">
	<NavBrand href="/">
		<span class="self-center whitespace-nowrap text-xl font-semibold dark:text-white"
			>SF4 Data Logger</span
		>
	</NavBrand>
	{#if showGetStarted}
		<div class="flex md:order-2">
			<Button size="sm" href="/measure">Get started</Button>
		</div>
	{:else}
		<div class="flex md:order-2">
			<Button size="sm" on:click={() => history.back()} color="alternative">Back</Button>
		</div>
	{/if}
	<!--
  // NavLi NavUI
  <NavUl class="order-1">
    <NavLi href="/" active={true}>Home</NavLi>
    <NavLi href="/about">About</NavLi>
    <NavLi href="/docs/components/navbar">Navbar</NavLi>
    <NavLi href="/pricing">Pricing</NavLi>
    <NavLi href="/contact">Contact</NavLi>
  </NavUl>
  -->
</Navbar>
