import { getOccupancy } from '$lib/db/occupancy.js';

export async function load() {
	const occupancy = await getOccupancy();
	return { occupancy };
}
