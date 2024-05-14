<script>
	import '../../app.css';
	import Footer from 'components/Footer.svelte';
	import Navbar from 'components/Navbar.svelte';
</script>

<Navbar showGetStarted={true} />

<slot />

<Footer />
