tong_le([], 0).
tong_le([H|T], Sum) :- H mod 2 =:= 1, tong_le(T, SubSum), Sum is H + SubSum.
tong_le([H|T], Sum) :- H mod 2 =:= 0, tong_le(T, Sum).
