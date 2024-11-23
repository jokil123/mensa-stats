<script lang="ts">
	export let data;
</script>

<svelte:head>
	<title>Mensa Stats</title>
</svelte:head>

<h1>Mensa Stats</h1>

<h2>Momentane Belegung:</h2>

<h3>{data.occupancy}</h3>
