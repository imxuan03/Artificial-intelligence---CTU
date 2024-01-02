(define (domain strips-sliding-tile)

    (:requirements :strips)

    (:predicates (tile ?x) (position ?x) (at ?t ?x ?y) (blank ?x ?y) (inc ?p ?pp) (dec ?p ?pp))

    (:action move-up
        :parameters (?ex ?ey ?t ?tx)
        :precondition (and (tile ?t) (position ?ex) (position ?ey) (position ?tx) (dec ?ex ?tx) (blank ?ex ?ey) (at ?t ?tx ?ey))
        :effect (and (not (blank ?ex ?ey)) (not (at ?t ?tx ?ey)) (blank ?tx ?ey) (at ?t ?ex ?ey))
    )
    
    (:action move-down
        :parameters (?ex ?ey ?t ?tx)
        :precondition (and (tile ?t) (position ?ex) (position ?ey) (position ?tx) (inc ?ex ?tx) (blank ?ex ?ey) (at ?t ?tx ?ey))
        :effect (and (not (blank ?ex ?ey)) (not (at ?t ?tx ?ey)) (blank ?tx ?ey) (at ?t ?ex ?ey))
    )
    
    (:action move-left
        :parameters (?ex ?ey ?t ?ty)
        :precondition (and (tile ?t) (position ?ex) (position ?ey) (position ?ty) (dec ?ey ?ty) (blank ?ex ?ey) (at ?t ?ex ?ty))
        :effect (and (not (blank ?ex ?ey)) (not (at ?t ?ex ?ty)) (blank ?ex ?ty) (at ?t ?ex ?ey))
    )
    
    (:action move-right
        :parameters (?ex ?ey ?t ?ty)
        :precondition (and (tile ?t) (position ?ex) (position ?ey) (position ?ty) (inc ?ey ?ty) (blank ?ex ?ey) (at ?t ?ex ?ty))
        :effect (and (not (blank ?ex ?ey)) (not (at ?t ?ex ?ty)) (blank ?ex ?ty) (at ?t ?ex ?ey))
    )
)