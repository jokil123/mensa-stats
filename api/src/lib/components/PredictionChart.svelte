<script lang="ts">
	import { cursorPlugin } from '$lib/global/chartjsCursor';
	import type { HistoryPoint } from '$lib/global/historyPoint';
	import { roundN } from '$lib/global/util';
	import Chart, { type ChartConfiguration } from 'chart.js/auto';
	import { onMount } from 'svelte';

	let chartGridColor = 'rgba(255,255,255,0.3)';
	let chartLabelColor = '#d1d5db';

	type Props = {
		history: HistoryPoint[];
	};
	let { history }: Props = $props();

	let last24h: HistoryPoint[] = $derived(
		history.filter((h) => Date.now() - h.timestamp.getTime() < 24 * 60 * 60 * 1000)
	);

	let oneWeekAgo: HistoryPoint[] = $derived(
		history.filter((h) => {
			let oldest = Date.now() - 7 * 24 * 60 * 60 * 1000;
			let newest = Date.now() - 6 * 24 * 60 * 60 * 1000;

			return oldest < h.timestamp.getTime() && h.timestamp.getTime() < newest;
		})
	);

	let prediction: HistoryPoint[] = $derived.by(() => {
		let mostRecentHistory = [...last24h].sort(
			(a, b) => b.timestamp.getTime() - a.timestamp.getTime()
		)[0];
		let oldestOneWeekAgo =
			[...oneWeekAgo].sort((a, b) => a.timestamp.getTime() - b.timestamp.getTime())[0] ||
			mostRecentHistory;

		if (!mostRecentHistory || !oldestOneWeekAgo) {
			return [];
		}

		let scalingFactor = mostRecentHistory.occupancy / oldestOneWeekAgo.occupancy;

		let prediction = oneWeekAgo.map((h) => {
			return {
				occupancy: h.occupancy * scalingFactor,
				timestamp: new Date(h.timestamp.getTime() + 7 * 24 * 60 * 60 * 1000)
			};
		});

		return [mostRecentHistory, ...prediction];
	});

	const toDataPoints = (historyPoints: HistoryPoint[]) => {
		if (!historyPoints) {
			return [];
		}

		return historyPoints.map((h) => {
			return {
				x: h.timestamp,
				y: roundN(h.occupancy, 1)
			};
		});
	};

	let chart: Chart;
	let canvas: HTMLCanvasElement;

	const data = {
		datasets: [
			{
				label: 'Geräte',
				borderColor: 'rgb(50, 168, 82)',
				backgroundColor: 'rgb(50, 168, 82, 0.2)',
				fill: true,
				data: [],
				lineTension: 0.3,
				pointRadius: 2
			},
			{
				label: 'Geräte Vorhersage',
				borderColor: 'rgb(68, 139, 239)',
				backgroundColor: 'rgb(68, 139, 239, 0.2)',
				// backgroundColor: draw('diagonal', '#ffffff', undefined, 10),
				fill: true,
				data: [],
				lineTension: 0.3,
				pointRadius: 2,
				borderDash: [10, 5]
			}
		]
	};

	const config: ChartConfiguration = {
		type: 'line',
		data,
		plugins: [cursorPlugin],
		options: {
			plugins: {
				legend: {
					display: false
				},
				cursor: {
					color: 'white'
				}
			},
			interaction: {
				mode: 'x',
				intersect: false,
				includeInvisible: true,
				axis: 'xy'
			},
			color: chartLabelColor,
			responsive: true,
			maintainAspectRatio: false,
			scales: {
				x: {
					grid: {
						color: chartGridColor
					},
					type: 'time', // Use time scale
					time: {
						unit: 'hour', // Adjust the time unit (hour, minute, day)
						tooltipFormat: 'll HH:mm', // Date format in tooltips
						displayFormats: {
							hour: 'HH:mm' // Display format of time labels
						}
					},
					title: {
						display: false,
						text: 'Zeit',
						color: chartLabelColor
					},
					ticks: {
						color: chartLabelColor
					}
				},
				y: {
					grid: {
						color: chartGridColor
					},
					beginAtZero: false,
					title: {
						display: false,
						text: 'Geräte',
						color: chartLabelColor
					},
					ticks: {
						color: chartLabelColor
					}
				}
			}
		}
	};

	onMount(() => {
		chart = new Chart(canvas, config);

		return () => {
			chart.destroy();
		};
	});

	// Example of updating data dynamically
	// function updateChart() {
	// 	chartData.datasets[0].data = [40, 50, 60];
	// 	chart.update(); // Update the chart with new data
	// }

	$effect(() => {
		chart.data.datasets[0].data = toDataPoints(last24h);
		chart.data.datasets[1].data = toDataPoints(prediction);
		// console.log(chart.data.datasets[0].data);
		chart.update();
	});
</script>

<div class="chart-container m-auto" style="position: relative; height:100%; width:100%;">
	<canvas style="opacity:{prediction.length == 0 ? '0.33' : '1'}" bind:this={canvas}></canvas>
	{#if prediction.length == 0}
		<p
			class="absolute left-1/2 top-1/2 -translate-x-1/2 -translate-y-2/3 text-3xl"
			style="box-shadow: 0px 0px 20px 20px #030712; background: #030712"
		>
			Keine Daten
		</p>
	{/if}
</div>
