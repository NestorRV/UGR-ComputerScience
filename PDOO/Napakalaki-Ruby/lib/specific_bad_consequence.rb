# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require_relative "bad_consequence"

module NapakalakiGame
  
  class SpecificBadConsequence < BadConsequence
  
    def initialize (aText, someLevels, someSpecificVisibleTreasures,someSpecificHiddenTreasures)
      super(aText, someLevels)
      @specificVisibleTreasures = someSpecificVisibleTreasures
      @specificHiddenTreasures = someSpecificHiddenTreasures
    end
    
    def isEmpty
      resultado = false
      if(@specificHiddenTreasures == nil && @specificVisibleTreasures == nil)
          resultado=true
      else
        if(@specificHiddenTreasures.empty? && @specificVisibleTreasures.empty?)
            resultado=true
        end
      end
      return resultado 
    end
    
    def getNVisibleTreasures
      return 0
    end

    def getNHiddenTreasures
      return 0
    end
    
    def getSpecificVisibleTreasures
      return @specificVisibleTreasures
    end
  
    def getSpecificHiddenTreasures
      return @specificHiddenTreasures
    end
    
    def getDeath
      return false
    end
    
    def substractVisibleTreasure(t)
        if (@specificVisibleTreasures != nil && @specificVisibleTreasures.empty?)
          @specificVisibleTreasures.remove(t.getType);
        
        end
    end
  
    def substractHiddenTreasure(t)
        if (@specificHiddenTreasures != nil && @specificHiddenTreasures.empty?)
          @specificHiddenTreasures.remove(t.getType);
        
      end
    end
  
    def adjustToFitTreasureLists(v, h)
        auxV = Array.new
        auxV2 = Array.new
        auxH = Array.new
        auxH2 = Array.new
        v.each { |t|  
          auxV << t.getType
        }
        h.each { |t|  
          auxH << t.getType
        }
        
        @specificVisibleTreasures.each { |tV|  
          if(auxV.include?(tV))
            auxV2 << tV
            auxV.delete_at(auxV.index(tV))
          end
        }
        @specificHiddenTreasures.each { |tH|  
          if(auxH.include?(tH))
            auxH2 << tH
            auxH.delete_at(auxH.index(tH))
          end
        }
      bc = SpecificBadConsequence.new(@text, 0, auxV2, auxH2)
      return bc
    
    end
    
    def to_s
      return "#{super} Visible Treasures: #{@nVisibleTreasures} Hidden Treasures: #{@nHiddenTreasures} Death: #{@death} Specific Hidden Treasures: #{@specificVisibleTreasures} Specific Visible Treasures: #{@specificHiddenTreasures}"
    end
    
  end
  
end
