connected(1,2).
connected(2,3).
connected(3,4).

connected(1,5).
connected(5,4).

path(X, Y, [X,Y]) :- connected(X, Y).
path(X, Y, [X|T]) :- connected(X, Z), path(Z, Y, T).

distancia(X, Y, SALIDA) :- findall(Z, path(X, Y, Z), L), 
    				  maplist(length, L, DISTANCIAS),
					  min_list(DISTANCIAS, MINIMO),
    				  SALIDA is MINIMO-1.

% ? distancia(1, 4, X).
% 2