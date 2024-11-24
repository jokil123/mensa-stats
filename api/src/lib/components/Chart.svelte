<script lang="ts">
	import { onMount } from 'svelte';
	import Chart, { type ChartConfiguration } from 'chart.js/auto';
	import 'chartjs-adapter-moment';
	import type { HistoryPoint } from '$lib/db/occupancy';

	type Props = {
		history: HistoryPoint[];
	};
	let { history }: Props = $props();
	let dataPoints = $derived(
		history
			? history.map((h) => {
					return {
						x: h.timestamp,
						y: h.occupancy
					};
				})
			: []
	);

	let chart: Chart;
	let canvas: HTMLCanvasElement;

	const data = {
		datasets: [
			{
				label: 'Belegung',
				borderColor: 'rgb(50, 168, 82)',
				backgroundColor: 'rgb(50, 168, 82, 0.2)',
				fill: false,
				data: [],
				lineTension: 0.5
				// pointRadius: 1
			}
		]
	};

	const config: ChartConfiguration = {
		type: 'line',
		data,
		options: {
			interaction: {
				mode: 'x',
				intersect: true,
				includeInvisible: true,
				axis: 'xy'
			},
			responsive: true,
			maintainAspectRatio: false,
			scales: {
				x: {
					type: 'time', // Use time scale
					time: {
						unit: 'hour', // Adjust the time unit (hour, minute, day)
						tooltipFormat: 'll HH:mm', // Date format in tooltips
						displayFormats: {
							hour: 'MMM D, HH:mm' // Display format of time labels
						}
					},
					title: {
						display: true,
						text: 'Zeit'
					}
				},
				y: {
					beginAtZero: true,
					title: {
						display: true,
						text: 'Geräte'
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
		chart.data.datasets[0].data = dataPoints;
		console.log(chart.data.datasets[0].data);
		chart.update();
	});
</script>

<div class="chart-container m-auto" style="position: relative; height:100%; width:100%">
	<canvas bind:this={canvas}></canvas>
</div>
