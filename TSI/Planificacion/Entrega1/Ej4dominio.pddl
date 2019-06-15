(define (domain LosMundosDeBelkan)
    (:requirements :strips :typing :fluents)
    (:types protagonista zona objeto personaje orientacion mochila tipo)
    
    (:functions
        (coste)
        (distancia ?x ?y - object)
        (puntos)
        (cantidad_puntos ?x - objeto ?y - personaje)
    )

    (:predicates   
        (esta ?x - protagonista ?y - zona)
        (esta_obj ?x - objeto ?y - zona)
        (esta_per ?x - personaje ?y - zona)
        (orien_prota ?x - orientacion)
        (conectada ?x - zona ?y - zona ?or - orientacion)
        (cogido ?x - objeto)
        (tiene ?x - objeto ?y - personaje)
        (contiene ?x - objeto)
        (tipo_zona ?x - zona ?y - tipo)
        (util ?x - objeto ?y - tipo)
        (libre ?x - tipo)
        (manovacia)
        (mochilavacia)
    )

    (:action moverProta
        :parameters (?p - protagonista ?z1 - zona ?z2 - zona ?or - orientacion ?t - tipo ?obj - objeto)
        :precondition (and (not (esta ?p ?z2)) (esta ?p ?z1) (conectada ?z1 ?z2 ?or) (orien_prota ?or) (tipo_zona ?z2 ?t) (or (libre ?t) (and (or (cogido ?obj) (contiene ?obj)) (util ?obj ?t))))
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
        ; :precondition (and (not (tiene ?obj ?per)) (esta ?p ?z) (esta_per ?per ?z) (cogido ?obj) (not (cogido ZAPATILLAS)) (not (cogido BIKINI)))
        ; He tenido que quitar la precondicion de que el personaje no tenga el objeto, porque si ya lo tiene, no se le puede dar y no se podría alcanzar
        ; los puntos necesarios
        :precondition (and (esta ?p ?z) (esta_per ?per ?z) (cogido ?obj) (not (cogido ZAPATILLAS)) (not (cogido BIKINI)))
        :effect (and (not (cogido ?obj)) (tiene ?obj ?per) (manovacia) (increase (puntos) (cantidad_puntos ?obj ?per)))
    )

    (:action guardarObj
        :parameters (?p - protagonista ?obj - objeto)
        :precondition (and (cogido ?obj) (mochilavacia))
        :effect (and (contiene ?obj) (not (cogido ?obj)) (not (mochilavacia)) (manovacia))
    )

    (:action sacarObj
        :parameters (?p - protagonista ?obj - objeto)
        :precondition (and (contiene ?obj) (manovacia))
        :effect (and (cogido ?obj) (not (contiene ?obj)) (not (manovacia)) (mochilavacia))
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
)