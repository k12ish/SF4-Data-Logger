<script lang="ts">
	import { Section, HeroHeader, FeatureDefault, FeatureItem } from 'flowbite-svelte-blocks';
	import {
		ChartPieSolid,
		LandmarkSolid,
		BriefcaseSolid,
		DollarOutline,
		RocketSolid,
		CogOutline
	} from 'flowbite-svelte-icons';
	import { Heading, P, Button } from 'flowbite-svelte';
	import { ArrowRightOutline } from 'flowbite-svelte-icons';
  import { Section, News, HeroHeader, HeroBody } from 'flowbite-svelte-blocks';
  import { Button } from 'flowbite-svelte';
  import { ArrowRightOutline } from 'flowbite-svelte-icons';
  import { Cta } from 'flowbite-svelte-blocks';
  import { ArrowRightOutline } from 'flowbite-svelte-icons';

	import ArduinoImage from 'lib/assets/harrison-broadbent-unsplash.jpg';
</script>

<Section name="heroVisual">
  <div class="mr-auto place-self-center lg:col-span-7">
    <HeroHeader h1Class="max-w-2xl mb-4 text-4xl font-extrabold tracking-tight leading-none md:text-5xl xl:text-6xl dark:text-white" pClass="max-w-2xl mb-6 font-light text-gray-500 lg:mb-8 md:text-lg lg:text-xl dark:text-gray-400">
      <svelte:fragment slot="h1">Measure your Heart</svelte:fragment>
      <svelte:fragment slot="paragraph">Your heart, your data, anywhere</svelte:fragment>
      <a href="measure/"><Button size="xl" class="inline-flex items-center justify-center mr-3">Measure<ArrowRightOutline size="md" class="ml-2 -mr-1" /></Button> </a>
    </HeroHeader>
  </div>
  <div class="hidden lg:mt-0 lg:col-span-5 lg:flex">
      <img class="w-full dark:hidden" src="https://flowbite.s3.amazonaws.com/blocks/marketing-ui/cta/cta-dashboard-mockup.svg" alt="dashboard" />
      <img class="w-full hidden dark:block" src="https://flowbite.s3.amazonaws.com/blocks/marketing-ui/cta/cta-dashboard-mockup-dark.svg" alt="dashboard" />
  </div>
</Section>

<Section name="feature">
	<HeroHeader
		class="mb-8 max-w-screen-md lg:mb-16"
		h2Class="mb-4 text-4xl tracking-tight font-extrabold text-gray-900 dark:text-white"
		pClass="text-gray-500 sm:text-xl dark:text-gray-400"
	>
		<svelte:fragment slot="h2">A Market Distruptor</svelte:fragment>
		<svelte:fragment slot="paragraph"
			>Operates on any device with a web browser, providing a flexible alternative to conventional ECG units</svelte:fragment
		>
	</HeroHeader>
	<FeatureDefault>
		<FeatureItem>
			<svelte:fragment slot="icon"
				><ChartPieSolid class="text-primary-600 dark:text-primary-300" /></svelte:fragment
			>
			<svelte:fragment slot="h3">Backed by NeuroKit2</svelte:fragment>
			<svelte:fragment slot="paragraph"
				>Utilizes the well-established NeuroKit2 Python library for robust analysis. Plots BPM variation and the mean PQRST cardiac cycle.</svelte:fragment
			>
		</FeatureItem>
		<FeatureItem>
			<svelte:fragment slot="icon"
				><LandmarkSolid class="text-primary-600 dark:text-primary-300" /></svelte:fragment
			>
			<svelte:fragment slot="h3">No Installation Required</svelte:fragment>
			<svelte:fragment slot="paragraph"
				>Simply plug and play on any machine with a web browser. All data is processed locally, ensuring regulatory compliance and enhanced privacy.</svelte:fragment
			>
		</FeatureItem>
		<FeatureItem>
			<svelte:fragment slot="icon"
				><BriefcaseSolid class="text-primary-600 dark:text-primary-300" /></svelte:fragment
			>
			<svelte:fragment slot="h3">Three Measurement Modes</svelte:fragment>
			<svelte:fragment slot="paragraph"
				>Provides enhanced diagnostic capabilities through multiple measurement modes.</svelte:fragment
			>
		</FeatureItem>
		<FeatureItem>
			<svelte:fragment slot="icon"
				><DollarOutline class="text-primary-600 dark:text-primary-300" /></svelte:fragment
			>
			<svelte:fragment slot="h3">Cost-effective</svelte:fragment>
			<svelte:fragment slot="paragraph"
				>The device costs less than £15 and our web hosting is free!</svelte:fragment
			>
		</FeatureItem>
		<FeatureItem>
			<svelte:fragment slot="icon"
				><RocketSolid class="text-primary-600 dark:text-primary-300" /></svelte:fragment
			>
			<svelte:fragment slot="h3">Highly Performant</svelte:fragment>
			<svelte:fragment slot="paragraph"
				>On average, uses less than half a thread when continuously plotting 5,000 data points at 60FPS.</svelte:fragment
			>
		</FeatureItem>
		<FeatureItem>
			<svelte:fragment slot="icon"
				><CogOutline class="text-primary-600 dark:text-primary-300" /></svelte:fragment
			>
			<svelte:fragment slot="h3">High Sampling Frequency</svelte:fragment>
			<svelte:fragment slot="paragraph"
				>Sampling frequency of 2.3kHz far exceeds the recommended 250 Hz for accurate cardiac analysis.</svelte:fragment
			>
		</FeatureItem>
	</FeatureDefault>
</Section>

<Section name="ctawithimg">
  <Cta ctatype="image">
    <svelte:fragment slot="img">
		<img src={ArduinoImage} class="w-full" alt="Arduino"/>
    </svelte:fragment>
    <svelte:fragment slot="h2">Accessible and Open Hardware</svelte:fragment>
    <p class="mb-6 font-light text-gray-500 md:text-lg dark:text-gray-400">
    Open source design files, with KiCad schematics and layouts for amplifiers, multiplexers, and the entire ECG circuit. 
    Additionally, simulation results and circuit models are available to help you understand and verify the performance of our device.
    </p>
    <a href="https://github.com/k12ish/SF4-Data-Logger" class="inline-flex items-center text-white bg-primary-700 hover:bg-primary-800 focus:ring-4 focus:ring-primary-300 font-medium rounded-lg text-sm px-5 py-2.5 text-center dark:focus:ring-primary-900">
      Explore our Repository
      <ArrowRightOutline size="md" class="ml-2 -mr-1" />
    </a>
  </Cta>
</Section>
