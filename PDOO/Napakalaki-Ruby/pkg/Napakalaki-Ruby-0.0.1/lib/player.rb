#encoding: UTF-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module NapakalakiGame

  require_relative "treasure.rb"
  require_relative "dice.rb"
  require_relative "bad_consequence.rb"
  require_relative "card_dealer.rb"

  class Player
    MAXLEVEL=10
    def initialize(name)
      @name=name
      @level=1
      @dead=true
      @canISteal=true
      @enemy=nil
      @hiddenTreasures=Array.new
      @visibleTreasures=Array.new
      @pendingBadConsequence=nil
    end
  
    def getName
      return @name
    end
  
    def bringToLife
      @dead=false
    end
  
    def getCombatLevel
      bonus=0;      
      @visibleTreasures.each do |i|
        bonus+=i.getBonus
      end
      combatLevel=@level+bonus
      return combatLevel
    end

    def incrementLevels(l)
      @level+=l
    end
  
    def decrementLevels(l)
      if(@level-l >=1)
        @level-=l
      end  
    end
  
    def setPendingBadConsequence(b)
      @pendingBadConsequence=b
    end
  
    def applyPrize(m)
      nLevels = m.getLevelGained
      incrementLevels(nLevels)
      nTreasures = m.getTreasuresGained
      if(nTreasures > 0)
        dealer = CardDealer.instance
        nTreasures.times do
          treasure = dealer.nextTreasure
          #@visibleTreasures << treasure
          self.visibleTreasures << treasure
        end
      end
    end
  
    def applyBadConsequence(m)
      badConsequence = m.getBadConsequence
      nLevels = badConsequence.getLevels
      decrementLevels(nLevels)
      pendingBad = badConsequence.adjustToFitTreasureLists(@visibleTreasures, @hiddenTreasures)
      setPendingBadConsequence(pendingBad)
    end
  
    def canMakeTreasureVisible(t)
      can_make = true
      
      if(t.getType == NapakalakiGame::TreasureKind::BOTHHANDS)
        @visibleTreasures.each do |i|
          if((i.getType == t.getType || i.getType == NapakalakiGame::TreasureKind::ONEHAND) && can_make)
            can_make = false
          end
        end
      else if(t.getType == NapakalakiGame::TreasureKind::ONEHAND && can_make)
          contador=0
          @visibleTreasures.each do |i|
            if(i.getType == t.getType && can_make)
              contador=contador+1
              if(contador==2)
                can_make = false             
              end
            end
          end
        else if(can_make)
            @visibleTreasures.each do |i|
              if(i.getType == t.getType && can_make)
                can_make=false
              end
            end
          end
        end
      end
      return can_make
    end
      
  
    def howManyVisibleTreasures(tKind)
      contador=0
      @visibleTreasures.each do |i|
        if(i.getType == tKind)
          contador+=1
        end  
      end
      return contador
    end
  
    def dieIfNoTreasures
      if(@visibleTreasures == 0 && @hiddenTreasures == 0)
        @dead = true
      end
    end
  
    def isDead
      return @dead
    end
  
    def getHiddenTreasures
      @hiddenTreasures
    end
  
    def getVisibleTreasures
      @visibleTreasures    
    end
  
    def combat(m) 
      myLevel = self.getCombatLevel
      monsterLevel = m.getCombatLevel
      if(myLevel > monsterLevel)
        applyPrize(m)
        if(@level > MAXLEVEL)
          combatResult = NapakalakiGame::CombatResult::WINGAME
        else
          combatResult = NapakalakiGame::CombatResult::WIN
        end
      else
        applyBadConsequence(m)
        combatResult = NapakalakiGame::CombatResult::LOSE
      end
      return combatResult
    end
  
    def makeTreasureVisible(t) 
    
    end
  
    def discardVisibleTreasure(t) 
      @visibleTreasures.delete(t)
      if(@pendingBadConsequence != nil && !@pendingBadConsequence.isEmpty)
        @pendingBadConsequence.substractVisibleTreasure(t)
      end
      dieIfNoTreasures
    end
  
    def discardHiddenTreasure(t)
      @hiddenTreasures.delete(t)
      if(@pendingBadConsequence != nil && !@pendingBadConsequence.isEmpty)
        @pendingBadConsequence.substractHiddenTreasure(t)
      end
      dieIfNoTreasures
    
    end
  
    def validState 
      if((@pendingBadConsequence == nil || @pendingBadConsequence.isEmpty) && @hiddenTreasures <= 4)
        state=true
      else
        state=false
      end
      return state
    end
  
    def initTreasure 
    
    end
  
    def getLevels
      return @level
    end
  
    def stealTreasure(t) 
    
    end
  
    def setEnemy(enemy) 
      @enemy=enemy
    end
  
    def giveMeATreasure
      if(canYouGiveMeATreasure)
        indice=rand(@hiddenTreasures.size)+1
        tesoro=@hiddenTreasures.at(indice)
        return tesoro
      else 
        return nil
      end
      
    end
  
    def canISteal 
      return @canISteal
    end
  
    def canYouGiveMeATreasure 
      if(@hiddenTreasures.size > 0)
        puede=true
      else
        puede=false
      end
      return puede
    end
  
    def haveStolen 
      @canISteal=false
    end
  
    def discardAllTreasures
      @visibleTreasures.each { |v|
        self.discardVisibleTreasures(v)
      }
      @hiddenTreasures.each { |h| 
        self.discardHiddenTreasures(h)
      }
    end
  
    #Borrar luego, lo dejo para que main sirva
    attr_reader:name
    attr_reader:hiddenTreasures
    attr_reader:visibleTreasures
    attr_reader:level
  
    private :bringToLife,:getCombatLevel,:incrementLevels
    private :decrementLevels,:setPendingBadConsequence
    private :applyPrize,:applyBadConsequence;:canMakeTreasureVisible
    private :howManyVisibleTreasures,:dieIfNoTreasures,:giveMeATreasure
    private :canYouGiveMeATreasure,:haveStolen
    
  end

end