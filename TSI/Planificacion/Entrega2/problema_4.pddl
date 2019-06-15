(define (problem zeno-0) (:domain zeno-travel)
(:customization
(= :time-format "%d/%m/%Y %H:%M:%S")
(= :time-horizon-relative 2500)
(= :time-start "05/06/2007 08:00:00")
(= :time-unit :hours))

(:objects 
    p1 p2 p3 p4 p5 p6 p7 - person
    Madrid Granada Sevilla Bilbao - city
    a1 - aircraft
)

(:init
    (at p1 Granada) 
    (at p2 Bilbao)
    (at p3 Sevilla)
	(at p4 Granada)
	(at p5 Granada)
	(at p6 Granada)
	(at p7 Madrid)
	
    (at a1 Madrid)
    (= (fuel-limit) 150000)
	
	(= (distance Granada Bilbao) 829)
    (= (distance Granada Madrid) 421)
    (= (distance Granada Sevilla) 252)
    (= (distance Bilbao Granada) 829)
    (= (distance Bilbao Madrid) 395)
    (= (distance Bilbao Sevilla) 933)
    (= (distance Madrid Granada) 421)
    (= (distance Madrid Bilbao) 395)
    (= (distance Madrid Sevilla) 534)
    (= (distance Sevilla Granada) 252)
    (= (distance Sevilla Bilbao) 933)
    (= (distance Sevilla Madrid) 534)
	
    (= (fuel a1) 150000)
    (= (slow-speed a1) 10)
    (= (fast-speed a1) 20)
    (= (slow-burn a1) 1)
    (= (fast-burn a1) 2)
    (= (capacity a1) 300)
    (= (refuel-rate a1) 1)
    (= (total-fuel-used) 0)
    (= (boarding-time) 1)
    (= (debarking-time) 1)
	
	(= (maxpasajeros a1) 20)
    (= (pasajeros a1) 0)
	
	(destino p1 Sevilla)
	(destino p2 Sevilla)
	(destino p3 Sevilla)
	(destino p4 Sevilla)
	(destino p5 Sevilla)
	(destino p6 Sevilla)
	(destino p7 Sevilla)
 )


(:tasks-goal
   :tasks(
   (transport-person p1 Sevilla)
   (transport-person p2 Sevilla)
   (transport-person p3 Sevilla)
   (transport-person p4 Sevilla)
   (transport-person p5 Sevilla)
   (transport-person p6 Sevilla)
   (transport-person p7 Sevilla)
   
   )
  )
)