men('john').
men('fred').
men('harry').

women('marry').
women('julie').
women('susan').
women('anne').

blonde('john').
blonde('julie').
blonde('susan').

dark('fred').
dark('marry').

brunette('marry').
brunette('anne').

gold('fred').
gold('julie').

rich(X) :- gold(X).

thich('john', X) :-rich(X), women(X).
thich('harry', X) :-rich(X),women(X).
thich('marry', X) :- dark(X), men(X).
thich('julie', X) :- dark(X),men(X).
thich('julie', X) :- rich(X),men(X).
thich('john', X) :- blonde(X), women(X).
thich('fred', X) :- brunette(X), women(X).

house('anne').
car('john'). 