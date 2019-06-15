#encoding: UTF-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module NapakalakiGame

  require 'singleton'
  require_relative "treasure.rb"
  require_relative "treasure_kind.rb"
  require_relative "monster.rb"

  class CardDealer
  
    include Singleton
  
    def initialize
      @unusedMonsters = Array.new
      @usedMonsters = Array.new
      @unusedTreasures = Array.new
      @usedTreasures = Array.new
    end
  
    def initTreasureCardDeck
      t1=Treasure.new("¡Sí mi amo",4,TreasureKind::HELMET)
      @unusedTreasures << t1
      t2=Treasure.new("Botas de investigación",3,TreasureKind::SHOES)
      @unusedTreasures << t2
      t3=Treasure.new("Capucha de Cthulhu",3,TreasureKind::HELMET)
      @unusedTreasures << t3
      t4=Treasure.new("A prueba de babas",2,TreasureKind::ARMOR)
      @unusedTreasures << t4
      t5=Treasure.new("Botas de lluvia ácida",1,TreasureKind::BOTHHANDS)
      @unusedTreasures << t5
      t6=Treasure.new("Casco minero",2,TreasureKind::HELMET)
      @unusedTreasures << t6
      t7=Treasure.new("Ametralladora Thompson",2,TreasureKind::BOTHHANDS)
      @unusedTreasures << t7
      t8=Treasure.new("Camiseta de la UGR",1,TreasureKind::ARMOR)
      @unusedTreasures << t8
      t9=Treasure.new("Clavo de rail ferroviario",3,TreasureKind::ONEHAND)
      @unusedTreasures << t9
      t10=Treasure.new("Cuchillo de sushi arcano",2,TreasureKind::ONEHAND)
      @unusedTreasures << t10
      t11=Treasure.new("Fez alópodo",3,TreasureKind::HELMET)
      @unusedTreasures << t11  
      t12=Treasure.new("Hacha prehistórica",2,TreasureKind::ONEHAND)
      @unusedTreasures << t12
      t13=Treasure.new("El aparato del Pr. Tesla",4,TreasureKind::ARMOR)
      @unusedTreasures << t13
      t14=Treasure.new("Gaita",4,TreasureKind::BOTHHANDS)
      @unusedTreasures << t14
      t15=Treasure.new("Insecticida",2,TreasureKind::ONEHAND)
      @unusedTreasures << t15
      t16=Treasure.new("Escopeta de 3 cañones",4,TreasureKind::BOTHHANDS)
      @unusedTreasures << t16
      t17=Treasure.new("Garabato mistico",2,TreasureKind::ONEHAND)
      @unusedTreasures << t17
      t18=Treasure.new("La rebeca metálica",2,TreasureKind::ARMOR)
      @unusedTreasures << t18
      t19=Treasure.new("Lanzallamas",4,TreasureKind::BOTHHANDS)
      @unusedTreasures << t19
      t20=Treasure.new("Necro-comicón",1,TreasureKind::ONEHAND)
      @unusedTreasures << t20
      t21=Treasure.new("Necronomicón",5,TreasureKind::BOTHHANDS)
      @unusedTreasures << t21
      t22=Treasure.new("Linterna a 2 manos",3,TreasureKind::BOTHHANDS)
      @unusedTreasures << t22
      t23=Treasure.new("Necro-gnomicón",2,TreasureKind::ONEHAND)
      @unusedTreasures << t23
      t24=Treasure.new("Necrotelecom",2,TreasureKind::HELMET)
      @unusedTreasures << t24
      t25=Treasure.new("Mazo de los antiguos",3,TreasureKind::ONEHAND)
      @unusedTreasures << t25
      t26=Treasure.new("Necro-playboycón",3,TreasureKind::ONEHAND)
      @unusedTreasures << t26
      t27=Treasure.new("Porra preternatural",2,TreasureKind::ONEHAND)
      @unusedTreasures << t27
      t28=Treasure.new("Shogulador",1,TreasureKind::BOTHHANDS)
      @unusedTreasures << t28
      t29=Treasure.new("Varita de atizamiento",3,TreasureKind::ONEHAND)
      @unusedTreasures << t29
      t30=Treasure.new("Tentácula de pega",2,TreasureKind::HELMET)
      @unusedTreasures << t30
      t31=Treasure.new("Zapato deja-amigos",1,TreasureKind::SHOES)
      @unusedTreasures << t31
    end
  
    def initMonsterCardDeck
      p1 = Prize.new(2,1)
      bc1 = BadConsequence.newLevelSpecificTreasures("Pierdes tu armadura visible y otra oculta.",0,[TreasureKind::ARMOR],[TreasureKind::ARMOR])
      @unusedMonsters << Monster.new("3 Byakhess de bonanza",8,bc1,p1)       
      p2 = Prize.new(1,1)
      bc2 = BadConsequence.newLevelSpecificTreasures("Embobados con el lindo primigenio te descartas de tu casco visible.",0,[TreasureKind::HELMET],[])
      @unusedMonsters << Monster.new("Chibithulhu",2,bc2,p2)
      p3 = Prize.new(1,1)
      bc3 = BadConsequence.newLevelSpecificTreasures("El primordial bostezo contagioso. Pierdes el calzado visible",0,[TreasureKind::SHOES],[])
      @unusedMonsters << Monster.new("El sopor de Dunwich",2,bc3,p3)
      p4 = Prize.new(4,1)
      bc4 = BadConsequence.newLevelSpecificTreasures("Te atrapan para llevarte de fiesta y te dejan caer en mitad del vuelo. Descarta 1 mano visible y 1 mano oculta", 0,[TreasureKind::ONEHAND],[TreasureKind::ONEHAND])
      @unusedMonsters << Monster.new("Ángeles de la noche ibicenca",14,bc4,p4)       
      p5 = Prize.new(3,1)
      bc5 = BadConsequence.newLevelSpecificTreasures("Pierdes todos tus tesoros visibles",0,[TreasureKind::ARMOR,TreasureKind::ONEHAND,TreasureKind::ONEHAND,TreasureKind::BOTHHANDS,TreasureKind::HELMET,TreasureKind::SHOES],[])
      @unusedMonsters << Monster.new("El gorrón en el umbral",10,bc5,p5) 
      p6 = Prize.new(2,1)
      bc6 = BadConsequence.newLevelSpecificTreasures("Pierdes la armadura visible",0,[TreasureKind::ARMOR],[])
      @unusedMonsters << Monster.new("H.P. Munchcraft",6,bc6,p6)
      p7 = Prize.new(1,1)
      bc7 = BadConsequence.newLevelSpecificTreasures("Sientes bichos bajo la ropa. Descarta la armadura visible",0,[TreasureKind::ARMOR],[])
      @unusedMonsters << Monster.new("Bichgooth",2,bc7,p7)
      p8 = Prize.new(4,2)
      bc8 = BadConsequence.newLevelNumberOfTreasures("Pierdes 5 niveles y 3 tesoros visibles",5,3,0)
      @unusedMonsters << Monster.new("El rey de rosa",13,bc8,p8)
      p9 = Prize.new(1,1)
      bc9 = BadConsequence.newLevelNumberOfTreasures("Toses los pulmones y pierdes 2 niveles",2,0,0)
      @unusedMonsters << Monster.new("La que redacta en las tinieblas",2,bc9,p9)
      p10 = Prize.new(2,1)
      bc10 = BadConsequence.newDeath("Estos monstruos resultan bastante superficiales y te aburren mortalmente. Estas muerto.")
      @unusedMonsters << Monster.new("Los hondos",8,bc10,p10)
      p11 = Prize.new(2,1)
      bc11 = BadConsequence.newLevelNumberOfTreasures("Pierdes 2 niveles y 2  tesoros ocultos.",2,0,2)
      @unusedMonsters << Monster.new("Semillas Cthulhu",4,bc11,p11)      
      p12 = Prize.new(2,1)
      bc12 = BadConsequence.newLevelSpecificTreasures("Te intentas escaquear. Pierdes una mano visible.",0,[TreasureKind::ONEHAND],[])
      @unusedMonsters << Monster.new("Dameargo",1,bc12,p12)
      p13 = Prize.new(1,1)
      bc13 = BadConsequence.newLevelNumberOfTreasures("Da mucho asquito. Pierdes 3 niveles",3,0,0)
      @unusedMonsters << Monster.new("Pillopólito Volante",3,bc13,p13)
      p14 = Prize.new(3,1)
      bc14 = BadConsequence.newDeath("No le hace gracia que pronuncien mal su nombre. Estás muerto.")
      @unusedMonsters << Monster.new("Yskhtihyssg-Goth",12,bc14,p14)
      p15 = Prize.new(4,1)
      bc15 = BadConsequence.newDeath("La familia te atrapa. Estás muerto")
      @unusedMonsters << Monster.new("Familia Feliz",1,bc15,p15)
      p16 = Prize.new(2,1)
      bc16 = BadConsequence.newLevelSpecificTreasures("La quinta directiva primaria te obliga a perder 2 niveles y un tesoro 2 manos visible",2,[TreasureKind::BOTHHANDS],[])
      @unusedMonsters << Monster.new("Roboggoth",8,bc16,p16)
      p17 = Prize.new(1,1)
      bc17 = BadConsequence.newLevelSpecificTreasures("Te asusta en la noche. Pierdes un casco visible",0,[TreasureKind::HELMET],[])
      @unusedMonsters << Monster.new("El Espía",5,bc17,p17)
      p18 = Prize.new(1,1)
      bc18 = BadConsequence.newLevelNumberOfTreasures("Menudo susto te llevas. Pierdes 2 niveles y 5 tesoros visibles.",2,5,0)
      @unusedMonsters << Monster.new("El Lenguas",20,bc18,p18)
      p19 = Prize.new(1,1)
      bc19 = BadConsequence.newLevelSpecificTreasures("Te faltan manos para tanta cabeza. Pierdes 3 niveles y tus tesoros visibles de las manos",3,[TreasureKind::ONEHAND,TreasureKind::ONEHAND,TreasureKind::BOTHHANDS],[])
      @unusedMonsters << Monster.new("Bicéfalo",20,bc19,p19)
    end
  
    def shuffleTreasures
      @unusedTreasures.shuffle!
    end
  
    def shuffleMonsters
      @unusedMonsters.shuffle!
    end
  
    def self.getInstance
    
    end
  
    def nextTreasure
      if(@unusedTreasures.size == 0)
        aux = @usedTreasures
        @usedTreasures = @unusedTreasures
        @unusedTreasures = aux
        
        @unusedTreasures.shuffle!
      end

      sig_tesoro = @unusedTreasures.first  
      return sig_tesoro
    end
  
    def nextMonster
      if(@unusedMonsters.size == 0)
        aux = @usedMonsters
        @usedMonsters = @unusedMonsters
        @unusedMonsters = aux
        
        @unusedMonsters.shuffle!
      end

      sig_monstruo = @unusedMonsters.first  
      return sig_monstruo
    end
  
    def giveTreasureBack(t)
      @usedTreasures << t
      @unusedTreasures.delete(t)
    end
  
    def giveMonsterBack(m)
      @usedMonsters << m
      @unusedMonsters.delete(m)
    end
  
    def initCards
    
    end
  
    private:initTreasureCardDeck,:initMonsterCardDeck,:shuffleTreasures,:shuffleMonsters
    private_class_method:new
  end
  
end

