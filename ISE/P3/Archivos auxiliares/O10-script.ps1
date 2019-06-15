$suma=0

for($i=0; $i -le 100; $i++){
	If ($i % 2 -ne 0) {
		$i
		$suma += $i
	}
}

"La suma es: " + $suma
