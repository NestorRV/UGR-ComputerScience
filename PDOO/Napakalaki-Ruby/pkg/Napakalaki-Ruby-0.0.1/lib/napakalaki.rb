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
      @dealer = CardDealer.instance
      @currentMonster = nil
    end
  
    def initPlayers(names)
      names.each { |i|
        player = Player.new(i)
        @players << player
      }
    end
  
    def nextPlayer
      if(@currentPlayer == nil && @currentPlayerIndex == 0)
        numero_aleatorio=rand(players.size)
        @currentPlayerIndex = numero_aleatorio
        jugador = @players.at(numero_aleatorio)
      else
        jugador = @players.at((@currentPlayerIndex + 1) % @players.size)
      end
      return jugador
    end
  
    def nextTurnAllowed
      if (@current_player == nil)
        allowed = true
      else
        allowed = @current_player.validState
      end
      return allowed
    end
  
    def setEnemies
      @players.each { |i|  
        numero_aleatorio=rand(players.size)
        enemy = @players.at(numero_aleatorio)
        if(enemy == i)
          enemy = @players.at((numero_aleatorio + 1) % @players.size)
        end
        i.setEnemy(enemy)
      }
    end
  
    def self.getInstance
    
    end
  
    def developCombat
      combatResult = @currentPlayer.combat(@currentMonster)
      @dealer.giveMonsterBack(@currentMonster)
      return combatResult    
    end
  
    def discardVisibleTreasures(treasures)
    
    end
  
    def discardHiddenTreasures(treasures)
    
    end
  
    def makeTreasuresVisible(treasures)
    
    end
  
    def initGame(players)
    
    end
  
    def getCurrentPlayer
      return @currentPlayer
    end
  
    def getCurrentMonster
      return @currentMonster
    end
  
    def nextTurn
    
    end
  
    def endOfGame(result)
      resultado = true if (result == CombatResult::WINGAME)
      return resultado
    end
  
    private :initPlayers,:nextPlayer,:nextTurnAllowed,:setEnemies
    private_class_method:new
  end

end