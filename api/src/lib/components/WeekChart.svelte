<script lang="ts">
	import type { HistoryPoint } from '$lib/scripts/db/occupancy';

	let times = [11, 12, 13, 14, 15, 16, 17, 18, 19];
	let days = ['Mo', 'Di', 'Mi', 'Do', 'Fr', 'Sa', 'So'];

	type Props = {
		history: HistoryPoint[];
	};
	let props: Props = $props();
	let history = $derived(filterHistory(props.history));

	function filterHistory(hist: HistoryPoint[]): HistoryPoint[] {
		if (!hist) {
			return [];
		}

		return hist.filter((h) => {
			let time = h.timestamp.getHours();
			return times.includes(time);
		});
	}

	let min = $derived(Math.min(...history.map((h) => h.occupancy)));
	let max = $derived(Math.max(0, ...history.map((h) => h.occupancy)));

	type WeekChartData = { [day: string]: { [time: number]: HistoryPoint } };

	let weekChartData = $derived(generateWeekChartData(history));

	function generateWeekChartData(history: HistoryPoint[]): WeekChartData {
		let weekChartData: WeekChartData = {};

		history.forEach((h) => {
			let time = h.timestamp.getHours();
			let dayIndex = (h.timestamp.getDay() + 6) % 7;
			let day = days[dayIndex];

			if (!times.includes(time)) {
				return;
			}

			if (!weekChartData[day]) {
				weekChartData[day] = {};
			}

			weekChartData[day][time] = h;
		});
		return weekChartData;
	}

	function dataAvailable(day: string, time: number): boolean {
		if (!weekChartData[day]) return false;
		if (!weekChartData[day][time]) return false;
		return true;
	}

	function getData(day: string, time: number): HistoryPoint {
		return weekChartData[day][time];
	}

	function getColor(day: string, time: number): string {
		if (!dataAvailable(day, time)) return `#111827`;

		let palette = ['#21c25d', '#84c04f', '#d4b53b', '#ffa340', '#ef4444'];
		let p = (getData(day, time).occupancy - min) / (max - min);
		let paletteIndex = Math.max(0, Math.ceil(p * palette.length) - 1);

		return palette[paletteIndex];

		// 0.0 - 0.2 -> 0
		// 0.2 - 0.4 -> 1
		// 0.4 - 0.6 -> 2
		// 0.6 - 0.8 -> 3
		// 0.8 - 1.0 -> 4
	}

	let width = $state(0);
	let compact: boolean = $derived(width < 640);
	let gridCols = $derived(compact);
</script>

<svelte:window bind:innerWidth={width} />

<div
	class="grid items-center justify-center justify-items-center gap-1 sm:gap-2 {compact
		? 'grid-flow-col'
		: 'grid-flow-row'}"
	style="grid-template-{compact ? 'rows' : 'columns'}: repeat({times.length + 1}, min-content);"
>
	<div>
		<!-- Corner -->
	</div>
	{#each times as time}
		<div class="font-bold">{time}</div>{/each}
	{#each days as day}
		<div class="justify-self-start font-bold">{day}</div>
		{#each times as time}
			<div
				class="flex h-8 w-8 items-center justify-center sm:h-12 sm:w-12"
				style="background-color: {getColor(day, time)}"
			>
				{#if dataAvailable(day, time)}
					<div class="text-white sm:font-bold">
						{getData(day, time).occupancy.toFixed(1)}
					</div>
				{/if}
			</div>
		{/each}
	{/each}
</div>
