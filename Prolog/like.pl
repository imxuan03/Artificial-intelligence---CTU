thich('mary','food').
thich('mary','wine').
thich('john','wine').
thich('john','mary').
thich('john',X) :-thich('mary',X).
thich('john',X) :-thich(X,'wine').
thich('john',X) :-thich(X,X).