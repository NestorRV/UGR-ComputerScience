etiquetas(tree(X), [X]).

etiquetas(tree(RAIZ, A1, A2), [RAIZ|SALIDA]) :- 
    etiquetas(A1, Y),
    etiquetas(A2, Z),
    append(Y, Z, SALIDA).

% ? etiquetas(tree(1, tree(2, tree(6), tree(7)), tree(3, tree(4, tree(8, tree(9), tree(10)), tree(9)), tree(5))), X).
% [1, 2, 6, 7, 3, 4, 8, 9, 10, 9, 5]