profundidad(tree(_), 0).

profundidad(tree(_, A1, A2), SALIDA) :- 
    profundidad(A1, Y),
    profundidad(A2, Z),
    SALIDA is 1+max(Y,Z).

% ? profundidad(tree(1, tree(2, tree(6), tree(7)), tree(3, tree(4, tree(8, tree(9), tree(10)), tree(9)), tree(5))), X).
% 4