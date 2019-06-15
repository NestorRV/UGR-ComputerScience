(define (domain LosMundosDeBelkan)
    (:requirements :strips :typing :fluents)
    (:types protagonista zona objeto personaje orientacion)
    
    (:functions
        (coste)
        (distancia ?x ?y - object)
    )

    (:predicates   
        (esta ?x - protagonista ?y - zona)
        (esta_obj ?x - objeto ?y - zona)
        (esta_per ?x - personaje ?y - zona)
        (orien_prota ?x - orientacion)
        (conectada ?x - zona ?y - zona ?or - orientacion)
        (cogido ?x - objeto)
        (tiene ?x - objeto ?y - personaje)
        (manovacia)
    )


    (:action girarDerecha
        :parameters (?or_prota - orientacion)
        :precondition (and (orien_prota ?or_prota))
        :effect 
        (and
            (when (and (orien_prota norte))
                (and (orien_prota este) (not (orien_prota norte)))
            )
    
            (when (and (orien_prota este))
                (and (orien_prota sur) (not (orien_prota este)))
            )
    
            (when (and (orien_prota sur))
                (and (orien_prota oeste) (not (orien_prota sur)))
            )
    
            (when (and (orien_prota oeste))
                (and (orien_prota norte) (not (orien_prota oeste)))
            )
        )
    )

    (:action girarIzquierda
        :parameters (?or_prota - orientacion)
        :precondition (and (orien_prota ?or_prota))
        :effect 
        (and
            (when (and (orien_prota norte))
                (and (orien_prota oeste) (not (orien_prota norte)))
            )
    
            (when (and (orien_prota oeste))
                (and (orien_prota sur) (not (orien_prota oeste)))
            )
    
            (when (and (orien_prota sur))
                (and (orien_prota este) (not (orien_prota sur)))
            )
    
            (when (and (orien_prota este))
                (and (orien_prota norte) (not (orien_prota este)))
            )
        )
    )

    (:action moverProta
        :parameters (?p - protagonista ?z1 - zona ?z2 - zona ?or - orientacion)
        :precondition (and (not (esta ?p ?z2)) (esta ?p ?z1) (conectada ?z1 ?z2 ?or) (orien_prota ?or))
        :effect (and (not (esta ?p ?z1)) (esta ?p ?z2) (increase (coste) (distancia ?z1 ?z2)))
    )


    (:action cogerObj
        :parameters (?p - protagonista ?obj - objeto ?z - zona)
        :precondition (and (esta ?p ?z) (esta_obj ?obj ?z) (manovacia))
        :effect (and (not (manovacia)) (cogido ?obj) (not (esta_obj ?obj ?z)))
    )

    (:action dejarObj
        :parameters (?p - protagonista ?obj - objeto ?z - zona)
        :precondition (and (esta ?p ?z) (cogido ?obj))
        :effect (and (not (cogido ?obj)) (esta_obj ?obj ?z) (manovacia))
    )

    (:action entregarObj
        :parameters (?p - protagonista ?obj - objeto ?z - zona ?per - personaje)
        :precondition (and (not (tiene ?obj ?per)) (esta ?p ?z) (esta_per ?per ?z) (cogido ?obj))
        :effect (and (not (cogido ?obj)) (tiene ?obj ?per) (manovacia))
    )
)