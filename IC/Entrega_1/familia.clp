; Néstor Rodríguez Vico

(deffacts Parentescos
    (RESPONDER)
    ; Definimos las personas de la familia según su sexo
    ; Las definimos por nombre y por genero
    (Persona "Persona1" Hombre) ; Yo
    (Persona "Persona2" Hombre) ; Hermano
    (Persona "Persona3" Hombre) ; Padre
    (Persona "Persona4" Mujer) ; Madre
    (Persona "Persona5" Hombre) ; Abuelo
    (Persona "Persona6" Mujer) ; Abuela
    (Persona "Persona7" Hombre) ; Abuelo
    (Persona "Persona8" Mujer) ; Abuela
    (Persona "Persona9" Hombre)
    (Persona "Persona10" Mujer)
    (Persona "Persona11" Mujer)
    (Persona "Persona12" Hombre)
    (Persona "Persona13" Mujer)
    (Persona "Persona14" Hombre)
    (Persona "Persona15" Mujer)
    (Persona "Persona16" Mujer)
    (Persona "Persona17" Hombre)
    (Persona "Persona18" Hombre)
    (Persona "Persona19" Mujer)
    (Persona "Persona20" Hombre)
    (Persona "Persona21" Mujer)
    (Persona "Persona22" Hombre)
    (Persona "Persona23" Mujer)

    ; Parejas
    ; (Relacion pareja P1 y P2) -> P1 es pareja de P2
    (Relacion pareja "Persona6" "Persona5")
    (Relacion pareja "Persona8" "Persona7")
    (Relacion pareja "Persona15" "Persona14")
    (Relacion pareja "Persona18" "Persona19")
    (Relacion pareja "Persona4" "Persona3")
    (Relacion pareja "Persona10" "Persona9")
    (Relacion pareja "Persona12" "Persona13")

    ; Padre de (Hijos de mis abuelos maternos)
    ; (Relacion padre P1 P2) -> P1 es padre de P2
    (Relacion padre "Persona8" "Persona15")
    (Relacion padre "Persona8" "Persona4")
    (Relacion padre "Persona8" "Persona17")
    (Relacion padre "Persona8" "Persona18")
    (Relacion padre "Persona7" "Persona15")
    (Relacion padre "Persona7" "Persona4")
    (Relacion padre "Persona7" "Persona17")
    (Relacion padre "Persona7" "Persona18")

    ; Padre de (Hijos de mis abuelos paternos)
    (Relacion padre "Persona6" "Persona3")
    (Relacion padre "Persona6" "Persona10")
    (Relacion padre "Persona6" "Persona12")
    (Relacion padre "Persona5" "Persona3")
    (Relacion padre "Persona5" "Persona10")
    (Relacion padre "Persona5" "Persona12")

    ; Padre de (Hijos de mis tios maternos)
    (Relacion padre "Persona18" "Persona20")
    (Relacion padre "Persona18" "Persona21")
    (Relacion padre "Persona19" "Persona20")
    (Relacion padre "Persona19" "Persona21")
    (Relacion padre "Persona15" "Persona16")
    (Relacion padre "Persona14" "Persona16")

    ; Padre de (Hijos de mis tios paternos)
    (Relacion padre "Persona10" "Persona11")
    (Relacion padre "Persona9" "Persona11")
    (Relacion padre "Persona12" "Persona23")
    (Relacion padre "Persona12" "Persona22")
    (Relacion padre "Persona13" "Persona23")
    (Relacion padre "Persona13" "Persona22")

    ; Padre de (mis padres)
    (Relacion padre "Persona3" "Persona1")
    (Relacion padre "Persona3" "Persona2")
    (Relacion padre "Persona4" "Persona1")
    (Relacion padre "Persona4" "Persona2")

    ; Definimos las relaciones duales
    (Dual padre hijo)
    (Dual hermano hermano)
    (Dual tio sobrino)
    (Dual pareja pareja)
    (Dual primo primo)
    (Dual suegro yerno)
    (Dual abuelo nieto)
    (Dual cuniado cuniado)

    ; Composiciones de parentescos
    (Composicion padre padre abuelo)
    (Composicion hermano padre tio)
    (Composicion pareja hermano cuniado)
    (Composicion hermano pareja cuniado)
    (Composicion hijo tio primo)
    (Composicion padre pareja suegro)
    (Composicion hijo padre hermano)
    (Composicion pareja padre padre)

    ; Cambio de genero en los parentescos
    (SexoFemenino pareja pareja)
    (SexoFemenino abuelo abuela)
    (SexoFemenino nieto nieta)
    (SexoFemenino padre madre)
    (SexoFemenino hermano hermana)
    (SexoFemenino hijo hija)
    (SexoFemenino tio tia)
    (SexoFemenino sobrino sobrina)
    (SexoFemenino primo prima)
    (SexoFemenino cuniado cuniada)
    (SexoFemenino suegro suegra)
    (SexoFemenino yerno nuera)
)

; La idea es dualizar las RelacionesDuales
; Si tenemos (Dual padre hijo), introducimos (Dual hijo padre)
(defrule DualizarDuales
    (Dual ?R1 ?R2)
    =>
    (assert (Dual ?R2 ?R1))
)

