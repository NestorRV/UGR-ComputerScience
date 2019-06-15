#encoding: UTF-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module NapakalakiGame

  require_relative "bad_consequence.rb"
  require_relative "monster.rb"
  require_relative "prize.rb"
  require_relative "treasure_kind.rb"
  require_relative "card_dealer.rb"
  require_relative "combat_result.rb"
  require_relative "dice.rb"
  require_relative "napakalaki.rb"
  require_relative "player.rb"
  require_relative "treasure.rb"

  #CREACION DE MONSTRUOS /////////////////////////////////////////////////////////////////////////////////////////////////
  monsters = Array.new

  p1 = Prize.new(2,1)
  bc1 = BadConsequence.newLevelSpecificTreasures("Pierdes tu armadura visible y otra oculta.",0,[TreasureKind::ARMOR],[TreasureKind::ARMOR])
  monsters << Monster.new("3 Byakhess de bonanza",8,bc1,p1)
        
  p2 = Prize.new(1,1)
  bc2 = BadConsequence.newLevelSpecificTreasures("Embobados con el lindo primigenio te descartas de tu casco visible.",0,[TreasureKind::HELMET],[])
  monsters << Monster.new("Chibithulhu",2,bc2,p2)
        
  p3 = Prize.new(1,1)
  bc3 = BadConsequence.newLevelSpecificTreasures("El primordial bostezo contagioso. Pierdes el calzado visible",0,[TreasureKind::SHOES],[])
  monsters << Monster.new("El sopor de Dunwich",2,bc3,p3)
        
  p4 = Prize.new(4,1)
  bc4 = BadConsequence.newLevelSpecificTreasures("Te atrapan para llevarte de fiesta y te dejan caer en mitad del vuelo. Descarta 1 mano visible y 1 mano oculta", 0,[TreasureKind::ONEHAND],[TreasureKind::ONEHAND])
  monsters << Monster.new("Ángeles de la noche ibicenca",14,bc4,p4)
        
  p5 = Prize.new(3,1)
  bc5 = BadConsequence.newLevelSpecificTreasures("Pierdes todos tus tesoros visibles",0,[TreasureKind::ARMOR,TreasureKind::ONEHAND,TreasureKind::ONEHAND,TreasureKind::BOTHHANDS,TreasureKind::HELMET,TreasureKind::SHOES],[])
  monsters << Monster.new("El gorrón en el umbral",10,bc5,p5)
        
  p6 = Prize.new(2,1)
  bc6 = BadConsequence.newLevelSpecificTreasures("Pierdes la armadura visible",0,[TreasureKind::ARMOR],[])
  monsters << Monster.new("H.P. Munchcraft",6,bc6,p6)
        
  p7 = Prize.new(1,1)
  bc7 = BadConsequence.newLevelSpecificTreasures("Sientes bichos bajo la ropa. Descarta la armadura visible",0,[TreasureKind::ARMOR],[])
  monsters << Monster.new("Bichgooth",2,bc7,p7)
        
  p8 = Prize.new(4,2)
  bc8 = BadConsequence.newLevelNumberOfTreasures("Pierdes 5 niveles y 3 tesoros visibles",5,3,0)
  monsters << Monster.new("El rey de rosa",13,bc8,p8)
        
  p9 = Prize.new(1,1)
  bc9 = BadConsequence.newLevelNumberOfTreasures("Toses los pulmones y pierdes 2 niveles",2,0,0)
  monsters << Monster.new("La que redacta en las tinieblas",2,bc9,p9)
        
  p10 = Prize.new(2,1)
  bc10 = BadConsequence.newDeath("Estos monstruos resultan bastante superficiales y te aburren mortalmente. Estas muerto.")
  monsters << Monster.new("Los hondos",8,bc10,p10)
        
  p11 = Prize.new(2,1)
  bc11 = BadConsequence.newLevelNumberOfTreasures("Pierdes 2 niveles y 2  tesoros ocultos.",2,0,2)
  monsters << Monster.new("Semillas Cthulhu",4,bc11,p11)
        
  p12 = Prize.new(2,1)
  bc12 = BadConsequence.newLevelSpecificTreasures("Te intentas escaquear. Pierdes una mano visible.",0,[TreasureKind::ONEHAND],[])
  monsters << Monster.new("Dameargo",1,bc12,p12)
        
  p13 = Prize.new(1,1)
  bc13 = BadConsequence.newLevelNumberOfTreasures("Da mucho asquito. Pierdes 3 niveles",3,0,0)
  monsters << Monster.new("Pillopólito Volante",3,bc13,p13)
        
  p14 = Prize.new(3,1)
  bc14 = BadConsequence.newDeath("No le hace gracia que pronuncien mal su nombre. Estás muerto.")
  monsters << Monster.new("Yskhtihyssg-Goth",12,bc14,p14)
        
  p15 = Prize.new(4,1)
  bc15 = BadConsequence.newDeath("La familia te atrapa. Estás muerto")
  monsters << Monster.new("Familia Feliz",1,bc15,p15)
        
  p16 = Prize.new(2,1)
  bc16 = BadConsequence.newLevelSpecificTreasures("La quinta directiva primaria te obliga a perder 2 niveles y un tesoro 2 manos visible",2,[TreasureKind::BOTHHANDS],[])
  monsters << Monster.new("Roboggoth",8,bc16,p16)
        
  p17 = Prize.new(1,1)
  bc17 = BadConsequence.newLevelSpecificTreasures("Te asusta en la noche. Pierdes un casco visible",0,[TreasureKind::HELMET],[])
  monsters << Monster.new("El Espía",5,bc17,p17)
        
  p18 = Prize.new(1,1)
  bc18 = BadConsequence.newLevelNumberOfTreasures("Menudo susto te llevas. Pierdes 2 niveles y 5 tesoros visibles.",2,5,0)
  monsters << Monster.new("El Lenguas",20,bc18,p18)

  p19 = Prize.new(1,1)
  bc19 = BadConsequence.newLevelSpecificTreasures("Te faltan manos para tanta cabeza. Pierdes 3 niveles y tus tesoros visibles de las manos",3,[TreasureKind::ONEHAND,TreasureKind::ONEHAND,TreasureKind::BOTHHANDS],[])
  monsters << Monster.new("Bicéfalo",20,bc19,p19)

  #//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  #Consultas para testear si los monstruos son correctos:
  puts "PRIMERA CONSULTA: "
  monsters.each do |i|
    if (i.combatLevel>10)
      puts i.to_s
    end
  end

  puts "SEGUNDA CONSULTA: "
  monsters.each do |i|
    if(!i.badConsequence.death)
      if(i.badConsequence.levels != 0)
        if(i.badConsequence.specificHiddenTreasures == nil && i.badConsequence.specificVisibleTreasures == nil)
          if(i.badConsequence.nVisibleTreasures == 0 && i.badConsequence.nHiddenTreasures == 0)
            puts i.to_s
          end
        else
          if(i.badConsequence.specificHiddenTreasures == nil || i.badConsequence.specificVisibleTreasures == nil)
            puts i.to_s
          end
          if(i.badConsequence.specificHiddenTreasures.size == 0 && i.badConsequence.specificVisibleTreasures.size == 0)
            puts i.to_s
          end
        end
      end
    end
  end

  puts "TERCERA CONSULTA: "
  monsters.each do |i|
    if (i.prize.level > 1)
      puts i.to_s
    end
  end

  puts "CUARTA CONSULTA: "
  buscado=[TreasureKind::HELMET, TreasureKind::ONEHAND]
  monsters.each do |i|
    if(i.badConsequence.specificVisibleTreasures!=nil)
      i.badConsequence.specificVisibleTreasures.each do |j|
        buscado.each do |k|
          if(j==k)
            puts i.to_s
          end
        end
      end
    end
  
    if(i.badConsequence.specificHiddenTreasures!=nil)
      i.badConsequence.specificHiddenTreasures.each do |j|
        buscado.each do |k|
          if(j==k)
            puts i.to_s
          end
        end
      end
    end
  end
end