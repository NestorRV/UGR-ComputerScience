(define (problem Problema5)

(:domain LosMundosDeBelkan)

(:OBJECTS 
    Z1 Z2 - zona 
    PROTAGONISTA - protagonista
    OSCAR MANZANA ROSA ALGORITMO ORO ZAPATILLAS BIKINI - objeto
    PRINCESA PRINCIPE BRUJA PROFESOR LEONARDO - personaje
    norte sur este oeste - orientacion
    MOCHILA - mochila
    BOSQUE AGUA PRECIPICIO ARENA PIEDRA - tipo
)

(:INIT
    ; Extremos
    (conectada Z1 Z2 norte)
    (conectada Z2 Z1 sur)

    (util BIKINI AGUA)
    (util ZAPATILLAS BOSQUE)
    (libre PIEDRA)
    (libre ARENA)

    ; Costes
    (= (distancia Z1 Z2) 5)
    (= (distancia Z2 Z1) 5)
    
    ; Tipo de terreno de cada zona
    (tipo_zona Z1 ARENA)
    (tipo_zona Z2 ARENA)

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
    (esta_obj OSCAR Z2)
    (esta_obj MANZANA Z2)
    (esta_obj ORO Z2)
    (esta_obj ALGORITMO Z2)
    (esta_obj ROSA Z2)

    (esta_per PRINCIPE Z1)
    (esta_per LEONARDO Z1)
    (esta_per BRUJA Z1)
    (esta_per PRINCESA Z1)
    (esta_per PROFESOR Z1)
    
    (esta PROTAGONISTA Z1)
    (orien_prota norte)
    (= (coste) 0)
    (= (puntos) 0)
    (manovacia)

    (= (objetos_guardados) 0)
    (= (tamanio_mochila) 10)
)

; El objetivo va a ser entregar los objetos a los personajes
(:goal 
    (and (tiene OSCAR LEONARDO) (tiene ROSA PRINCESA) (tiene MANZANA BRUJA) (tiene ALGORITMO PROFESOR) (tiene ORO PRINCIPE)))

    (:metric minimize (coste))
)