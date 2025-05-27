<script lang="ts">
	import Chart from '$lib/components/Chart.svelte';
	import Gauge from '$lib/components/Gauge.svelte';
	import MarginBox from '$lib/components/MarginBox.svelte';
	import OccupancyCaption from '$lib/components/OccupancyCaption.svelte';
	import Footer from '$lib/components/Footer.svelte';
	import WeekChart from '$lib/components/WeekChart.svelte';
	import PredictionChart from '$lib/components/PredictionChart.svelte';

	let { data } = $props();

	let percentage = $derived(data.occupancy.occupancy / data.max.occupancy);

	let isAlive = $derived(Date.now() - data.occupancy.timestamp.getTime() < 10 * 60 * 1000);
</script>

<svelte:head>
	<title>Mensa Stats</title>
</svelte:head>

<MarginBox>
	<div class="mb-20 text-center">
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

		<Gauge min={data.min.occupancy} max={data.max.occupancy} current={data.occupancy.occupancy} />

		<h3 class="mb-10 text-center text-xl font-bold italic">
			Wie <OccupancyCaption p={percentage} />
		</h3>

		<div class="mb-5 flex items-center justify-center gap-7">
			<div class="flex items-center justify-center gap-4">
				<div
					class="h-5 w-5 rounded-full {isAlive
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
					(vor {((Date.now() - data.occupancy.timestamp.getTime()) / (1000 * 60)).toFixed(1)} Minuten)
				</p>
			</div>
		</div>
	</div>
</MarginBox>

<div class="bg-gray-950 py-16">
	<MarginBox>
		{#if data.averagedHistory && data.averagedHistory.length > 1}
			<div class="mb-8 text-center">
				<h2 class="text-3xl font-bold">Vorhersage</h2>
				<p class="text-gray-400">Belegung anhand vorheriger Daten</p>
			</div>
			<div class="mb-16">
				<PredictionChart history={data.averagedHistory} />
			</div>

			<div class="mb-8 text-center">
				<h2 class="text-3xl font-bold">Wochentage</h2>
				<p class="text-gray-400">Belegung pro Wochentag</p>
			</div>
			<div class="mb-16">
				<WeekChart history={data.averagedHistory} />
			</div>

			<div class="mb-8 text-center">
				<h2 class="text-3xl font-bold">Statistik</h2>
				<p class="text-gray-400">Belegung der letzten sieben Tage</p>
			</div>
			<div class="mb-16 h-72">
				<Chart history={data.averagedHistory} />
			</div>
		{:else}
			<div class="text-center">
				<h2 class="text-3xl font-bold">Kein Daten vorhanden!</h2>
				<p class="text-gray-400">Schaue später nochmal vorbei</p>
			</div>
		{/if}
	</MarginBox>
</div>

<Footer />
