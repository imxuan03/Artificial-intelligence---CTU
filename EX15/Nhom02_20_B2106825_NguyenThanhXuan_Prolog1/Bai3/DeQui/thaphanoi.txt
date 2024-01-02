move(1, A, B, _) :- print(A), print('-->'),print(B),nl.
move(N, A, B, C) :- N1 is N-1,
		    move(N1,A,C,B),
		    move(1,A,B,C), move(N1,C,B,A).