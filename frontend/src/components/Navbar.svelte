<script>
	import { Navbar, NavBrand, NavHamburger, Button } from 'flowbite-svelte';
	export let showButton = true;
</script>

<Navbar class="m-4">
	<NavBrand href="/">
		<span class="self-center whitespace-nowrap text-xl font-semibold dark:text-white"
			>SF4 Data Logger</span
		>
	</NavBrand>
	<div class="flex md:order-2" class:invisible={!showButton}>
		<Button size="sm" href="/about">Get started</Button>
		<NavHamburger />
	</div>
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
