; Néstor Rodríguez Vico

(deffacts Hechos
    (REPETIR)
    (Tipo1 Elemento1 Elemento2 Elemento3 Elemento4 Elemento5 Elemento6)
)

; Funcion que crea una nueva lista a partir de otra
; convirtiendo todos los elementos a mayúscula
; Ojo! Invierte el orden de las lista
(deffunction minus_to_mayus ($?lista)
    (bind ?respuesta (create$ ))
    (progn$ (?field ?lista)
        (bind ?respuesta (insert$ ?respuesta 1 (upcase ?field)))
    )
    (printout t ?respuesta crlf)
    (return ?respuesta)
)

; Le mostramos la lista al usuario y le pedimos que eliga uno
; Insertamos el elemento elegido pero en mayuscula
; e insertamos toda la lista en mayuscula. Esto se hace para
; que funcione independientemente de si el usuario introduce el 
; elemento en mayuscula o minuscula
(defrule Empecemos
    (declare (salience 30))
    (Tipo1 $?lista)
    (REPETIR)
    =>
    (printout t "El tipo de hecho que he elegido es Tipo1 y esta es la lista de elementos entre los que tienes que elegir uno: " crlf)
    (printout t ?lista crlf)
    (assert (ElementoElegido (upcase (read))))
    (assert (Tipo1_Bis (minus_to_mayus ?lista)))
    (assert (COMPROBAR))
)

; Comprobamos si esta el elemento elegido comparándolo 
; con la lista en mayuscula
(defrule Esta
    ?f1 <- (COMPROBAR)
    ?f2 <- (REPETIR)
    (ElementoElegido ?elegido)
    (Tipo1_Bis $? ?elegido $?)
    =>
    (printout t "El elemento está en la lista." crlf)
    (retract ?f1)
    (retract ?f2)
)

; Si no está, repetimos el proceso
; Debemos retractarnos del hecho repetir y asertarlo de nuevo.
; Esto se hace para que cambie su identificador y por lo tanto
; clips ejecute la primera regla de nuevo (clips no ejecuta una regla si 
; ya se ha ejecutado con los mismos hechos)
(defrule NoEsta
    (declare (salience -5))
    ?f1 <- (COMPROBAR)
    ?f2 <- (REPETIR)
    =>
    (printout t "El elemento NO está en la lista." crlf crlf)
    (retract ?f1)
    (retract ?f2)
    (assert (REPETIR))
)