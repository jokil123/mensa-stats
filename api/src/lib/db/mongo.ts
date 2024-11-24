import { MongoClient } from 'mongodb';
// import 'dotenv/config';
// import { DB_URL } from '$env/dynamic/private';

// Default value because otherwise build system breaks lol
let client: MongoClient = new MongoClient('mongodb://domain.com');

export async function start_mongo() {
	console.log('Starting mongo...');
	if (!process.env.DB_URL) {
		throw new Error('DB_URL environment variable must be set!');
	}

	client = new MongoClient(process.env.DB_URL);
	await client.connect();
	return client;
}

export default client.db();
