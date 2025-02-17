import { getOccupancy } from '$lib/scripts/db/occupancy';
import { error, type RequestEvent } from '@sveltejs/kit';

// This function will return 200 OK with no content if the latest datapoint is less than 10 minutes old
// Otherwise it will return 503 Service Unavailable
export async function GET({ request }: RequestEvent) {
	let collectorId = request.url.split('/')[5];

	let last = await getOccupancy(collectorId);
	if (!last) {
		error(503, 'No data available');
	}

	let now = Date.now();

	if (now - last.timestamp.getTime() > 10 * 60 * 1000) {
		let minutes = (now - last.timestamp.getTime()) / (1000 * 60);

		error(503, `Service unavailable, last data point is ${minutes} minutes old`);
	}

	return new Response(`collector ${collectorId} is alive`, {
		headers: {
			'Content-Type': 'text/plain'
		}
	});
}
