// lerps from 0-1 (a-b)
export function lerp(a: number, b: number, t: number) {
	return a * (1 - t) + b * t;
}

export function roundN(num: number, n: number) {
	const m = Math.pow(10, n);
	return Math.round(num * m) / m;
}
