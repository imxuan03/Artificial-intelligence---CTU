noids([], L, L).
noids([H|T], L2, [H|L3]) :- noids(T, L2, L3).
