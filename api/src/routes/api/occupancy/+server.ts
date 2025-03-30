import { authorizeDevice } from '$lib/scripts/server/db/authorize';
import { saveOccupancyEntry } from '$lib/scripts/server/db/occupancy';
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
		occupancy: { type: 'integer' }
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

	// console.log(json);

	if (!(await authorizeDevice(json.device, json.token))) {
		error(401, 'You are not authorized for this, nice try though lol');
	}

	await saveOccupancyEntry(json.device, json.occupancy);

	console.log(`Measured ${json.occupancy} devices`);

	return new Response('Number Received', {
		headers: {
			'Content-Type': 'application/json'
		}
	});
}
