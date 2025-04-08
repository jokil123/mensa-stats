// lerps from 0-1 (a-b)
export function lerp(a: number, b: number, t: number) {
	return a * (1 - t) + b * t;
}
