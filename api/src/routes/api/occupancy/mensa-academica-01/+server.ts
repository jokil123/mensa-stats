import { error, type RequestEvent } from '@sveltejs/kit';

export async function POST({ request }: RequestEvent) {
	console.log(request.headers);

	if (request.headers.get('Authorization') != 'Bearer 1234') {
		error(401, 'You are not authorized for this stupid fucker!');
	}

	const devices = await request.body;

	console.log(devices);

	return new Response('Number Received', {
		headers: {
			'Content-Type': 'application/json'
		}
	});
}
