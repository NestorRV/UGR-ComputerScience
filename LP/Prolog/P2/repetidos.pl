pertenece(X, [X|_]).
pertenece(X, [_|T]) :- pertenece(X, T).

borrar_repetidos([], X, X).

borrar_repetidos([H|T], ACUMULADOR, SALIDA) :- pertenece(H, ACUMULADOR), borrar_repetidos(T, ACUMULADOR, SALIDA).

borrar_repetidos([H|T], ACUMULADOR, SALIDA) :- not(pertenece(H, ACUMULADOR)), append(ACUMULADOR, [H], NEW_ACUMULADOR),  borrar_repetidos(T, NEW_ACUMULADOR, SALIDA).

% ? borrar_repetidos([1, 2, 3, 1, 2, 3], [], X).
% [1, 2, 3]
% ? borrar_repetidos([1, 2, 3], [], X).
% [1, 2, 3]