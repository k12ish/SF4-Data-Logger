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
</script>

<Section name="heroVisual">
  <div class="mr-auto place-self-center lg:col-span-7">
    <HeroHeader h1Class="max-w-2xl mb-4 text-4xl font-extrabold tracking-tight leading-none md:text-5xl xl:text-6xl dark:text-white" pClass="max-w-2xl mb-6 font-light text-gray-500 lg:mb-8 md:text-lg lg:text-xl dark:text-gray-400">
      <svelte:fragment slot="h1">Measure your Heart</svelte:fragment>
      <svelte:fragment slot="paragraph">From checkout to global sales tax compliance, companies around the world use Flowbite to simplify their payment stack.</svelte:fragment>
      <a href="measure/"><Button size="xl" class="inline-flex items-center justify-center mr-3">Get started<ArrowRightOutline size="md" class="ml-2 -mr-1" /></Button> </a>
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
		<svelte:fragment slot="h2">Designed for business teams like yours</svelte:fragment>
		<svelte:fragment slot="paragraph"
			>Here at Flowbite we focus on markets where technology, innovation, and capital can unlock
			long-term value and drive economic growth.</svelte:fragment
		>
	</HeroHeader>
	<FeatureDefault>
		<FeatureItem>
			<svelte:fragment slot="icon"
				><ChartPieSolid class="text-primary-600 dark:text-primary-300" /></svelte:fragment
			>
			<svelte:fragment slot="h3">Marketing</svelte:fragment>
			<svelte:fragment slot="paragraph"
				>Plan it, create it, launch it. Collaborate seamlessly with all the organization and hit
				your marketing goals every month with our marketing plan.</svelte:fragment
			>
		</FeatureItem>
		<FeatureItem>
			<svelte:fragment slot="icon"
				><LandmarkSolid class="text-primary-600 dark:text-primary-300" /></svelte:fragment
			>
			<svelte:fragment slot="h3">Legal</svelte:fragment>
			<svelte:fragment slot="paragraph"
				>Protect your organization, devices and stay compliant with our structured workflows and
				custom permissions made for you.</svelte:fragment
			>
		</FeatureItem>
		<FeatureItem>
			<svelte:fragment slot="icon"
				><BriefcaseSolid class="text-primary-600 dark:text-primary-300" /></svelte:fragment
			>
			<svelte:fragment slot="h3">Business Automation</svelte:fragment>
			<svelte:fragment slot="paragraph"
				>Auto-assign tasks, send Slack messages, and much more. Now power up with hundreds of new
				templates to help you get started.</svelte:fragment
			>
		</FeatureItem>
		<FeatureItem>
			<svelte:fragment slot="icon"
				><DollarOutline class="text-primary-600 dark:text-primary-300" /></svelte:fragment
			>
			<svelte:fragment slot="h3">Finance</svelte:fragment>
			<svelte:fragment slot="paragraph"
				>Audit-proof software built for critical financial operations like month-end close and
				quarterly budgeting.</svelte:fragment
			>
		</FeatureItem>
		<FeatureItem>
			<svelte:fragment slot="icon"
				><RocketSolid class="text-primary-600 dark:text-primary-300" /></svelte:fragment
			>
			<svelte:fragment slot="h3">Enterprise Design</svelte:fragment>
			<svelte:fragment slot="paragraph"
				>Craft beautiful, delightful experiences for both marketing and product with real
				cross-company collaboration.</svelte:fragment
			>
		</FeatureItem>
		<FeatureItem>
			<svelte:fragment slot="icon"
				><CogOutline class="text-primary-600 dark:text-primary-300" /></svelte:fragment
			>
			<svelte:fragment slot="h3">Operations</svelte:fragment>
			<svelte:fragment slot="paragraph"
				>Keep your company’s lights on with customizable, iterative, and structured workflows built
				for all efficient teams and individual.</svelte:fragment
			>
		</FeatureItem>
	</FeatureDefault>
</Section>
