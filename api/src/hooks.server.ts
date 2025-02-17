import { start_mongo } from '$lib/scripts/db/mongo';
import 'dotenv/config';

try {
	await start_mongo();
	console.log('Mongo started!');
} catch (e) {
	console.error(e);
}
