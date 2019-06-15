connected(1,2).
connected(1,3).
connected(2,4).
connected(3,4).

connected(1,5).
connected(1,6).

connected(5,4).
connected(6,4).

path(X, Y, [X|T]) :- connected(X, Z), path(Z, Y, T), !.
path(X, Y, [X,Y]) :- connected(X,Y).

% ? path(1, 4, X).
% [1, 2, 4]