import { MongoClient } from 'mongodb';
import 'dotenv/config';

const client = new MongoClient(process.env.DB_URL);

export async function start_mongo() {
	console.log('Starting mongo...');
	await client.connect();
	return client;
}

export default client.db();
