import { authorizeDevice } from '$lib/server/db/authorize';
import { saveOccupancyEntry } from '$lib/server/db/occupancy';
import { error, type RequestEvent } from '@sveltejs/kit';
import { Ajv } from 'ajv';

type occupancyJSON = {
	device: string;
	token: string;
	occupancy: number;
};

const validateJSON = new Ajv().compile({
	type: 'object',
	properties: {
		device: { type: 'string' },
		token: { type: 'string' },
		occupancy: { type: 'number' }
	},
	required: ['device', 'token', 'occupancy'],
	additionalProperties: false
});

export async function POST({ request }: RequestEvent) {
	let json: occupancyJSON;
	try {
		json = await request.json();
		// eslint-disable-next-line @typescript-eslint/no-unused-vars
	} catch (e) {
		error(400, 'Non JSON request!');
	}

	if (!validateJSON(json)) {
		error(400, 'Malformed data!');
	}

	if (!(await authorizeDevice(json.device, json.token))) {
		error(401, 'You are not authorized for this, nice try though lol');
	}

	if (json.occupancy < 0) {
		error(400, 'Occupancy may not be negative!');
	}

	await saveOccupancyEntry(json.device, json.occupancy);

	console.log(`collector "${json.device}" measured ${json.occupancy} devices`);

	return new Response('Number received', {
		headers: {
			'Content-Type': 'application/json'
		}
	});
}
