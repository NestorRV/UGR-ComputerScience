#encoding: UTF-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module NapakalakiGame
  
  require 'singleton'
  require_relative "monster.rb"
  require_relative "card_dealer.rb"
  require_relative "player.rb"
  require_relative "combat_result.rb"

  class Napakalaki
    include Singleton

    def initialize
      @currentPlayer = nil
      @currentPlayerIndex = 0;
      @players = Array.new
      @dealer = CardDealer.getInstance
      @currentMonster = nil
    end

    def developCombat
      combatResult = @currentPlayer.combat(@currentMonster)
      @dealer.giveMonsterBack(@currentMonster)
      if(combatResult == NapakalakiGame::CombatResult::LOSEANDCONVERT)
        nC = @dealer.nextCultist
        cP = CultistPlayer.new(@currentPlayer, nC)
        @players[@currentPlayerIndex]=cP
        @players.each { |p|  
          if(p.enemy == cP)
            p.setEnemy(cP)
          end
        }
        @currentPlayer = cP
      end
      return combatResult    
    end
  
    def discardVisibleTreasures(treasures)
      treasures.each { |treasure|  
        @currentPlayer.discardVisibleTreasure(treasure)
        @dealer.giveTreasureBack(treasure)
      }
    end
  
    def discardHiddenTreasures(treasures)
      treasures.each { |treasure|  
        @currentPlayer.discardHiddenTreasure(treasure)
        @dealer.giveTreasureBack(treasure)
      }
    end
  
    def makeTreasuresVisible(treasures)
      treasures.each { |t|
        @currentPlayer.makeTreasureVisible(t)
      }
    end
  
    def initGame(players)
      initPlayers(players)
      setEnemies
      @dealer.initCards
      self.nextTurn
    end
  
    def getCurrentPlayer
      return @currentPlayer
    end
  
    def getCurrentMonster
      return @currentMonster
    end
  
    def nextTurn
      stateOK = nextTurnAllowed
      if (stateOK)
        @currentMonster = @dealer.nextMonster
        @currentPlayer = nextPlayer
        dead = @currentPlayer.isDead
        if(dead)
          @currentPlayer.initTreasures
        end
      end
      return stateOK
    end
  
    def endOfGame(result)
      resultado = true if (result == CombatResult::WINGAME)
      return resultado
    end
  
    private
      
    def initPlayers(names)
      names.each { |i|
        player = Player.new(i)
        @players << player
      }
    end
  
    def nextPlayer
      if(@currentPlayer == nil && @currentPlayerIndex == 0)
        numero_aleatorio=rand(@players.size)
        @currentPlayerIndex = numero_aleatorio
        jugador = @players.at(numero_aleatorio)
      else
        jugador = @players.at((@currentPlayerIndex + 1) % @players.size)
        @currentPlayerIndex = (@currentPlayerIndex + 1) % @players.size
      end
      return jugador
    end
  
    def nextTurnAllowed
      if (@currentPlayer == nil)
        allowed = true
      else
        allowed = @currentPlayer.validState
      end
      return allowed
    end
  
    def setEnemies
      @players.each { |i|  
        numero_aleatorio=rand(@players.size)
        enemy = @players.at(numero_aleatorio)
        if(enemy == i)
          enemy = @players.at((numero_aleatorio + 1) % @players.size)
        end
        i.setEnemy(enemy)
      }
    end
  end

end
