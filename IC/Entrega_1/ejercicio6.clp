; Néstor Rodríguez Vico

(deffacts Hechos
  (RESPONDER)
  (Modulo 1)
)

; Preguntamos en que modulo quiere entrar y lo asertamos
(defrule PreguntarModulo1
    ?f <- (Modulo 1)
    =>
    (printout t "Pulse 2, 3 o 4 para ir al módulo 2, 3 o 4 respectivamente: " crlf)
    (assert (Modulo (read)))
    (retract ?f)
)

; Si entramos en el dos o en el 3 debemos asegurarnos de que quiera estar en ese modulo
(defrule PreguntarModulo2
    (Modulo 2)
    =>
    (printout t "Estoy en modulo 2. Estas seguro de que queires quedarte aqui? Pulse s/S para si y n/N para no. " crlf)
    (assert (Respuesta (upcase (read)) 2))
)

(defrule PreguntarModulo3
    (Modulo 3)
    =>
    (printout t "Estoy en modulo 3. Estas seguro de que queires quedarte aqui? Pulse s/S para si y n/N para no. " crlf)
    (assert (Respuesta (upcase (read)) 3))
)

; En el cuatro saludamos, por eso insertamos un hecho con el nombre del usuario
(defrule PreguntarModulo4
    (Modulo 4)
    =>
    (printout t "Estoy en modulo 4. Como decias que te llamabas? ")
    (assert (Nombre (read)))
)

; Vemos si debemos cambiarnos de modulo o no
; Debemos retractarnos del hecho que nos guarda en el bucle en el que estabamos
(defrule CambiarNoCambiarMod2
    ?d <- (Respuesta N 2)
    ?f <- (Modulo 2)
    =>
    (retract ?f)
    (retract ?d)
    (assert (Modulo 3))
)

; Vemos si debemos cambiarnos de modulo o no
; Debemos retractarnos del hecho que nos guarda en el bucle en el que estabamos
(defrule CambiarNoCambiarMod3
    ?d <- (Respuesta N 3)
    ?f <- (Modulo 3)
    =>
    (retract ?f)
    (retract ?d)
    (assert (Modulo 1))
)

; Saludamos al usuario
(defrule Saludar
    ?f1 <- (RESPONDER)
    ?f2 <- (Modulo ?m)
    (Nombre ?n)
    =>
    (retract ?f1)
    (retract ?f2)
    (printout t "Hola " ?n "! Un placer verte por aqui de nuevo!" crlf)
)