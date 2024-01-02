fibo(1,1).
fibo(2,1).
fibo(N,R) :- N>2, N1 is N-1, N2 is N-2, fibo(N1,R1), fibo(N2,R2), R is R1+R2.
