import { getOccupancy, getOccupancyHistory, getOccupancyMax } from '$lib/db/occupancy.js';
import { error } from '@sveltejs/kit';

export async function load() {
	const occupancy = await getOccupancy('mensa-academica-01');
	const max = await getOccupancyMax('mensa-academica-01', 31556952);
	const history = await getOccupancyHistory('mensa-academica-01', 604800);

	if (max == null || occupancy == null) {
		error(505, "Couldn't fetch data from db");
	}

	return { occupancy, max, history };
}
