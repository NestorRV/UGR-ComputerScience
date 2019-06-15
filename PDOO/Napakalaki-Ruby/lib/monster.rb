#encoding: UTF-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module NapakalakiGame

  require_relative "bad_consequence.rb"
  require_relative "prize.rb"
  require_relative "treasure_kind.rb"

  class Monster
    def initialize(name, level, bc, prize, lC)
      @name=name
      @combatLevel=level
      @prize=prize
      @badConsequence=bc
      @levelChangeAgainstCultistPlayer=lC
    end
    
    def Monster.newNotLC(name, level, bc, prize)
      new(name, level, bc, prize, 0)
    end
    
    def Monster.newLC(name, level, bc, prize, lC)
      new(name, level, bc, prize, lC)
    end
  
    def getName
      @name
    end
  
    def getCombatLevel
      @combatLevel
    end
    
    def getCombatLevelAgainstCultistPlayer
      return @levelChangeAgainstCultistPlayer + @combatLevel
    end
  
    def getBadConsequence
      @badConsequence
    end
  
    def getLevelsGained
      ganado=@prize.getLevels
      return ganado
    end
  
    def getTreasuresGained
      ganado=@prize.getTreasures
      return ganado
    end
  
    #Borrar luego, lo dejo para que lo de main sirva
    attr_reader:name
    attr_reader:combatLevel
    attr_reader:prize
    attr_reader:badConsequence
  
    def to_s
      "Nombre: #{@name} Combat Level: #{@combatLevel} \nPrize: #{@prize} \nBad Consequence: #{@badConsequence} \n \n"
    end
  end

end
