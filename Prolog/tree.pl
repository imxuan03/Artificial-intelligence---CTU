anh('An', 'Binh').
vo('Yen', 'An').
chong('Binh', 'Hoa').
me('Hoa', 'Khang').
emgai('Khang', 'Thinh').
emtrai('Thinh','Cuong').
contrai('Cuong','Binh').
congai('Lanh', 'An').
chi('Lanh','Dung').
emgai('Hanh','Dung').
emgai('Hanh','Lanh').
congai('Dung','Yen').
cha(X,Y) :-chong(X,Z),me(Z,Y).
bac(Y,Z) :-cha(X,Z),anh(Y,X).
chu(Y,Z) :-cha(X,Z),emtrai(Y,X).
co(Y,Z) :-cha(X,Z),emgai(Y,X).
anhemruot(X,Y) :-cha(Z,X),cha(Z,Y),me(V,X),me(V,Y).
anhho(X,Z) :-contrai(X, Y),bac(Y,Z).
chiho(X,Z) :-congai(X,Y),bac(Y,Z).
emtraiho(X,Z) :-contrai(X,Y),chu(Y,Z).
emgaiho(X,Z) :-congai(X,Y),chu(Y,Z).
