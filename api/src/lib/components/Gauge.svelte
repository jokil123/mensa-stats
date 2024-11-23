<script lang="ts">
	import { onMount } from 'svelte';
	import { browser } from '$app/environment';

	type props = {
		max: number;
		min: number;
		current: number;
	};
	let { max, min, current }: props = $props();

	let gauge: any;

	let percentage = $derived((current - min) / (max - min));

	function valP(p: number) {
		return min + p * (max - min);
	}

	onMount(async () => {
		if (!browser) {
			return;
		}

		const { Gauge } = await import('gaugeJS');

		// Create gauge options
		const options = {
			staticZones: [
				{ strokeStyle: '#27b34d', min: min, max: valP(0.3) }, // Green
				{ strokeStyle: '#505f73', min: valP(0.3), max: valP(0.7) },
				{ strokeStyle: '#F03E3E', min: valP(0.7), max: max } // Red
			],
			angle: -0.2, // The span of the gauge arc
			lineWidth: 0.2, // The line thickness
			radiusScale: 1, // Relative radius
			pointer: {
				length: 0.6, // // Relative to gauge radius
				strokeWidth: 0.035, // The thickness
				color: '#FFFFFF' // Fill color
			},
			limitMax: false, // If false, max value increases automatically if value > maxValue
			limitMin: false, // If true, the min value of the gauge will be fixed
			generateGradient: true,
			highDpiSupport: true // High resolution support
		};

		// Target canvas element
		const target = document.getElementById('gauge');
		gauge = new Gauge(target).setOptions(options);

		gauge.maxValue = max; // Set max value
		gauge.setMinValue(min); // Set min value
		gauge.animationSpeed = 10; // Animation speed
		gauge.set(current); // Set initial value
	});

	$effect(() => {
		if (gauge) {
			gauge.set(current);
		}
	});
</script>

<div>
	<canvas id="gauge" style="width:100%;"></canvas>
</div>

<style>
	canvas {
		/* display: block; */
		/* margin: auto; */
		/* width: 100px; */
	}
</style>
