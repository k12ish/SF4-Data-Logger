<script>
	import { Heading, P, Button } from 'flowbite-svelte';
	import { ArrowRightOutline } from 'flowbite-svelte-icons';
</script>

<div class="text-center">
	<Heading tag="h1" class="mb-4" customSize="text-4xl font-extrabold  md:text-5xl lg:text-6xl">
		Build your own Electrocardiogram
	</Heading>
	<P class="mb-6 text-lg sm:px-16 lg:text-xl xl:px-48 dark:text-gray-400">
		Measure your heart with an Arduino Uno!
	</P>
	<Button href="https://en.wikipedia.org/wiki/Electrocardiography">
		Learn more
		<ArrowRightOutline class="ms-2 h-6 w-6" />
	</Button>
</div>
