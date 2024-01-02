luythua(_,0,1).
luythua(A,B,X) :- B>0, B1 is B -1, luythua(A,B1,X1), X is X1*A.
