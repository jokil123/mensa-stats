<script lang="ts">
	let { p }: { p: number } = $props();

	const captions = [
		{ p: 0.1, c: 'Rewe am Sonntag' },
		{ p: 0.3, c: 'Tinder auf dem Land' },
		{ p: 0.4, c: 'H01 in der zweiten vorlesungswoche' },
		{ p: 0.6, c: 'Super-C IT Helpdesk' },
		{ p: 0.5, c: 'Super-C IT Helpdesk' },
		{ p: 0.7, c: 'Europapark Anstehen' },
		{ p: 0.8, c: 'Schlange Stehen Simulator' },
		{ p: 0.9, c: 'Maschi Party' },
		{ p: 1.0, c: 'Travis Scott 2021' }
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
