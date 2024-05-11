<script>
	import '../app.css';
	import { Skeleton } from 'flowbite-svelte';
	import  Footer from './../components/Footer.svelte'
</script>

<slot />
<div class="container mx-auto">
	<Skeleton size="xl" class="my-8" />
	<Skeleton size="xl" class="my-8" />
	<Skeleton size="xl" class="my-8" />
	<Skeleton size="xl" class="my-8" />
	<Skeleton size="xl" class="my-8" />
</div>

<Footer/>

<style></style>
