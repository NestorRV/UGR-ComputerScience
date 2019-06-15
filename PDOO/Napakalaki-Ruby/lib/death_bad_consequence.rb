# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require_relative "bad_consequence"
require_relative "player"

module NapakalakiGame
  
  class DeathBadConsequence < NumericBadConsequence
    
    def initialize (aText)
      super(aText, Player.MaxLevel, @@MAXTREASURES, @@MAXTREASURES)
      @death = true
    end
    
    def getDeath
      @death
    end
    
    def to_s
      return "#{super} Death: true "
    end

  end

end
