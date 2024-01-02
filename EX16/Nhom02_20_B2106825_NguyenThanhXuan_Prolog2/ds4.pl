hoanvi(X, Y, [X, Y|T], [Y, X|T]).
hoanvi(X, Y, [H|T], [H|T1]) :- hoanvi(X, Y, T, T1).
