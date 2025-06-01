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
	// const history = await getOccupancyHistory(device, 604800);
	const averagedHistory = await getAveragedOccupancyHistory(device, 604800, 60);

	// console.log('occupancy: ', occupancy);
	// console.log('min: ', min);
	// console.log('max: ', max);
	// console.log('averagedHistory: ', averagedHistory);

	if (!occupancy || !min || !max || !averagedHistory) {
		error(505, "Couldn't fetch data from db, this usually indicates no data has been collected");
	}

	return { occupancy, min, max, averagedHistory };
}
