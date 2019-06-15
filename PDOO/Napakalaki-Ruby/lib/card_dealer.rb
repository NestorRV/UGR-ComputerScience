#encoding: UTF-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module NapakalakiGame

  require_relative "treasure.rb"
  require_relative "treasure_kind.rb"
  require_relative "monster.rb"
  require_relative "cultist.rb"
  require_relative "specific_bad_consequence.rb"
  require_relative "numeric_bad_consequence.rb"
  require_relative "death_bad_consequence.rb"

  class CardDealer
  
    @@instance = nil
    @@currentCultistIndex = 0
    def initialize
      @unusedMonsters = Array.new
      @usedMonsters = Array.new
      @unusedTreasures = Array.new
      @usedTreasures = Array.new
      @unusedCultists = Array.new
    end
  
    def self.getInstance
      if(@@instance == nil)
        @@instance = CardDealer.new
      end
      return @@instance
    end
  
    def nextTreasure
      if(@unusedTreasures.size == 0)
        aux = @usedTreasures
        @usedTreasures = @unusedTreasures
        @unusedTreasures = aux
        
        @unusedTreasures.shuffle!
      end

      sig_tesoro = @unusedTreasures.first
      @unusedTreasures.delete_at(0)
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
      @unusedMonsters.delete_at(0)
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
      initTreasureCardDeck
      initMonsterCardDeck
      initCultistCardDeck
    end
    
    def nextCultist
      cultist = @unusedCultists.at(@@currentCultistIndex)
      @@currentCultistIndex = (@@currentCultistIndex +1) % @@currentCultistIndex.size
      return cultist
    end
    
    private
    
    def initCultistCardDeck
      c1 = Cultist.new("Sectario", 1)
      @unusedCultists << c1
      c2 = Cultist.new("Sectario", 2)
      @unusedCultists << c2
      c3 = Cultist.new("Sectario", 1)
      @unusedCultists << c3
      c4 = Cultist.new("Sectario", 2)
      @unusedCultists << c4
      c5 = Cultist.new("Sectario", 1)
      @unusedCultists << c5
      c6 = Cultist.new("Sectario", 1)
      @unusedCultists << c6
      
      @unusedCultists.shuffle!
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
      
      @unusedTreasures.shuffle!
    end
    
    def initMonsterCardDeck
      p1 = Prize.new(2,1)
      bc1 = SpecificBadConsequence.new("Pierdes tu armadura visible y otra oculta.",0,[TreasureKind::ARMOR],[TreasureKind::ARMOR])
      @unusedMonsters << Monster.newNotLC("3 Byakhess de bonanza",8,bc1,p1)       
      p2 = Prize.new(1,1)
      bc2 = SpecificBadConsequence.new("Embobados con el lindo primigenio te descartas de tu casco visible.",0,[TreasureKind::HELMET],[])
      @unusedMonsters << Monster.newNotLC("Chibithulhu",2,bc2,p2)
      p3 = Prize.new(1,1)
      bc3 = SpecificBadConsequence.new("El primordial bostezo contagioso. Pierdes el calzado visible",0,[TreasureKind::SHOES],[])
      @unusedMonsters << Monster.newNotLC("El sopor de Dunwich",2,bc3,p3)
      p4 = Prize.new(4,1)
      bc4 = SpecificBadConsequence.new("Te atrapan para llevarte de fiesta y te dejan caer en mitad del vuelo. Descarta 1 mano visible y 1 mano oculta", 0,[TreasureKind::ONEHAND],[TreasureKind::ONEHAND])
      @unusedMonsters << Monster.newNotLC("Ángeles de la noche ibicenca",14,bc4,p4)       
      p5 = Prize.new(3,1)
      bc5 = SpecificBadConsequence.new("Pierdes todos tus tesoros visibles",0,[TreasureKind::ARMOR,TreasureKind::ONEHAND,TreasureKind::ONEHAND,TreasureKind::BOTHHANDS,TreasureKind::HELMET,TreasureKind::SHOES],[])
      @unusedMonsters << Monster.newNotLC("El gorrón en el umbral",10,bc5,p5) 
      p6 = Prize.new(2,1)
      bc6 = SpecificBadConsequence.new("Pierdes la armadura visible",0,[TreasureKind::ARMOR],[])
      @unusedMonsters << Monster.newNotLC("H.P. Munchcraft",6,bc6,p6)
      p7 = Prize.new(1,1)
      bc7 = SpecificBadConsequence.new("Sientes bichos bajo la ropa. Descarta la armadura visible",0,[TreasureKind::ARMOR],[])
      @unusedMonsters << Monster.newNotLC("Bichgooth",2,bc7,p7)
      p8 = Prize.new(4,2)
      bc8 = NumericBadConsequence.new("Pierdes 5 niveles y 3 tesoros visibles",5,3,0)
      @unusedMonsters << Monster.newNotLC("El rey de rosa",13,bc8,p8)
      p9 = Prize.new(1,1)
      bc9 = NumericBadConsequence.new("Toses los pulmones y pierdes 2 niveles",2,0,0)
      @unusedMonsters << Monster.newNotLC("La que redacta en las tinieblas",2,bc9,p9)
      p10 = Prize.new(2,1)
      bc10 = DeathBadConsequence.new("Estos monstruos resultan bastante superficiales y te aburren mortalmente. Estas muerto.")
      @unusedMonsters << Monster.newNotLC("Los hondos",8,bc10,p10)
      p11 = Prize.new(2,1)
      bc11 = NumericBadConsequence.new("Pierdes 2 niveles y 2  tesoros ocultos.",2,0,2)
      @unusedMonsters << Monster.newNotLC("Semillas Cthulhu",4,bc11,p11)      
      p12 = Prize.new(2,1)
      bc12 = SpecificBadConsequence.new("Te intentas escaquear. Pierdes una mano visible.",0,[TreasureKind::ONEHAND],[])
      @unusedMonsters << Monster.newNotLC("Dameargo",1,bc12,p12)
      p13 = Prize.new(1,1)
      bc13 = NumericBadConsequence.new("Da mucho asquito. Pierdes 3 niveles",3,0,0)
      @unusedMonsters << Monster.newNotLC("Pillopólito Volante",3,bc13,p13)
      p14 = Prize.new(3,1)
      bc14 = DeathBadConsequence.new("No le hace gracia que pronuncien mal su nombre. Estás muerto.")
      @unusedMonsters << Monster.newNotLC("Yskhtihyssg-Goth",12,bc14,p14)
      p15 = Prize.new(4,1)
      bc15 = DeathBadConsequence.new("La familia te atrapa. Estás muerto")
      @unusedMonsters << Monster.newNotLC("Familia Feliz",1,bc15,p15)
      p16 = Prize.new(2,1)
      bc16 = SpecificBadConsequence.new("La quinta directiva primaria te obliga a perder 2 niveles y un tesoro 2 manos visible",2,[TreasureKind::BOTHHANDS],[])
      @unusedMonsters << Monster.newNotLC("Roboggoth",8,bc16,p16)
      p17 = Prize.new(1,1)
      bc17 = SpecificBadConsequence.new("Te asusta en la noche. Pierdes un casco visible",0,[TreasureKind::HELMET],[])
      @unusedMonsters << Monster.newNotLC("El Espía",5,bc17,p17)
      p18 = Prize.new(1,1)
      bc18 = NumericBadConsequence.new("Menudo susto te llevas. Pierdes 2 niveles y 5 tesoros visibles.",2,5,0)
      @unusedMonsters << Monster.newNotLC("El Lenguas",20,bc18,p18)
      p19 = Prize.new(1,1)
      bc19 = SpecificBadConsequence.new("Te faltan manos para tanta cabeza. Pierdes 3 niveles y tus tesoros visibles de las manos",3,[TreasureKind::ONEHAND,TreasureKind::ONEHAND,TreasureKind::BOTHHANDS],[])
      @unusedMonsters << Monster.newNotLC("Bicéfalo",20,bc19,p19)
      
      p20 = Prize.new(3,1)
      bc20 = SpecificBadConsequence.new("Pierdes una mano visible.",0,[TreasureKind::ONEHAND],[])
      @unusedMonsters << Monster.newLC("El mal indecible impronunciable",10,bc20,p20,-2)
      p21 = Prize.new(2,1)
      bc21 = SpecificBadConsequence.new("Pierdes tus tesoros visibles. Jajaja.",0,[TreasureKind::ARMOR,TreasureKind::ONEHAND,TreasureKind::ONEHAND,TreasureKind::BOTHHANDS,TreasureKind::HELMET,TreasureKind::SHOES],[])
      @unusedMonsters << Monster.newLC("Testigos oculares",6,bc21,p21,2)
      p22 = Prize.new(2,5)
      bc22 = DeathBadConsequence.new("Hoy no es tu día de suerte. Mueres")
      @unusedMonsters << Monster.newLC("El gran cthulhu",20,bc22,p22,4)
      p23 = Prize.new(2,1)
      bc23 = NumericBadConsequence.new("Tu gobierno te recorta 2 niveles.",2,0,0)
      @unusedMonsters << Monster.newLC("Serpiente Político",8,bc23,p23,-2)
      p24 = Prize.new(1,1)
      bc24 = SpecificBadConsequence.new("Pierdes tu casco y tu armadura visible. Pierdes tus manos ocultas.",0,[TreasureKind::HELMET,TreasureKind::ARMOR],[TreasureKind::ONEHAND,TreasureKind::ONEHAND,TreasureKind::BOTHHANDS])
      @unusedMonsters << Monster.newLC("Felpuggoth",2,bc24,p24,5)
      p25 = Prize.new(4,2)
      bc25 = NumericBadConsequence.new("Pierdes 2 niveles.",2,0,0)
      @unusedMonsters << Monster.newLC("Shoggoth",16,bc25,p25,-4)
      p26 = Prize.new(1,1)
      bc26 = NumericBadConsequence.new("Pintalabios negro. Pierdes 2 niveles.",3,0,0)
      @unusedMonsters << Monster.newLC("Lolitagooth",2,bc26,p26,3)
      
      @unusedMonsters.shuffle!
    end    
    
    def shuffleCultist
      @unusedCultists.shuffle!
    end
    
    def shuffleTreasures
      @unusedTreasures.shuffle!
    end
  
    def shuffleMonsters
      @unusedMonsters.shuffle!
    end
  end
  
end

