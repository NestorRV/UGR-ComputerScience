% working_directory(_, './Users/nestor/Dropbox/UGR/4/1/LP/Practicas/Prolog').
% [gegalkine].

:-op(1, fy, no).
:-op(500, yfx, :*).
:-op(501, yfx, :+).
:-op(900, yfx, =>).

gegalkine(X, X):- atom(X), !.
gegalkine(no A, SALIDA):- gegalkine(A, X), SALIDA = uno :+ X.
gegalkine(A => B, SALIDA):- gegalkine(A, RES_A),
    gegalkine(B, RES_B),
    SALIDA = uno :+ RES_A :+ RES_A :* RES_B.

% 1. Dado un polinomio, define una función que exprese dicho polinomio como suma
% de distrib (producto de variables). Para ello tendrá que aplicarse la
% propiedad distributiva.

distrib(X :* (Y :+ Z), S) :- distrib(X:*Y, PRIM), distrib(X:*Z, SEG), S = PRIM :+ SEG, !.
distrib((X :+ Y) :* Z, S) :- distrib(X:*Z, PRIM), distrib(Y:*Z, SEG), S = PRIM :+ SEG, !.
distrib(X :* Y, S) :- distrib(X, DX),
    distrib(Y, DY),
    (X == DX, Y == DY -> S = DX :* DY; distrib(DX :* DY, RESULT), S = RESULT).

distrib(X :+ Y, S) :- distrib(X, PRIM), distrib(Y, SEG), S = PRIM :+ SEG, !.
distrib(X, S) :- S = X.
distrib(uno, S) :- S = uno.

% distrib((1:+b) :* c, S).

% 2. Escribe una función que dada una suma de polinomios, de una lista con los
% sumandos. Para esta función escribe una inversa: dada una lista de polinomios,
% que construya la suma de los elementos.

suma2list(A :+ B, S) :- suma2list(A, PRIM),
    suma2list(B, SEG),
    append(PRIM, SEG, S), !.
suma2list(A :* B, S) :- S = [A :* B], !.
suma2list(X, S) :- S = [X].
suma2list(uno, S) :- S = [uno].

% suma2list(1:*b:+(1:*b:+(a:*b)):+(1:*b:+(a:*b)), X).

list2suma([], S) :- S = cero.
list2suma([X], S) :- S = X, !.
list2suma([H|T], S) :- list2suma(T, SDOS), S = H :+ SDOS.

% list2suma([a, b, c, d], X).

% 3. Haz lo mismo con el producto.

prod2list(uno, S) :- S = [].
prod2list(A :* B, S) :- prod2list(A, PRIM),
    prod2list(B, SEG),
    append(PRIM, SEG, S), !.
prod2list(A :+ B, S) :- S = [A :+ B], !.
prod2list(X, S) :- S = [X].

list2prod([], S) :- S = uno.
list2prod([X], S) :- S = X, !.
list2prod([H|T], S) :- list2prod(T, SDOS), S = H :* SDOS.

% 4. Escribe una función que elimine elementos repetidos de una lista.
borrarRep(LIST, S) :- sort(LIST, R), S = R.

% borrarRep([a, c, c, b, a], X).

% 5. Escribe una función que elimine los elementos que aparezcan un número par
% de veces en una lista, y que mantenga una copia de los que aperecen un número
% impar. Por ejemplo, para [a,a,a,b,b] devolvería [a].

even(0).
even(X) :- X > 0, X1 is X - 1, odd(X1), !.
even(X) :- X < 0, X1 is X + 1, odd(X1), !.

odd(1).
odd(X) :- X > 0, X1 is X - 1, even(X1), !.
odd(X) :- X < 0, X1 is X + 1, even(X1), !.

count([], _, 0).
count([H|T], Num, X) :- dif(Num,H), count(T, Num, X).
count([H|T], Num, X) :- Num = H, count(T, Num, X1), X is X1 + 1, !.

% count([uno, uno, a, b, uno], uno, X).

count_occurrences(LISTZ, S):- findall([X,L], (bagof(true,member(X,LISTZ),Xs), length(Xs,L)), S).

% count_occurrences([1, 1, 2, 3], X).
% X = [[1, 2], [2, 1], [3, 1]]

proc([], X, X).
proc([[H|T]|TAIL], ACC, X) :- odd(T), append(ACC, [H], NEW_ACC), proc(TAIL, NEW_ACC, X), !.
proc([[_|T]|TAIL], ACC, X) :- even(T), proc(TAIL, ACC, X), !.

borrarPar(LISTA, X) :- count_occurrences(LISTA, OCC), proc(OCC, [], X).

% 6. Con todos estos ingredientes escribe un simplificador de funciones
% polinomiales con coeficientes en Z2, para así poder decidir si una
% proposición es una tautología.


tautologia_listas(X, S):-
    gegalkine(X, GEGAL),
    distrib(GEGAL, DISTRIB),
    suma2list(DISTRIB, LISTASUMAS),
    maplist(prod2list, LISTASUMAS, LISTAPRODS),
    maplist(borrarRep, LISTAPRODS, LISTAPRODS_SINREPES),
    maplist(borrarPar, LISTAPRODS_SINREPES, SINPARES),
    borrarPar(SINPARES, SINPARES_GENERAL),
    S = SINPARES_GENERAL, !.

convertir(X, S) :-
    maplist(list2prod, X, AUX),
    list2suma(AUX, RESULT),
    S = RESULT.

tautologia(X, S) :- tautologia_listas(X, AUX),
    convertir(AUX, RESULT),
    S = RESULT.

% tautologia(a => (b => a), X).
% tautologia((a => b) => (no b => no a), X).
