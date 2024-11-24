import mongo from './mongo';

// Saves an occupancy entry to the db
export async function saveOccupancyEntry(device: string, occupancy: number) {
	const collection = mongo().collection('occupancy');

	const doc = {
		timestamp: new Date(),
		metadata: {
			device
		},
		occupancy
	};

	await collection.insertOne(doc);
}

// Gets the most recent occupancy entry by device
export async function getOccupancy(device: string): Promise<number | null> {
	const collection = mongo().collection('occupancy');

	const mostRecent = await collection
		.find()
		.filter({ metadata: { device: device } })
		.sort({ timestamp: -1 })
		.limit(1)
		.toArray();

	if (mostRecent.length != 1) {
		return null;
	}

	return mostRecent[0].occupancy;
}

// Gets the maximum Occupancy during the last s seconds
export async function getOccupancyMax(device: string, s: number): Promise<number | null> {
	const now = new Date();

	const max = await mongo()
		.collection('occupancy')
		.aggregate([
			{
				$match: {
					timestamp: { $gte: new Date(now.getTime() - s * 1000) },
					'metadata.device': { $eq: device }
				}
			},
			{
				$group: {
					_id: null,
					maxValue: { $max: '$occupancy' }
				}
			}
		])
		.toArray();

	if (max.length != 1) {
		// if there is no maximum return the last entry
		console.log("Couldn't get max, using last value");
		return await getOccupancy(device);
	}

	return max[0].maxValue as number;
}

// Gets the minimum Occupancy during the last s seconds
export async function getOccupancyMin(device: string, s: number): Promise<number | null> {
	const now = new Date();

	const min = await mongo()
		.collection('occupancy')
		.aggregate([
			{
				$match: {
					timestamp: { $gte: new Date(now.getTime() - s * 1000) },
					'metadata.device': { $eq: device }
				}
			},
			{
				$group: {
					_id: null,
					maxValue: { $min: '$occupancy' }
				}
			}
		])
		.toArray();

	if (min.length != 1) {
		// if there is no maximum return the last entry
		console.log("Couldn't get min, using last value");
		return await getOccupancy(device);
	}

	return min[0].maxValue as number;
}

export type HistoryPoint = {
	timestamp: Date;
	occupancy: number;
};

// gets all occupancy datapoints of the last s seconds
export async function getOccupancyHistory(device: string, s: number): Promise<HistoryPoint[]> {
	const now = new Date();

	const historyDocs = await mongo()
		.collection('occupancy')
		.aggregate([
			{
				$match: {
					timestamp: { $gte: new Date(now.getTime() - s * 1000) },
					'metadata.device': { $eq: device }
				}
			}
		])
		.toArray();

	const historyData = historyDocs.map((d) => {
		return {
			timestamp: d.timestamp,
			occupancy: d.occupancy
		};
	});

	return historyData;
}
