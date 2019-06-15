-- Nestor Rodriguez Vico
import Data.List

infixl 1 :->
infixl 6 :+
infixl 7 :*

data Proposicion = A Int | Not Proposicion | Proposicion :-> Proposicion deriving (Show,Eq)
data Polinomio = Cero | Uno | X Int | Polinomio :+ Polinomio | Polinomio :* Polinomio deriving (Show,Eq,Ord)

gegalkine :: Proposicion -> Polinomio
gegalkine (A numero) = (X numero)
gegalkine (Not p) = (Uno :+ gegalkine (p))
gegalkine (p1 :-> p2) = (Uno :+ gegalkine (p1) :+ gegalkine (p1) :* gegalkine(p2))

-- gegalkine ((Not (((A 1) :-> (A 2)))) :-> (A 3))

-- 1. Dado un polinomio, define una función que exprese dicho polinomio como suma
-- de distrib (producto de variables). Para ello tendrá que aplicarse la
-- propiedad distributiva.

distrib :: Polinomio -> Polinomio
distrib Cero = Cero
distrib Uno = Uno
distrib (X numero) = (X numero)

distrib (a :* (b :+ c)) = distrib (a :* b) :+ distrib (a :* c)
distrib ((a :+ b) :* c) = distrib (a :* c) :+ distrib (b :* c)
distrib (a :+ b) = distrib (a) :+ distrib (b)
distrib (a :* b) = if a == ma && b == mb then (ma :* mb) else distrib (ma :* mb) where ma = distrib(a)
                                                                                       mb = distrib(b)

-- distrib (((X 1):*((X 2):+(X 3))):*((X 4):+(X 5)))
-- distrib (((X 1):*((X 2):+(X 3))):*(X 4))

-- 2. Escribe una función que dada una suma de polinomios, de una lista con los
-- sumandos. Para esta función escribe una inversa: dada una lista de polinomios,
-- que construya la suma de los elementos.

suma2list :: Polinomio -> [Polinomio]
suma2list Cero = [Cero]
suma2list Uno = [Uno]
suma2list (X numero) = [X numero]
suma2list (a :* b) = [a :* b]
suma2list (a :+ b) = suma2list (a) ++ suma2list(b)

list2suma :: [Polinomio] -> Polinomio
list2suma [] = Cero
list2suma (x:xs) = if length xs == 0 then (x) else x :+ list2suma (xs)

-- 3. Haz lo mismo con el producto.

prod2list :: Polinomio -> [Polinomio]
prod2list Cero = []
prod2list Uno = []
prod2list (X numero) = [X numero]
prod2list (a :+ b) = [a :+ b]
prod2list (a :* b) = prod2list (a) ++ prod2list(b)

list2prod :: [Polinomio] -> Polinomio
list2prod [] = Uno
list2prod (x:xs) = if length xs == 0 then (x) else x :* list2prod (xs)

-- 4. Escribe una función que elimine elementos repetidos de una lista.

borrarRep lista = sort (nub lista)

-- 5. Escribe una función que elimine los elementos que aparezcan un número par
-- de veces en una lista, y que mantenga una copia de los que aperecen un número
-- impar. Por ejemplo, para [a,a,a,b,b] devolvería [a].

count x xs = (length . filter (== x)) xs

borrarPar lista = borrarRep [x | x <- lista, odd (count x lista)]

-- 6. Con todos estos ingredientes escribe un simplificador de funciones
-- polinomiales con coeficientes en Z2, para así poder decidir si una
-- proposición es una tautología.

tautologia_listas propos = borrarPar (map borrarPar (map borrarRep (map prod2list (suma2list (distrib (gegalkine (propos)))))))
convertir resultado =  list2suma (map list2prod resultado)
tautologia propos = convertir (tautologia_listas propos)

-- tautologia ((A 1) :-> ((A 2) :-> (A 1)))
-- tautologia (((A 1) :-> (A 2)) :-> (Not (A 2) :-> Not (A 1)))
