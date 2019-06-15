(define (problem Problema4)

(:domain LosMundosDeBelkan)

(:OBJECTS 
    Z1 Z2 Z3 Z4 Z5 Z6 Z7 Z8 Z9 - zona
    PROTAGONISTA - protagonista
    OSCAR MANZANA ROSA ALGORITMO ORO ZAPATILLAS BIKINI - objeto
    PRINCESA PRINCIPE BRUJA PROFESOR LEONARDO - personaje
    norte sur este oeste - orientacion
    MOCHILA - mochila
    BOSQUE AGUA PRECIPICIO ARENA PIEDRA - tipo
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


    (= (distancia Z1 Z2) 1)
    (= (distancia Z2 Z1) 1)
    (= (distancia Z2 Z3) 1)
    (= (distancia Z3 Z2) 1)

    (= (distancia Z4 Z5) 1)
    (= (distancia Z5 Z4) 1)
    (= (distancia Z5 Z6) 1)
    (= (distancia Z6 Z5) 1)

    (= (distancia Z7 Z8) 1)
    (= (distancia Z8 Z7) 1)
    (= (distancia Z8 Z9) 1)
    (= (distancia Z9 Z8) 1)

    (= (distancia Z1 Z4) 1)
    (= (distancia Z4 Z1) 1)
    (= (distancia Z4 Z7) 1)
    (= (distancia Z7 Z4) 1)

    (= (distancia Z3 Z6) 1)
    (= (distancia Z6 Z3) 1)
    (= (distancia Z6 Z9) 1)
    (= (distancia Z9 Z6) 1)
    
    (= (distancia Z2 Z5) 1)
    (= (distancia Z5 Z2) 1)

    ; Tipo de terreno de cada zona
    (tipo_zona Z1 PRECIPICIO)
    (tipo_zona Z2 AGUA)
    (tipo_zona Z3 BOSQUE)
    (tipo_zona Z4 ARENA)
    (tipo_zona Z5 ARENA)
    (tipo_zona Z6 ARENA)
    (tipo_zona Z7 ARENA)
    (tipo_zona Z8 ARENA)
    (tipo_zona Z9 ARENA)

    ; Puntos obtenidos
    (= (cantidad_puntos OSCAR LEONARDO) 10)
    (= (cantidad_puntos ROSA LEONARDO) 1)
    (= (cantidad_puntos MANZANA LEONARDO) 3)
    (= (cantidad_puntos ALGORITMO LEONARDO) 4)
    (= (cantidad_puntos ORO LEONARDO) 5)

    (= (cantidad_puntos OSCAR PRINCESA) 5)
    (= (cantidad_puntos ROSA PRINCESA) 10)
    (= (cantidad_puntos MANZANA PRINCESA) 1)
    (= (cantidad_puntos ALGORITMO PRINCESA) 3)
    (= (cantidad_puntos ORO PRINCESA) 4)

    (= (cantidad_puntos OSCAR BRUJA) 4)
    (= (cantidad_puntos ROSA BRUJA) 5)
    (= (cantidad_puntos MANZANA BRUJA) 10)
    (= (cantidad_puntos ALGORITMO BRUJA) 1)
    (= (cantidad_puntos ORO BRUJA) 3)

    (= (cantidad_puntos OSCAR PROFESOR) 3)
    (= (cantidad_puntos ROSA PROFESOR) 4)
    (= (cantidad_puntos MANZANA PROFESOR) 5)
    (= (cantidad_puntos ALGORITMO PROFESOR) 10)
    (= (cantidad_puntos ORO PROFESOR) 1)

    (= (cantidad_puntos OSCAR PRINCIPE) 1)
    (= (cantidad_puntos ROSA PRINCIPE) 3)
    (= (cantidad_puntos MANZANA PRINCIPE) 4)
    (= (cantidad_puntos ALGORITMO PRINCIPE) 5)
    (= (cantidad_puntos ORO PRINCIPE) 10)

    ; Objetos en el mapa
    (esta_obj OSCAR Z4)
    (esta_obj OSCAR Z5)
    (esta_obj OSCAR Z6)
    (esta_obj OSCAR Z7)
    (esta_obj OSCAR Z8)
    (esta_obj MANZANA Z4)
    (esta_obj MANZANA Z5)
    (esta_obj MANZANA Z6)
    (esta_obj MANZANA Z7)
    (esta_obj MANZANA Z8)
    (esta_obj ZAPATILLAS Z9)
    (esta_obj ZAPATILLAS Z2)
    (esta_obj BIKINI Z3)

    (esta_per PRINCIPE Z2)
    (esta_per LEONARDO Z3)
    (esta_per BRUJA Z9)
    (esta_per PRINCESA Z4)
    (esta_per PROFESOR Z8)
    
    (esta PROTAGONISTA Z7)
    (orien_prota norte)
    (= (coste) 0)
    (= (puntos) 0)
    (manovacia)
    (mochilavacia)

    (util BIKINI AGUA)
    (util ZAPATILLAS BOSQUE)
    (libre PIEDRA)
    (libre ARENA)
)

; El objetivo va a ser entregar los objetos a los personajes
(:goal 
    (and (>= (puntos) 50)))

    (:metric minimize (coste))
)