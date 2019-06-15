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
    @@MAXLEVEL=10
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
    
    def copyPlayer(p)
      @name = p.name
      @level=p.level
      @dead=p.dead
      @canISteal=p.canISteal
      @enemy=p.enemy
      @hiddenTreasures=p.hiddenTreasures
      @visibleTreasures=p.visibleTreasures
      @pendingBadConsequence=p.pendingBadConsequence     
    end
    
    def self.MaxLevel
      return @@MAXLEVEL
    end
    
    protected
    
    def enemy
      return @enemy
    end
    
    def getHiddenTreasures
      @hiddenTreasures
    end
  
    def getVisibleTreasures
      @visibleTreasures    
    end
    
    public
  
    def getName
      return @name
    end
  
    def isDead
      return @dead
    end
  
    def combat(m) 
      myLevel = getCombatLevel()
      monsterLevel = getOponentLevel(m)
      if(myLevel > monsterLevel)
        applyPrize(m)
        if(@level >= @@MAXLEVEL)
          combatResult = NapakalakiGame::CombatResult::WINGAME
        else
          combatResult = NapakalakiGame::CombatResult::WIN
        end
      else
        applyBadConsequence(m)
        sc = shouldConvert
        if(sc)
          combatResult = NapakalakiGame::CombatResult::LOSEANDCONVERT
        else
          combatResult = NapakalakiGame::CombatResult::LOSE
        end
      end
      return combatResult
    end
  
    def makeTreasureVisible(t) 
      canI = canMakeTreasureVisible(t)
      if(canI)
        @visibleTreasures << t
        @hiddenTreasures.delete_at(@hiddenTreasures.index(t))
      end
    
    end
  
    def discardVisibleTreasure(t) 
      @visibleTreasures.delete_at(@visibleTreasures.index(t))
      if(@pendingBadConsequence != nil && !@pendingBadConsequence.isEmpty)
        @pendingBadConsequence.substractVisibleTreasure(t)
      end
      dieIfNoTreasures
    end
  
    def discardHiddenTreasure(t)
      @hiddenTreasures.delete_at(@hiddenTreasures.index(t))
      if(@pendingBadConsequence != nil && !@pendingBadConsequence.isEmpty)
        @pendingBadConsequence.substractHiddenTreasure(t)
      end
      dieIfNoTreasures
    end
  
    def validState 
      if((@pendingBadConsequence == nil || @pendingBadConsequence.isEmpty) && @hiddenTreasures.size <= 4)
        state=true
      else
        state=false
      end
      return state
    end
  
    def initTreasures 
      dealer = CardDealer.getInstance
      dice = Dice.instance
      bringToLife
      treasure = dealer.nextTreasure
      @hiddenTreasures << treasure
      number = dice.nextNumber
      
      if(number > 1)
        treasure = dealer.nextTreasure
        @hiddenTreasures << treasure
      end
      
      if(number == 6)
        treasure = dealer.nextTreasure
        @hiddenTreasures << treasure
      end
    end

    def getLevels
      return @level
    end
  
    def stealTreasure() 
      treasure = nil
      canI = self.canISteal
      if(canI)
        canYou = @enemy.canYouGiveMeATreasure
        if(canYou)
          treasure = @enemy.giveMeATreasure
          @hiddenTreasures << treasure
          haveStolen
        end
      end
      return treasure
    end
  
    def setEnemy(enemy) 
      @enemy=enemy
    end
 
    def canISteal 
      return @canISteal
    end
  
    def discardAllTreasures
      auxV = Array.new(@visibleTreasures)
      auxV.each { |v|
        self.discardVisibleTreasure(v)
      }
      
      auxH = Array.new(@hiddenTreasures)
      auxH.each { |h| 
        self.discardHiddenTreasure(h)
      }
    end
    
    def canYouGiveMeATreasure 
      if(@hiddenTreasures.size > 0)
        puede=true
      else
        puede=false
      end
      return puede
    end
    
    def giveMeATreasure
      if(canYouGiveMeATreasure)
        indice=rand(@hiddenTreasures.size)+1
        tesoro=@hiddenTreasures.at(indice)
        @hiddenTreasures.delete_at(indice)
        return tesoro
      else 
        return nil
      end
    end
    
    def to_s
      "#{@name}, Level: #{@level}"  
    end
    
    private
    
    def bringToLife
      @dead=false
    end

    def incrementLevels(l)
      if(@level + l <= @@MAXLEVEL)
        @level +=l
      else
        @level = @@MAXLEVEL
      end
    end
  
    def decrementLevels(l)
      if(@level-l >=1)
        @level-=l
      else
        @level = 1
      end  
    end
  
    def setPendingBadConsequence(b)
      @pendingBadConsequence=b
    end
  
    def applyPrize(m)
      nLevels = m.getLevelsGained
      incrementLevels(nLevels)
      nTreasures = m.getTreasuresGained
      if(nTreasures > 0)
        dealer = CardDealer.getInstance
        nTreasures.times do
          treasure = dealer.nextTreasure
          @hiddenTreasures << treasure
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
            if(i.getType == NapakalakiGame::TreasureKind::BOTHHANDS)
              can_make = false
            end
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
  
    def haveStolen 
      @canISteal=false
    end
    
    protected
    
    def getOponentLevel(m)
      return m.getCombatLevel
    end
    
    def shouldConvert
      d = Dice.instance
      aux = d.nextNumber
      return (aux == 1)      
    end
    
    def getCombatLevel
      bonus=0;      
      @visibleTreasures.each do |i|
        bonus+=i.getBonus
      end
      combatLevel=@level+bonus
      return combatLevel
    end
  
    #Borrar luego, lo dejo para que main sirva
    attr_reader:name
    attr_reader:hiddenTreasures
    attr_reader:visibleTreasures
    attr_reader:level
  end
end