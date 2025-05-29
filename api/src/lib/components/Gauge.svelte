<script lang="ts">
	import { onMount } from 'svelte';
	import { browser } from '$app/environment';

	let gaugeHeight = $state(0);

	type props = {
		max: number;
		min: number;
		current: number;
	};
	let { max, min, current }: props = $props();

	let gauge: any;

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
				{ strokeStyle: '#22c55e', min: min, max: valP(0.3) }, // Green
				{ strokeStyle: '#505f73', min: valP(0.3), max: valP(0.7) },
				{ strokeStyle: '#ef4444', min: valP(0.7), max: max } // Red
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

<div class="flex justify-center">
	<canvas bind:clientHeight={gaugeHeight} id="gauge" style="width:100%;" class="max-w-[50rem]"
	></canvas>
</div>

<div
	class="m-auto mb-10 flex w-full justify-between"
	style="width:{gaugeHeight * 0.6}px; margin-top: {-gaugeHeight * 0.1}px"
>
	<p style="font-size: {gaugeHeight * 0.1}px;" class="font-bold">{Math.floor(min)}</p>
	<p style="font-size: {gaugeHeight * 0.1}px;" class="font-bold">{Math.ceil(max)}</p>
</div>

<style>
	canvas {
		/* display: block; */
		/* margin: auto; */
		/* width: 100px; */
	}
</style>
