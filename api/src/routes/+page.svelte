<script lang="ts">
	import Chart from '$lib/components/Chart.svelte';
	import Gauge from '$lib/components/Gauge.svelte';
	import MarginBox from '$lib/components/MarginBox.svelte';
	import OccupancyCaption from '$lib/components/OccupancyCaption.svelte';
	import Footer from '$lib/components/Footer.svelte';

	let { data } = $props();

	let percentage = $derived(data.occupancy.occupancy / data.max.occupancy);

	let isAlive = $derived(Date.now() - data.occupancy.timestamp.getTime() < 10 * 60 * 1000);
</script>

<svelte:head>
	<title>Mensa Stats</title>
</svelte:head>

<MarginBox>
	<div class="mb-32 text-center">
		<h1 class="mb-8 text-5xl font-bold text-white">Mensa Stats</h1>

		<h2 class="">Momentane Belegung:</h2>

		<div class="flex items-center justify-center">
			<h3 class="text-7xl font-bold text-white">
				{data.occupancy.occupancy}
			</h3>
			{#if data.occupancy.occupancy == data.max.occupancy}
				<p title="Neuer Rekord!" class="cursor-pointer select-none text-5xl">🔥</p>
			{/if}
		</div>
		<p class="mb-8">Bluetooth Geräte</p>

		<div class="mb-5 flex items-center justify-center gap-7">
			<div class="flex items-center justify-center gap-4">
				<div
					class="h-7 w-7 rounded-full {isAlive
						? 'bg-green-500'
						: 'bg-red-500'} outline outline-offset-2"
				></div>
				<h2 class="text-3xl font-bold {isAlive ? 'text-green-500' : 'text-red-500'}">
					{isAlive ? 'Online' : 'Offline'}
				</h2>
			</div>

			<div>
				<!-- if last update happened withing the last 24 hours display only time, otherwise display date (hh:mm dd.mm.yy) -->
				<p>Letztes Update:</p>
				<p class="text-2xl font-bold">
					{#if data.occupancy.timestamp.getDate() === new Date().getDate()}
						{data.occupancy.timestamp.toLocaleTimeString()}
					{:else}
						{data.occupancy.timestamp.toLocaleString()}
					{/if}
				</p>
				<p>
					(vor {((Date.now() - data.occupancy.timestamp.getTime()) / (1000 * 60)).toFixed(0)} Minuten)
				</p>
			</div>
		</div>

		<Gauge min={data.min.occupancy} max={data.max.occupancy} current={data.occupancy.occupancy} />

		<h3 class="text-center text-xl font-bold italic">Wie <OccupancyCaption p={percentage} /></h3>
	</div>
</MarginBox>

<div class="bg-gray-950 py-16">
	<MarginBox>
		<div class="mb-10 text-center">
			<h2 class="text-3xl font-bold">Statistik</h2>
			<p class="text-gray-400">Belegung der letzten sieben Tage</p>
		</div>
		<div class="h-72">
			<Chart history={data.averagedHistory} />
		</div>
	</MarginBox>
</div>

<Footer />
