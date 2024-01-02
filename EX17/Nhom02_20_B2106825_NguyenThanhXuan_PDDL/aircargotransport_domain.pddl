(define (domain air-cargo)

    (:requirements :strips)

    (:predicates
        (In ?obj ?place) (At ?obj ?place) (Cargo ?obj) (Plane ?obj) (Airport ?obj)
    )

    (:action LOAD
        :parameters (?c ?p ?a)
        :precondition (and (At ?c ?a) (At ?p ?a) (Cargo ?c) (Plane ?p) (Airport ?a))
        :effect (and (not (At ?c ?a)) (In ?c ?p))
    )
    
    (:action UNLOAD
        :parameters (?c ?p ?a)
        :precondition (and (In ?c ?p) (At ?p ?a) (Cargo ?c) (Plane ?p) (Airport ?a))
        :effect (and (not (In ?c ?p)) (At ?c ?a))
    )
    
    (:action FLY
        :parameters (?p ?from ?to)
        :precondition (and (At ?p ?from) (Plane ?p) (Airport ?from) (Airport ?to))
        :effect (and (not (At ?p ?from)) (At ?p ?to))
    )
)