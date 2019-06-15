# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module NapakalakiGame
  class NumericBadConsequence < BadConsequence

    def initialize (aText, someLevels, someVisibleTreasures, someHiddenTreasures)
      super(aText, someLevels)
      @nVisibleTreasures = someVisibleTreasures
      @nHiddenTreasures = someHiddenTreasures
    end

    def isEmpty
      resultado=false

      if(@nVisibleTreasures == 0 && @nHiddenTreasures == 0)
        resultado=true
      end

      return resultado

    end

    def getNVisibleTreasures
      @nVisibleTreasures
    end

    def getNHiddenTreasures
      @nHiddenTreasures
    end
    
    def getSpecificVisibleTreasures
      return Array.new
    end
  
    def getSpecificHiddenTreasures
      return Array.new
    end
    
    def getDeath
      return false
    end

    def substractVisibleTreasure(t)
      @nVisibleTreasures = @nVisibleTreasures - 1

      if(@nVisibleTreasures < 0)
        @nVisibleTreasures = 0
      end

    end

    def substractHiddenTreasure(t)
      @nHiddenTreasures = @nHiddenTreasures - 1
      if (@nHiddenTreasures < 0)
        @nHiddenTreasures = 0
      end
    end

    def adjustToFitTreasureLists(v, h)
      if(@nVisibleTreasures >= v.size)
        nV = v.size
      else
        nV = @nVisibleTreasures
      end
      if(@nHiddenTreasures >= h.size)
        nH = h.size
      else
        nH = @nHiddenTreasures
      end
      bc = NumericBadConsequence.new(@text, 0, nV, nH)
      return bc
    end
    
    def to_s
        return "#{super} Visible Treasures: #{@nVisibleTreasures} Hidden Treasures: #{@nHiddenTreasures} Death: #{@death}" 
    end

  end

end
