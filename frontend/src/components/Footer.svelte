<script>
  import { Footer, FooterIcon } from 'flowbite-svelte';
  import { FacebookSolid, GithubSolid, DiscordSolid, TwitterSolid } from 'flowbite-svelte-icons';
</script>

<Footer footerType="socialmedia">
  <hr class="my-3 border-gray-200 sm:mx-auto dark:border-gray-700 lg:my-8" />
  <div class="sm:flex sm:items-center sm:justify-between">
		<span class="block text-sm text-gray-500 sm:text-center dark:text-gray-400">
			©{new Date().getFullYear()}
			<a href="https://github.com/k12ish/" class="hover:underline">Krish Shah</a> and
			<a href="https://github.com/jepohle" class="hover:underline">Jeremias Pohle</a>. All Rights
			Reserved.
		</span>
    <div class="flex mt-4 space-x-6 rtl:space-x-reverse sm:justify-center sm:mt-0">
      <FooterIcon href="https://github.com/k12ish/SF4-Data-Logger">
        <GithubSolid class="w-5 h-5 text-gray-500 dark:text-gray-500 hover:text-gray-900 dark:hover:text-white" />
      </FooterIcon>
    </div>
  </div>
</Footer>
