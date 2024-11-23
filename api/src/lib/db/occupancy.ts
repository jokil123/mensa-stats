import mongo from './mongo';

export async function saveOccupancyEntry(device: string, occupancy: number) {
	const collection = mongo.collection('occupancy');

	const doc = {
		timestamp: new Date(),
		device,
		occupancy
	};

	await collection.insertOne(doc);
}

export async function getOccupancy(): Promise<number> {
	const collection = mongo.collection('occupancy');

	const mostRecent = await collection.find().sort({ timestamp: -1 }).limit(1).toArray();

	return mostRecent[0].occupancy;
}
