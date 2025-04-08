import { MongoClient } from 'mongodb';
import { env } from '$env/dynamic/private';

// Default value because otherwise build system breaks lol
let client: MongoClient;

export async function start_mongo() {
	console.log('Starting mongo...');
	if (!env.DB_URL) {
		throw new Error('DB_URL environment variable must be set!');
	}

	client = new MongoClient(env.DB_URL);
	await client.connect();
	return client;
}

export default () => {
	if (!client) {
		throw new Error('Got fetched db before initialization');
	}

	return client.db();
};
