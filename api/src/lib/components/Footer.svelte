<script lang="ts">
	import github from '$lib/assets/github.png';
	import MarginBox from './MarginBox.svelte';

	let pageHeight = 0;
	let windowHeight = 0;
</script>

<svelte:body bind:offsetHeight={pageHeight} />
<svelte:window bind:innerHeight={windowHeight} />

<footer
	class="{windowHeight == pageHeight && 'absolute bottom-0'} z-50 w-full py-5"
	style="background-color: rgb(2,2,6);"
>
	<MarginBox>
		<div class="flex flex-col items-center justify-center gap-10 font-bold md:flex-row">
			<a href="/info">Info</a>
			<a href="https://github.com/jokil123/mensa-stats" class="flex items-center gap-1">
				GitHub
				<img src={github} alt="GitHub Logo" class="h-7 w-7" />
			</a>
			<a href="https://joshualung.com">Portfolio</a>
			<a href="mailto://joshua.lung@rwth-aachen.de">joshua.lung@rwth-aachen.de</a>
		</div>
	</MarginBox>
</footer>
