-- Nestor Rodriguez Vico

-- 1. Escribe una función 'suma' que dados un entero y un dígito,
-- le añada al entero el dígito por la derecha.

suma entero digito = 10 * entero + digito

-- 2. Escribe una función 'resto' que calcule el resto de dividir
-- un entero por otro haciendo uso exclusivo de substracción.

resto numerador denominador = if numerador < denominador then numerador else resto (numerador - denominador) denominador

-- 3. Escribe una función 'mcd' que calcule el máximo común divisor de
-- dos enteros haciendo uso exclusivo de restas.

mcd 0 0 = error "No existe el mcd de 0 y 0."
mcd a 0 = a
mcd 0 b = b
mcd a b = if a >= b then mcd (a - b) b else mcd a (b - a)

-- 4. Escribe una función que convierta de binario a decimal y otra que
-- convierta de decimal a binario.

binToDecAux list 0 = list !! 0
binToDecAux list index = (binToDecAux list (index - 1)) + 2 ^ index * (list !! index)
binToDec list = binToDecAux (reverse list) (length list - 1)

decToBinAux number binario = if number > 0 then decToBinAux (div number 2) ([number `mod` 2]++binario) else binario
decToBin number = decToBinAux number []

-- 5. Escribe la función 'fact' que calcula el factorial de un número.

fact numero = if numero == 1 then numero else fact (numero - 1) * numero
