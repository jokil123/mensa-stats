<script lang="ts">
	let { p }: { p: number } = $props();

	const captions = [
		{ p: 0.1, c: 'So voll wie Rewe am Sonntag' },
		{ p: 0.3, c: 'So voll wie Tinder auf dem Land' },
		{ p: 0.4, c: 'So voll wie H01 in der zweiten vorlesungswoche' },
		// { p: 0.6, c: 'So voll wie Super-C IT Helpdesk' },
		// { p: 0.5, c: 'So voll wie Super-C IT Helpdesk' },
		{ p: 0.7, c: 'So voll wie Europapark Anstehen' },
		{ p: 0.8, c: 'So voll wie Schlange Stehen Simulator' },
		{ p: 0.9, c: 'So voll wie Maschi Party Schlange' },
		{ p: 1.0, c: 'So voll wie Travis Scott 2021' }
	];

	let selected = $derived(
		captions
			.filter((c) => {
				return p <= c.p;
			})
			.sort((a, b) => {
				return a.p - b.p;
			})[0]
	);
</script>

<span>{selected.c}</span>
