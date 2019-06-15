(define (domain zeno-travel)

(:requirements
  :typing
  :fluents
  :derived-predicates
  :negative-preconditions
  :universal-preconditions
  :disjuntive-preconditions
  :conditional-effects
  :htn-expansion

  ; Requisitos adicionales para el manejo del tiempo
  :durative-actions
  :metatags
 )

(:types aircraft person city - object)
(:constants slow fast - object)
(:predicates (at ?x - (either person aircraft) ?c - city)
             (in ?p - person ?a - aircraft)
             (different ?x ?y) (igual ?x ?y)
             (hay-fuel-slow ?a ?c1 ?c2)
			 (hay-fuel-fast ?a ?c1 ?c2)
)

(:functions (fuel ?a - aircraft)
            (distance ?c1 - city ?c2 - city)
            (slow-speed ?a - aircraft)
            (fast-speed ?a - aircraft)
            (slow-burn ?a - aircraft)
            (fast-burn ?a - aircraft)
            (capacity ?a - aircraft)
            (refuel-rate ?a - aircraft)
            (total-fuel-used)
            (boarding-time)
            (debarking-time)
			(fuel-limit)
			(maxpasajeros ?a - aircraft)
            (pasajeros ?a - aircraft)
            (destino ?p - person ?c - city)
)

; El consecuente "vacio" se representa como "()" y significa "siempre verdad"
(:derived
  (igual ?x ?x) ()
)

(:derived 
  (different ?x ?y) (not (igual ?x ?y))
)

; este literal derivado se utiliza para deducir, a partir de la información en el estado actual, 
; si hay fuel suficiente para que el avión ?a vuele de la ciudad ?c1 a la ?c2
; el antecedente de este literal derivado comprueba si el fuel actual de ?a es mayor que 1. 
; En este caso es una forma de describir que no hay restricciones de fuel. Pueden introducirse una
; restricción más copleja  si en lugar de 1 se representa una expresión más elaborada (esto es objeto de
; los siguientes ejercicios).

(:derived   
  (hay-fuel-slow ?a - aircraft ?c1 - city ?c2 - city)
  (> (fuel ?a) (* (distance ?c1 ?c2) (slow-burn ?a)))
)

(:derived   
  (hay-fuel-fast ?a - aircraft ?c1 - city ?c2 - city)
  (> (fuel ?a) (* (distance ?c1 ?c2) (fast-burn ?a)))
)

(:task transport-person
	:parameters (?p - person ?c - city)

	(:method Case1 ; si la persona esta en la ciudad no se hace nada
		:precondition (at ?p ?c)
		
		:tasks ()
	)

	(:method Case2 ;si no esta en la ciudad destino, pero avion y persona estan en la misma ciudad
		:precondition (and (at ?p - person ?c1 - city) (at ?a - aircraft ?c1 - city))

		:tasks ((board) (mover-avion ?a ?c1 ?c) (debark))
	)
	
	(:method Case3 ; El avión y la persona no están en la misma ciudad
		:precondition (and (at ?p - person ?c1 - city) (at ?a - aircraft ?c2 - city)
					   (different ?c1 - city ?c2 - city))
		
		:tasks ((mover-avion ?a ?c2 ?c1) (board) (mover-avion ?a ?c1 ?c) (debark))
	)
)

(:task mover-avion
	:parameters (?a - aircraft ?c1 - city ?c2 -city)
	; este método se escogerá para usar la acción fly siempre que el avión tenga fuel para
	; volar desde ?c1 a ?c2
	; si no hay fuel suficiente el método no se aplicará y la descomposición de esta tarea
	; se intentará hacer con otro método. Cuando se agotan todos los métodos posibles, la
	; descomponsición de la tarea mover-avión "fallará". 
	; En consecuencia HTNP hará backtracking y escogerá otra posible vía para descomponer
	; la tarea mover-avion (por ejemplo, escogiendo otra instanciación para la variable ?a)
	
	(:method fuel-suficiente-fast
		:precondition (and (hay-fuel-fast ?a ?c1 ?c2) (> (fuel-limit) (total-fuel-used)))
		
		:tasks ((zoom ?a ?c1 ?c2))
	)
	
	(:method fuel-insuficiente-fast
		:precondition (and (not (hay-fuel-fast ?a ?c1 ?c2)) (> (fuel-limit) (total-fuel-used)))
		
		:tasks ((refuel ?a ?c1) (zoom ?a ?c1 ?c2))
	)
	
	(:method fuel-suficiente-slow
		:precondition (and (hay-fuel-slow ?a ?c1 ?c2) (> (fuel-limit) (total-fuel-used)))
		
		:tasks ((fly ?a ?c1 ?c2))
	)
	
	(:method fuel-insuficiente-slow
		:precondition (and (not (hay-fuel-slow ?a ?c1 ?c2)) (> (fuel-limit) (total-fuel-used)))
		
		:tasks ((refuel ?a ?c1) (fly ?a ?c1 ?c2))
	)
)
 
(:import "Primitivas-Zenotravel-Ejercicio4.pddl") 
)