; Si tenemos (Relacion padre P1 P2), introducimos (Relacion hijo P2 P1)
(defrule RelacionesDuales
    (Relacion ?R1 ?x ?y)
    (Justificacion ?R1 ?x ?y ?j)
    (Dual ?R1 ?R2)
    =>
    (assert (Relacion ?R2 ?y ?x))
    (assert (Justificacion ?R2 ?y ?x ?j))
)

; Las composiciones es para generar relaciones que se dan 
; por relaciones intermedias
; Si tenemos (Relacion hermano P1 P2) y (Relacion padre P2 P3)
; y existe una composicion (Composicion hermano padre tio)
; podemos deducir que (Relacion tio P1 P3)
; Hay 4 versiones para tener cuidado con los generos de las dos personas 
; que se va a generar la relacion. Esto se hace para añadir la justificacion
; correctamente, es decir, que los generos sean correctos
(defrule ComponerMascMasc
    (Relacion ?R1 ?x ?y)
    (Relacion ?R2 ?y ?z)
    (Persona ?x Hombre)
    (Persona ?y Hombre)
    (Composicion ?R1 ?R2 ?R3)
    (test (neq ?x ?z))
    =>
    (assert (Relacion ?R3 ?x ?z))
    (assert (Justificacion ?R3 ?x ?z (str-cat " porque " ?x " es " ?R1 " de " ?y " y " ?y " es " ?R2 " de " ?z)))
)

(defrule ComponerMascFem
    (Relacion ?R1 ?x ?y)
    (Relacion ?R2 ?y ?z)
    (Persona ?x Hombre)
    (Persona ?y Mujer)
    (SexoFemenino ?R2 ?femenino)
    (Composicion ?R1 ?R2 ?R3)
    (test (neq ?x ?z))
    =>
    (assert (Relacion ?R3 ?x ?z))
    (assert (Justificacion ?R3 ?x ?z (str-cat " porque " ?x " es " ?R1 " de " ?y " y " ?y " es " ?femenino " de " ?z)))
)

(defrule ComponerFemMasc
    (Relacion ?R1 ?x ?y)
    (Relacion ?R2 ?y ?z)
    (Persona ?x Mujer)
    (SexoFemenino ?R1 ?femenino)
    (Persona ?y Hombre)
    (Composicion ?R1 ?R2 ?R3)
    (test (neq ?x ?z))
    =>
    (assert (Relacion ?R3 ?x ?z))
    (assert (Justificacion ?R3 ?x ?z (str-cat " porque " ?x " es " ?femenino " de " ?y " y " ?y " es " ?R2 " de " ?z)))
)

(defrule ComponerFemFem
    (Relacion ?R1 ?x ?y)
    (Relacion ?R2 ?y ?z)
    (Composicion ?R1 ?R2 ?R3)
    (Persona ?x Mujer)
    (Persona ?y Mujer)
    (SexoFemenino ?R1 ?femenino)
    (SexoFemenino ?R2 ?femenino2)
    (test (neq ?x ?z))
    =>
    (assert (Relacion ?R3 ?x ?z))
    (assert (Justificacion ?R3 ?x ?z (str-cat " porque " ?x " es " ?femenino " de " ?y " y " ?y " es " ?femenino2 " de " ?z)))
)

; Si nos preguntan por una persona masculina no debemos hacer nada especial
; más allá de comprobar que existe un hecho que relaciona las dos personas
(defrule Masculino
    ?f <- (RESPONDER)
    (InformacionSobre ?n1 ?n2)
    (Relacion ?r ?n1 ?n2)
    (Persona ?n1 Hombre)
    (Justificacion ?r ?n1 ?n2 ?just)
    =>
    (printout t ?n1 " es " ?r " de " ?n2 ?just crlf)
    (retract ?f)
)

; Si nos preguntan por una persona femenina debemos comprobar que 
; existe un hecho que relaciona las dos personas y ademas
; cambiar el genero de la relacion, por eso el hecho SexoFemenino
(defrule Femenino
    ?f <- (RESPONDER)
    (InformacionSobre ?n1 ?n2)
    (Relacion ?r ?n1 ?n2)
    (Persona ?n1 Mujer)
    (SexoFemenino ?r ?femenino)
    (Justificacion ?r ?n1 ?n2 ?just)
    =>
    (printout t ?n1 " es " ?femenino " de " ?n2 ?just crlf)
    (retract ?f)
)

; Otenemos el nombre de la primera persona
(defrule ObtenerPrimerNombre
    =>
    (printout t "Dime el nombre de la primera persona: ")
    (assert (PrimeraPersona (readline)))
)

; Otenemos el nombre de la segunda persona y asertamos el hecho
; (InformacionSobre P1 P2), ppara saber sobre que personas se nos ha preguntado
(defrule ObtenerSegundoNombre
    (PrimeraPersona ?n1)
    =>
    (printout t "Dime el nombre de la segunda persona: ")
    (assert (InformacionSobre ?n1 (readline)))
)
