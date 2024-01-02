thucan('ga').
thucan('tao').
thucan(Y) :- an(X,Y), consong(X).
consong('Bill').
an('Bill', 'dauphong').
an('John', X) :- thucan(X).
an('Sue', X) :- an('Bill', X).