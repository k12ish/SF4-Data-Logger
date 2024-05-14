<script>
  import { Heading, P, Button } from 'flowbite-svelte';
  import { ArrowRightOutline } from 'flowbite-svelte-icons';
</script>

<div class="text-center">
  <Heading tag="h1" class="mb-4" customSize="text-4xl font-extrabold  md:text-5xl lg:text-6xl">
    Build your own Electrocardiogram
  </Heading>
  <P class="mb-6 text-lg lg:text-xl sm:px-16 xl:px-48 dark:text-gray-400">
    Measure your heart with an Arduino Uno!
  </P>
  <Button href="https://en.wikipedia.org/wiki/Electrocardiography">
    Learn more
    <ArrowRightOutline class="w-6 h-6 ms-2" />
  </Button>
</div>
