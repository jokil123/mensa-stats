import {
	getAveragedOccupancyHistory,
	getOccupancy,
	getOccupancyHistory,
	getOccupancyMax,
	getOccupancyMin
} from '$lib/server/db/occupancy.js';
import { error } from '@sveltejs/kit';

export async function load({ params }) {
	const device = params.slug.split('/').pop();

	if (device == undefined) {
		error(404, 'Not Found');
	}

	const occupancy = await getOccupancy(device);
	const max = await getOccupancyMax(device, 31556952);
	const min = await getOccupancyMin(device, 31556952);
	const history = await getOccupancyHistory(device, 604800);
	const averagedHistory = await getAveragedOccupancyHistory(device, 604800, 60);

	if (!occupancy || !min || !max || !history || !averagedHistory) {
		error(505, "Couldn't fetch data from db");
	}

	return { occupancy, min, max, history, averagedHistory };
}
