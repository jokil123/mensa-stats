<script lang="ts">
	import Chart from '$lib/components/Chart.svelte';
	import Gauge from '$lib/components/Gauge.svelte';
	import MarginBox from '$lib/components/MarginBox.svelte';
	import OccupancyCaption from '$lib/components/OccupancyCaption.svelte';
	let { data } = $props();

	let percentage = $derived(data.occupancy / data.max);
</script>

<svelte:head>
	<title>Mensa Stats</title>
</svelte:head>

<MarginBox>
	<div class="text-center">
		<h1 class="mb-5 text-5xl font-bold">Mensa Stats</h1>

		<h2 class="">Momentane Belegung:</h2>

		<h3 class="text-6xl font-bold">{data.occupancy}</h3>
		<p class="mb-10">Bluetooth Geräte</p>

		{#if data.occupancy == data.max}
			Neuer Rekord 🔥
		{/if}

		<div class="relative">
			<Gauge min={0} max={data.max} current={data.occupancy} />
		</div>

		<h3 class="text-center italic">Wie <OccupancyCaption p={percentage} /></h3>

		<div class="m-auto flex max-h-72 justify-center">
			<Chart history={data.history} />
		</div>
	</div>
</MarginBox>
