import mongo from './mongo';

export async function authorizeDevice(device: string, token: string): Promise<boolean> {
	const documentExists = await mongo().collection('devices').findOne({
		device: device,
		token: token // Check if the token exists in the array
	});

	return documentExists != null;
}
