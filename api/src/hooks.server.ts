import { start_mongo } from '$lib/server/db/mongo';
import 'log-timestamp';

try {
	await start_mongo();
	console.log('Mongo started!');
} catch (e) {
	console.error(e);
}
