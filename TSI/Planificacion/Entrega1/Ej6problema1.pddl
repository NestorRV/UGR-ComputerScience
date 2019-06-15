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


    (= (distancia Z1 Z2) 5)
    (= (distancia Z2 Z1) 5)
    (= (distancia Z2 Z3) 5)
    (= (distancia Z3 Z2) 5)

    (= (distancia Z4 Z5) 5)
    (= (distancia Z5 Z4) 5)
    (= (distancia Z5 Z6) 5)
    (= (distancia Z6 Z5) 5)

    (= (distancia Z7 Z8) 5)
    (= (distancia Z8 Z7) 5)
    (= (distancia Z8 Z9) 5)
    (= (distancia Z9 Z8) 5)

    (= (distancia Z1 Z4) 5)
    (= (distancia Z4 Z1) 5)
    (= (distancia Z4 Z7) 5)
    (= (distancia Z7 Z4) 5)

    (= (distancia Z3 Z6) 5)
    (= (distancia Z6 Z3) 5)
    (= (distancia Z6 Z9) 5)
    (= (distancia Z9 Z6) 5)
    
    (= (distancia Z2 Z5) 5)
    (= (distancia Z5 Z2) 5)

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
    (= (penalizacion OSCAR LEONARDO) 0)
    (= (penalizacion ROSA LEONARDO) 9)
    (= (penalizacion MANZANA LEONARDO) 7)
    (= (penalizacion ALGORITMO LEONARDO) 6)
    (= (penalizacion ORO LEONARDO) 5)

    (= (penalizacion OSCAR PRINCESA) 5)
    (= (penalizacion ROSA PRINCESA) 0)
    (= (penalizacion MANZANA PRINCESA) 9)
    (= (penalizacion ALGORITMO PRINCESA) 7)
    (= (penalizacion ORO PRINCESA) 6)

    (= (penalizacion OSCAR BRUJA) 6)
    (= (penalizacion ROSA BRUJA) 5)
    (= (penalizacion MANZANA BRUJA) 0)
    (= (penalizacion ALGORITMO BRUJA) 9)
    (= (penalizacion ORO BRUJA) 7)

    (= (penalizacion OSCAR PROFESOR) 7)
    (= (penalizacion ROSA PROFESOR) 6)
    (= (penalizacion MANZANA PROFESOR) 5)
    (= (penalizacion ALGORITMO PROFESOR) 0)
    (= (penalizacion ORO PROFESOR) 9)

    (= (penalizacion OSCAR PRINCIPE) 9)
    (= (penalizacion ROSA PRINCIPE) 7)
    (= (penalizacion MANZANA PRINCIPE) 6)
    (= (penalizacion ALGORITMO PRINCIPE) 5)
    (= (penalizacion ORO PRINCIPE) 0)

    ; Objetos en el mapa
    (esta_obj OSCAR Z4)
    (esta_obj MANZANA Z5)
    (esta_obj ORO Z6)
    (esta_obj ALGORITMO Z7)
    (esta_obj ROSA Z8)
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
    (= (penalizacion_jugador) 0)
    (manovacia)

    (util BIKINI AGUA)
    (util ZAPATILLAS BOSQUE)
    (libre PIEDRA)
    (libre ARENA)

    (= (tamanio_mochila) 10)
    (= (objetos_guardados) 0)
    (= (objetos_entregados) 0)
)

(:goal 
    (and (>= (objetos_entregados) 4)))

    (:metric minimize (penalizacion_jugador))
)