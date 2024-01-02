pt_nho_hon([], _, []).
pt_nho_hon([H|T], N, [H|L1]) :- H < N, pt_nho_hon(T, N, L1).
pt_nho_hon([H|T], N, L1) :- H >= N, pt_nho_hon(T, N, L1).
