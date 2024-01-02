thempt([], X, [X]).
thempt([H|T], X, [H|R]) :- thempt(T, X, R).