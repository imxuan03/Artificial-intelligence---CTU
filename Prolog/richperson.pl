men(john).
men(fred).
men(harry).

women(mary).
women(julie).
women(susan).
women(anne).

hair(john,blonde).
hair(fred,dark).
hair(harry,dark).
hair(julie,blonde).
hair(susan,blonde).
hair(mary,brunette).
hair(anne,brunette).

gold(fred).
gold(julie).

rich(X) :-gold(X).

like(john,X) :- rich(X),women(X).
like(harry,X) :-rich(X),women(X).
like(john,X) :-hair(X,blonde),women(X).
like(fred,X) :-hair(X,brunette),women(X).
like(mary,X) :-hair(X,dark),men(X).
like(julie,X) :-hair(X,dark),men(X).
like(julie,X) :-rich(X), men(X).
thichlannhau(X,Y) :-like(X,Y),like(Y,X).

car(john).
house(anne).