<script lang="ts">
	let { p }: { p: number } = $props();

	const captions = [
		{ p: 0.1, c: 'Rewe am Sonntag' },
		{ p: 0.2, c: 'Tinder auf dem Land' },
		{ p: 0.6, c: 'Super-C IT Helpdesk' },
		{ p: 0.8, c: 'Europapark Anstehen' },
		{ p: 0.9, c: 'Schlange Stehen Simulator' },
		{ p: 1, c: 'Travis Scott 2021' }
	];

	let selected = $derived(
		captions
			.filter((c) => {
				return c.p <= p;
			})
			.sort((a, b) => {
				return b.p - a.p;
			})[0]
	);
</script>

<span>{selected.c}</span>
