(define (problem zeno-0) (:domain zeno-travel)
(:customization
(= :time-format "%d/%m/%Y %H:%M:%S")
(= :time-horizon-relative 2500)
(= :time-start "05/06/2007 08:00:00")
(= :time-unit :hours))

(:objects 
    p1 p2 p3 p4 p5 - person
    Barcelona Madrid Granada Sevilla Bilbao - city
    a1 - aircraft
)

(:init
    (at p1 Barcelona) 
    (at p2 Madrid)
    (at p3 Granada)
	(at p4 Sevilla)
	(at p5 Bilbao)
	
    (at a1 Barcelona)
    (= (fuel-limit) 150000)
	
	(= (distance Granada Barcelona) 868)
    (= (distance Granada Bilbao) 829)
    (= (distance Granada Madrid) 421)
    (= (distance Granada Sevilla) 252)
    (= (distance Barcelona Granada) 868)
    (= (distance Barcelona Bilbao) 620)
    (= (distance Barcelona Madrid) 621)
    (= (distance Barcelona Sevilla) 1046)
    (= (distance Bilbao Granada) 829)
    (= (distance Bilbao Madrid) 395)
    (= (distance Bilbao Barcelona) 620)
    (= (distance Bilbao Sevilla) 933)
    (= (distance Madrid Granada) 421)
    (= (distance Madrid Bilbao) 395)
    (= (distance Madrid Barcelona) 621)
    (= (distance Madrid Sevilla) 534)
    (= (distance Sevilla Granada) 252)
    (= (distance Sevilla Bilbao) 933)
    (= (distance Sevilla Madrid) 534)
    (= (distance Sevilla Barcelona) 1046)
	
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
	
	(destino p1 Barcelona) 
    (destino p2 Barcelona)
    (destino p3 Barcelona)
	(destino p4 Barcelona)
	(destino p5 Barcelona)
 )


(:tasks-goal
   :tasks(
   (transport-person p1 Barcelona) 
   (transport-person p2 Barcelona)
   (transport-person p3 Barcelona)
   (transport-person p4 Barcelona)
   (transport-person p5 Barcelona)
   )
  )
)