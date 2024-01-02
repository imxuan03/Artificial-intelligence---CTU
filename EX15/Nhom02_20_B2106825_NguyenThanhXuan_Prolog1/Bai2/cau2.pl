nguoi(marcus).
pompeian(marcus).
lama(X) :- pompeian(X).
lanhchua(ceasar).
amsat(X,Y) :- lama(X),khongtrungthanh(X,Y),lanhchua(Y).
khongtrungthanh(marcus,ceasar).