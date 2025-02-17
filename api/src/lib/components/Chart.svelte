<script lang="ts">
	import { onMount } from 'svelte';
	import Chart, { type ChartConfiguration } from 'chart.js/auto';
	import 'chartjs-adapter-moment';
	import type { HistoryPoint } from '$lib/scripts/db/occupancy';
	import { cursorPlugin } from '$lib/scripts/db/chartjsCursor';

	let chartGridColor = 'rgba(255,255,255,0.3)';
	let chartLabelColor = '#d1d5db';

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
				fill: true,
				data: [],
				lineTension: 0.3,
				pointRadius: 2
			}
		]
	};

	const config: ChartConfiguration = {
		type: 'line',
		data,
		plugins: [cursorPlugin],
		options: {
			plugins: {
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
						unit: 'day', // Adjust the time unit (hour, minute, day)
						tooltipFormat: 'll HH:mm', // Date format in tooltips
						displayFormats: {
							hour: 'MMM D, HH:mm' // Display format of time labels
						}
					},
					title: {
						display: true,
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
					beginAtZero: true,
					title: {
						display: true,
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
		chart.data.datasets[0].data = dataPoints;
		// console.log(chart.data.datasets[0].data);
		chart.update();
	});
</script>

<div class="chart-container m-auto" style="position: relative; height:100%; width:100%">
	<canvas bind:this={canvas}></canvas>
</div>
