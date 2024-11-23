import { start_mongo } from '$lib/db/mongo';

try {
	await start_mongo();
	console.log('Mongo started!');
} catch (e) {
	console.error(e);
}
