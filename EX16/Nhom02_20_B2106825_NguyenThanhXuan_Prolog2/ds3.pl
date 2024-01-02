ptvtle([], []).
ptvtle([X], [X]).
ptvtle([_, Y | T], [Y | L]) :- ptvtle(T, L).
