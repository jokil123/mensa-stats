import {
	getAveragedOccupancyHistory,
	getOccupancy,
	getOccupancyHistory,
	getOccupancyMax,
	getOccupancyMin
} from '$lib/scripts/db/occupancy.js';
import { error } from '@sveltejs/kit';

export async function load() {
	const occupancy = await getOccupancy('mensa-academica-01');
	const max = await getOccupancyMax('mensa-academica-01', 31556952);
	const min = await getOccupancyMin('mensa-academica-01', 31556952);
	const history = await getOccupancyHistory('mensa-academica-01', 604800);
	const averagedHistory = await getAveragedOccupancyHistory('mensa-academica-01', 604800, 60);

	if (min == null || max == null || occupancy == null) {
		error(505, "Couldn't fetch data from db");
	}

	return { occupancy, min, max, history, averagedHistory };
}
