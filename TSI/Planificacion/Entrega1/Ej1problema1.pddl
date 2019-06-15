(define (problem Problema1)

(:domain LosMundosDeBelkan)

(:OBJECTS 
    Z1 Z2 Z3 Z4 Z5 Z6 Z7 Z8 Z9 - zona
    PROTAGONISTA - protagonista
    OSCAR MANZANA ROSA ALGORITMO ORO - objeto
    PRINCESA PRINCIPE BRUJA PROFESOR LEONARDO - personaje
    norte sur este oeste - orientacion
)

(:INIT
    ; Extremos
    (conectada Z1 Z2 este)
    (conectada Z2 Z1 oeste)
    (conectada Z2 Z3 este)
    (conectada Z3 Z2 oeste)

    (conectada Z4 Z5 este)
    (conectada Z5 Z4 oeste)
    (conectada Z5 Z6 este)
    (conectada Z6 Z5 oeste)

    (conectada Z7 Z8 este)
    (conectada Z8 Z7 oeste)
    (conectada Z8 Z9 este)
    (conectada Z9 Z8 oeste)

    (conectada Z1 Z4 sur)
    (conectada Z4 Z1 norte)
    (conectada Z4 Z7 sur)
    (conectada Z7 Z4 norte)

    (conectada Z3 Z6 sur)
    (conectada Z6 Z3 norte)
    (conectada Z6 Z9 sur)
    (conectada Z9 Z6 norte)
    
    (conectada Z2 Z5 sur)
    (conectada Z5 Z2 norte)

    ; Objetos en el mapa
    (esta_obj ORO Z4)
    (esta_obj OSCAR Z5)
    (esta_obj MANZANA Z6)
    (esta_obj ROSA Z7)
    (esta_obj ALGORITMO Z8)

    (esta_per PRINCIPE Z2)
    (esta_per LEONARDO Z3)
    (esta_per BRUJA Z9)
    (esta_per PRINCESA Z4)
    (esta_per PROFESOR Z8)
    
    (esta PROTAGONISTA Z7)
    (orien_prota norte)
    (manovacia)
)

; El objetivo va a ser entregar los objetos a los personajes
(:goal 
    (and (tiene OSCAR LEONARDO) (tiene ROSA PRINCESA) (tiene MANZANA BRUJA) (tiene ALGORITMO PROFESOR) (tiene ORO PRINCIPE)))
)