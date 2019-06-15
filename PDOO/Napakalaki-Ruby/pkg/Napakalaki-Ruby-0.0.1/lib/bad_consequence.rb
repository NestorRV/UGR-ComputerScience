#encoding: UTF-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module NapakalakiGame

  require_relative "treasure_kind.rb"

  class BadConsequence
    MAXTREASURES=10
    def initialize (aText, someLevels, someVisibleTreasures, someHiddenTreasures, someSpecificVisibleTreasures,someSpecificHiddenTreasures, death)
      @text = aText
      @levels = someLevels
      @nVisibleTreasures = someVisibleTreasures
      @nHiddenTreasures = someHiddenTreasures
      @specificVisibleTreasures = someSpecificVisibleTreasures
      @specificHiddenTreasures = someSpecificHiddenTreasures
      @death = death
    end
  
    def BadConsequence.newLevelNumberOfTreasures(t, l, nVisible, nHidden)
      new(t, l, nVisible, nHidden, nil, nil, false)        
    end
    def BadConsequence.newLevelSpecificTreasures(t, l, v, h)
      new(t, l, 0, 0, v, h, false)        
    end
    def BadConsequence.newDeath(t)
      new(t, 0, 0, 0, nil, nil, true)    
    end
  
    #Borrar luego, lo dejo para que main sirva
    attr_reader:text
    attr_reader:levels
    attr_reader:nVisibleTreasures
    attr_reader:nHiddenTreasures
    attr_reader:death
    attr_reader:specificVisibleTreasures
    attr_reader:specificHiddenTreasures
  
    def isEmpty
      resultado=false
      if(@specificHiddenTreasures == nil && @specificVisibleTreasures == nil)
        if(@nVisibleTreasures == 0 && @nHiddenTreasures == 0)
          resultado=true
        end
      else
        if(@specificHiddenTreasures.size == 0 && @specificVisibleTreasures.size == 0)
          if(@nVisibleTreasures == 0 && @nHiddenTreasures == 0)
            resultado=true
          end
        end
      end
      
      return resultado 
    end
  
    def getLevels
      @levels
    end
  
    def getNVisibleTreasures
      @nVisibleTreasures
    end
  
    def getNHiddenTreasures
      @nHiddenTreasures
    end
  
    def getSpecificVisibleTreasures
      @specificVisibleTreasures
    end
  
    def getSpecificHiddenTreasures
      @specificHiddenTreasures
    end
  
    def substractVisibleTreasure(t)
      if (!@death)
        if (@specificVisibleTreasures != nil && @specificVisibleTreasures.size != 0)
          @specificVisibleTreasures.remove(t.getType);
        else
          @nVisibleTreasures = @nVisibleTreasures - 1
          if (@nVisibleTreasures < 0)
            @nVisibleTreasures = 0
          end
        end
      end
    end
  
    def substractHiddenTreasure(t)
      if (!@death)
        if (@specificHiddenTreasures != nil && @specificHiddenTreasures.size != 0)
          @specificHiddenTreasures.remove(t.getType);
        else
          @nHiddenTreasures = @nHiddenTreasures - 1
          if (@nHiddenTreasures < 0)
            @nHiddenTreasures = 0
          end
        end
      end
    end
  
    def adjustToFitTreasureLists(v, h)
      if(@specificHiddenTreasures == nil || @specificVisibleTreasures == nil)
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
        bc = newLevelNumberOfTreasures(@text, @levels, nV, nH)
        return bc
      
      else
        auxV = ArrayList.new
        auxV2 = ArrayList.new
        auxH = ArrayList.new
        auxH2 = ArrayList.new
        v.each { |t|  
          auxV << t.getType
        }
        h.each { |t|  
          auxH << t.getType
        }
        
        @specificVisibleTreasures.each { |tV|  
          if(auxV.include?(tV))
            auxV2 << tV
            auxV.delete(tV)
          end
        }
        @specificHiddenTreasures.each { |tH|  
          if(auxH.include?(tH))
            auxH2 << tH
            auxH.delete(tH)
          end
        }
      end
      bc = newLevelSpecificTreasures(@text, @levels, auxV2, auxH2)
      return bc
    
    end
  
    def to_s
      if ((@specificHiddenTreasures == nil || @specificVisibleTreasures == nil) && !(@death))
        "Text: #{@text} Levels: #{@levels} Visible Treasures: #{@nVisibleTreasures} Hidden Treasures: #{@nHiddenTreasures} Death: #{@death}"
      elsif ((@specificHiddenTreasures != nil || @specificVisibleTreasures != nil) && !(@death))
        "Text: #{@text} Levels: #{@levels} Visible Treasures: #{@nVisibleTreasures} Hidden Treasures: #{@nHiddenTreasures} Death: #{@death} Specific Hidden Treasures: #{@specificVisibleTreasures} Specific Visible Treasures: #{@specificHiddenTreasures}"
      else
        "Text: #{@text} Death: true"  
      end
    end
  
    private_class_method:new
  end

end
