import type { HistoryPoint } from '$lib/global/historyPoint';
import mongo from './mongo';

// Saves an occupancy entry to the db
export async function saveOccupancyEntry(device: string, occupancy: number) {
	const collection = mongo().collection('occupancy');

	let dateBucket = new Date();
	dateBucket.setUTCHours(0, 0, 0, 0);

	const doc = {
		timestamp: new Date(),
		metadata: {
			device,
			date: dateBucket
		},
		occupancy
	};

	await collection.insertOne(doc);
}

// Gets the most recent occupancy entry by device
export async function getOccupancy(device: string): Promise<HistoryPoint | null> {
	const collection = mongo().collection('occupancy');

	const mostRecent = await collection
		.find()
		.filter({ 'metadata.device': device })
		.sort({ timestamp: -1 })
		.limit(1)
		.toArray();

	if (mostRecent.length != 1) {
		return null;
	}

	return {
		timestamp: mostRecent[0].timestamp,
		occupancy: mostRecent[0].occupancy
	};
}

// Gets the maximum Occupancy during the last s seconds
export async function getOccupancyMax(device: string, s: number): Promise<HistoryPoint | null> {
	const now = new Date();

	const max = await mongo()
		.collection('occupancy')
		.find()
		.filter({
			timestamp: { $gte: new Date(now.getTime() - s * 1000) },
			'metadata.device': device
		})
		.sort({ occupancy: -1 })
		.limit(1)
		.toArray();

	if (max.length != 1) {
		// if there is no maximum return the last entry
		console.log("Couldn't get max, using last value");
		return await getOccupancy(device);
	}

	return {
		timestamp: max[0].timestamp,
		occupancy: max[0].occupancy
	};
}

// Gets the minimum Occupancy during the last s seconds
export async function getOccupancyMin(device: string, s: number): Promise<HistoryPoint | null> {
	const now = new Date();

	const min = await mongo()
		.collection('occupancy')
		.find()
		.filter({
			timestamp: { $gte: new Date(now.getTime() - s * 1000) },
			'metadata.device': device
		})
		.sort({ occupancy: 1 })
		.limit(1)
		.toArray();

	if (min.length != 1) {
		// if there is no maximum return the last entry
		console.log("Couldn't get min, using last value");
		return await getOccupancy(device);
	}

	return {
		timestamp: min[0].timestamp,
		occupancy: min[0].occupancy
	};
}

// gets all occupancy datapoints of the last s seconds and averages data over binSize minutes
export async function getAveragedOccupancyHistory(
	device: string,
	s: number,
	binSize: number
): Promise<HistoryPoint[]> {
	const now = new Date();

	const averagedHistoryDocs = await mongo()
		.collection('occupancy')
		.aggregate([
			{
				$match: {
					timestamp: { $gte: new Date(now.getTime() - s * 1000) },
					'metadata.device': device
				}
			},
			{
				$sort: { timestamp: 1 }
			},
			{
				$group: {
					_id: {
						$dateTrunc: {
							// Truncate timestamp to the hour
							date: '$timestamp',
							unit: 'minute',
							binSize: binSize // Optional: If you want to group by, say, 2-hour intervals, set binSize: 2
						}
					},
					averageOccupancy: { $avg: '$occupancy' }
				}
			},
			{
				$project: {
					_id: 0, // Exclude _id
					timestamp: '$_id', // Rename _id to timestamp for clarity
					averageOccupancy: 1,
					medianValue: 1
				}
			}
		])
		.toArray();

	const averagedHistoryData = averagedHistoryDocs.map((d) => {
		return {
			timestamp: d.timestamp,
			occupancy: d.averageOccupancy
		};
	});

	// console.log(averagedHistoryData);
	return averagedHistoryData;
}

// gets all occupancy datapoints of the last s seconds
export async function getOccupancyHistory(device: string, s: number): Promise<HistoryPoint[]> {
	const now = new Date();

	const historyDocs = await mongo()
		.collection('occupancy')
		.aggregate([
			{
				$match: {
					timestamp: { $gte: new Date(now.getTime() - s * 1000) },
					'metadata.device': device
				}
			},
			{
				$sort: { timestamp: 1 }
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
