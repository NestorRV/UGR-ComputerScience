# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module NapakalakiGame
  require_relative "cultist.rb"
  
  class CultistPlayer < Player
    @@totalCultistPlayers = 0
    def initialize(p, c)
      super(p.getName)
      self.copyPlayer(p)
      @myCultistCard = c
      @@totalCultistPlayers = @@totalCultistPlayers + 1    
    end
  
    protected
  
    def getCombatLevel
      valor = super
      valor += valor * 0.2
      valor += (@myCultistCard.getGainedLevels * CultistPlayer.getTotalCultistPlayers)
      valor = valor.truncate
      return valor
    end
  
    def getOponentLevel(m)
      return m.getCombatLevelAgainstCultistPlayer
    end
  
    def shouldConvert
      return false
    end
  
    private
  
    def giveMeATreasure
      if(canYouGiveMeATreasure)
        indice=rand(getVisibleTreasures.size)+1
        tesoro=getVisibleTreasures.at(indice)
        getVisibleTreasures.delete_at(indice)
        return tesoro
      else
        return nil
      end
    end
  
    def canYouGiveMeATreasure
      if(getVisibleTreasures.size > 0)
        puede = true
      else
        puede = false
      end
      return puede
    end
  
    public
  
    def self.getTotalCultistPlayers
      return @@totalCultistPlayers
    end
  end
end
