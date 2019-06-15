#encoding: UTF-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module NapakalakiGame

  require_relative "treasure_kind.rb"

  class Treasure

    def initialize(name, bonus,t)
      @name=name
      @bonus=bonus
      @type=t
    end
  
    def getName
      return @name
    end
  
    def getBonus
      return @bonus
    end
  
    def getType
      return @type
    end
    
    def to_s
      "Name: #{@name}, Bonus: #{@bonus}, Type: #{@type}"
    end
  
    #Borrar luego, lo dejo para que main sirva
    attr_reader:name
    attr_reader:bonus
    attr_reader:type
  end

end
