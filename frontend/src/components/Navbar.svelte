<script>
	import { Navbar, NavBrand, Button } from 'flowbite-svelte';
	import { landingPage } from '../lib/stores.js';
</script>

<Navbar class="m-4">
	<NavBrand href="/">
		<button 
			class="self-center whitespace-nowrap text-xl font-semibold dark:text-white"
			on:click={() => landingPage.update((_) => true)}
			>SF4 Data Logger</button
		>
	</NavBrand>
	<div class="flex md:order-2" class:hidden={!$landingPage}>
		<Button size="sm" 
			on:click={() => landingPage.update((_) => false)}
		>
			Get started
		</Button>
	</div>
	<div class="flex md:order-2" class:hidden={$landingPage}>
		<Button 
			size="sm" 
			on:click={() => landingPage.update((_) => true)}
			color="alternative"
		>
			Back
		</Button>
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
