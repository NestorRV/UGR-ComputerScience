byCar(auckland,hamilton).
byCar(hamilton,raglan).
byCar(valmont,saarbruecken).
byCar(valmont,metz).

byTrain(metz,frankfurt).
byTrain(saarbruecken,frankfurt).
byTrain(metz,paris).
byTrain(saarbruecken,paris).

byPlane(frankfurt,bangkok).
byPlane(frankfurt,singapore).
byPlane(paris,losAngeles).
byPlane(bangkok,auckland).
byPlane(singapore,auckland).
byPlane(losAngeles,auckland).

travel(X, Y, go(X, Y)) :- byCar(X, Y).
travel(X, Y, go(X, Y)) :- byTrain(X, Y).
travel(X, Y, go(X, Y)) :- byPlane(X, Y).

travel(X, Y, go(X, Z, G)) :- byCar(X, Z), travel(Z, Y, G).
travel(X, Y, go(X, Z, G)) :- byTrain(X, Z), travel(Z, Y, G).
travel(X, Y, go(X, Z, G)) :- byPlane(X, Z), travel(Z, Y, G).

% ? travel(auckland, raglan, G).
% go(auckland, hamilton, go(hamilton, raglan))
% ? travel(auckland, paris, G).
% False