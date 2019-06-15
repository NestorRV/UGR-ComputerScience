(define (problem Problema1)

(:domain LosMundosDeBelkan)

(:OBJECTS 
    Z1 Z2 Z3 Z4 Z5 Z6 Z7 Z8 Z9 Z10 Z11 Z12 Z13 Z14 Z15 Z16 Z17 Z18 Z19 Z20 Z21 Z22 Z23 Z24 Z25 - zona 
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
    (conectada Z2 Z3 oeste)
    (conectada Z3 Z4 este)
    (conectada Z4 Z3 oeste)
    (conectada Z4 Z5 este)
    (conectada Z5 Z6 oeste)

    (conectada Z5 Z10 sur)
    (conectada Z10 Z5 norte)
    (conectada Z10 Z15 sur)
    (conectada Z15 Z10 norte)
    (conectada Z15 Z20 sur)
    (conectada Z20 Z15 norte)
    (conectada Z20 Z25 sur)
    (conectada Z25 Z20 norte)
    
    (conectada Z25 Z24 oeste)
    (conectada Z24 Z25 este)
    (conectada Z24 Z23 oeste)
    (conectada Z23 Z24 este)
    (conectada Z23 Z22 oeste)
    (conectada Z22 Z23 este)
    (conectada Z22 Z21 oeste)
    (conectada Z21 Z22 este)

    (conectada Z21 Z16 norte)
    (conectada Z16 Z21 sur)
    (conectada Z16 Z11 norte)
    (conectada Z11 Z16 sur)
    (conectada Z11 Z6 norte)
    (conectada Z6 Z11 sur)
    (conectada Z6 Z1 norte)
    (conectada Z1 Z6 sur)

    ; Zonas intermedias
    (conectada Z7 Z8 este)
    (conectada Z8 Z7 oeste)
    (conectada Z8 Z3 norte)
    (conectada Z3 Z8 sur)
    (conectada Z13 Z8 norte)
    (conectada Z8 Z13 sur)
    (conectada Z9 Z10 este)
    (conectada Z10 Z9 oeste)
    (conectada Z9 Z14 sur)
    (conectada Z14 Z9 norte)

    (conectada Z11 Z12 este)
    (conectada Z12 Z11 oeste)
    (conectada Z12 Z13 este)
    (conectada Z13 Z12 oeste)
    (conectada Z13 Z14 este)
    (conectada Z14 Z13 oeste)
    (conectada Z17 Z12 norte)
    (conectada Z12 Z17 sur)
    (conectada Z18 Z13 norte)
    (conectada Z13 Z18 sur)
    (conectada Z14 Z19 norte)
    (conectada Z19 Z14 sur)
    
    (conectada Z17 Z18 este)
    (conectada Z18 Z17 oeste)
    (conectada Z19 Z20 este)
    (conectada Z20 Z19 oeste)

    (conectada Z19 Z24 sur)
    (conectada Z24 Z19 norte)

    ; Objetos en el mapa
    (esta_obj ORO Z22)
    (esta_obj OSCAR Z9)
    (esta_obj MANZANA Z15)
    (esta_obj ROSA Z10)
    (esta_obj ALGORITMO Z19)

    (esta_per PRINCIPE Z6)
    (esta_per LEONARDO Z14)
    (esta_per BRUJA Z5)
    (esta_per PRINCESA Z21)
    (esta_per PROFESOR Z25)
    
    (esta PROTAGONISTA Z13)
    (orien_prota norte)
    (manovacia)
)

; El objetivo va a ser entregar los objetos a los personajes
(:goal 
    (and (tiene OSCAR LEONARDO) (tiene ROSA PRINCESA) (tiene MANZANA BRUJA) (tiene ALGORITMO PROFESOR)))
)