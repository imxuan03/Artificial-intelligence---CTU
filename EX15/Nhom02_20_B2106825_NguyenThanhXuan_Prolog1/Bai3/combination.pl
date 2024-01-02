combination(_, 0, []).
combination([X|T], K, [X|Comb]) :- K > 0, K1 is K - 1, combination(T, K1, Comb).
combination([_|T], K, Comb) :- K > 0, combination(T, K, Comb).