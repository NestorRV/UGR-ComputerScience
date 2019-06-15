
-- Nestor Rodriguez Vico

-- 1. Define una función 'raiz' que tome por argumento dos números: el primero un
-- número al que deseamos calcular su raíz cuadrada; y el segundo un margen de
-- error. Para ello aplicar repetidamente la expresión r+nr/2, hasta que dos de
-- los rs consecutivos se diferencien en menos del margen de error deseado.

raiz r n error = if abs ((((r + (n/r)) / 2)) - r) < error then r else raiz ((r + (n/r)) / 2) n error
-- raiz 25 25 0.000001

-- 2. Define una función 'corta', que dada una lista y un elemento de esa lista,
-- corte a la lista en dos partes, la primera conteniendo todos los elementos
-- hasta el elemento dado, y la segunda el resto.


corta lista elemento salida
                            | y == elemento = (salida++[y], ys)
                            | otherwise = corta ys elemento (salida++[y])
                            where (y:ys) = lista
-- corta [0, 1, 2, 1, 1, 3, 5] 2 []

-- 3. Define un tipo de dato árbol binario, y una función 'espejo', que de la vuelta
-- a un árbol binario dado en cada uno de sus niveles.

data BinTree a = Empty | Nodo a (BinTree a) (BinTree a) deriving (Show, Eq)

mirror Empty = Empty
mirror (Nodo a left right) = (Nodo a (mirror right) (mirror left))

-- let myBinTree = Nodo 1 (Nodo 2 Empty Empty) (Nodo 3 Empty Empty)
-- show myBinTree
-- mirror myBinTree

-- 4. Define un tipo de dato árbol general con hojas y nodos etiquetados. Define
-- una función que tome por argumento un árbol general y devuelva una lista con
-- todas las etiquetas del árbol.

data Tree a = Empty_ | Nodo_ a [Tree a] deriving (Show, Eq)

etiquetas Empty_ = []
etiquetas (Nodo_ a []) = [a]
etiquetas (Nodo_ a (x:xs)) = (etiquetas (x))++(etiquetas (Nodo_ a xs))


-- Nodo_ 1 [Nodo_ 2 [Nodo_ 6 []], Nodo_ 3 [], Nodo_ 4 [], Nodo_ 5 []]

-- 5. Escribe una función polimórfica 'profundidad' que
-- encuentre la profundidad máxima de un árbol general.

profundidad Empty_ = 0
profundidad (Nodo_ a []) = 0
profundidad (Nodo_ _ list) = 1 + maximum (map profundidad list)

-- profundidad (Nodo_ 1 [Nodo_ 2 [Nodo_ 6 []], Nodo_ 3 [], Nodo_ 4 [], Nodo_ 5 []])

-- 6. Escribe una función 'retuerce' que crea la imagen
-- especular de un árbol general dado.

espejo_general Empty_ = Empty_
espejo_general (Nodo_ a list) = (Nodo_ a (map espejo_general (reverse list)))

-- espejo_general (Nodo_ 1 [Nodo_ 2 [Nodo_ 6 []], Nodo_ 3 [], Nodo_ 4 [], Nodo_ 5 []])
