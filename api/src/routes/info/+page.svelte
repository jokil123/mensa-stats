<script>
	import Footer from '$lib/components/Footer.svelte';
	import MarginBox from '$lib/components/MarginBox.svelte';
</script>

<MarginBox>
	<a href="/"><h1 class="mb-8 text-5xl font-bold text-white">Mensa Stats Info</h1></a>
	<p>
		Die Mensa burger sind ja vieleicht ganz nice, jedoch ist die Schlange oft etwas lange für meinen
		Geschmack. Inpiriert von den <a class="text-blue-400" href="https://mensa.liste.party/"
			>high-tech Lösungen anderer Unis,
		</a>
		habe ich mir kurzerhand gedacht "Warum nicht auch bei uns? Ist ja eigentlich ganz einfach". Tja,
		einfach wars' ja nicht, aber immerhin spare ich mir jetzt das ewige Schlangestehen.
	</p>
	<br />
	<p>
		Mensa stats misst wie voll die Mensa ist, indem die Anzahl an Bluetooth Geräten gezählt wird.
		Ist zwar nicht so genau, aber gut genug 🤷‍♂️. Daran kann ich leider nichts ändern solange die
		RWTH, die Eduroam Daten nicht veröfftenlicht. Persönliche Daten wie MAC- und IP-Adresse werden
		natürlich nicht gespeichert. Die Daten werden ausschließlich für diese Webseite verwendet yada
		yada bla bla (Please don't sue me 🥲)
	</p>
	<br />
	<p>
		Falls ihr mir das nicht glauben wollt, könnt ihr aber auch gerne euren eigenen Audit starten, da
		<a class="text-blue-400" href="https://github.com/jokil123/mensa-stats"
			>das ganze Projekt auf meinem GitHub</a
		>
		zu finden ist. Auf eigene Gefahr besuchen, mein Code ist dafür bekannt spontane Aneurismen zu verursachen.
		Falls ihr weitere Ideen habt, was man cooles mit den Daten machen kann, gerne einfach ne Email schreiben!
	</p>
	<br />
	<p class="mb-10 font-bold">Naja, made with Hate and Spite in Svelte & C++ {'<3'}</p>
</MarginBox>

<Footer />
