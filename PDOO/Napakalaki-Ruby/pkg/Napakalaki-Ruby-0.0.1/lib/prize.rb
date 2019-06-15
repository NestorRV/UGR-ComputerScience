#encoding: UTF-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module NapakalakiGame

  class Prize
    #Constructor
    def initialize(t, l)
      @treasures=t
      @level=l
    end
  
    def getTreasures
      @treasures
    end
  
    def getLevels
      @level
    end
  
    #Borrar luego, lo dejo para que main sirva
    attr_reader:treasures
    attr_reader:level
  
    def to_s
      "Tesoros ganados: #{@treasures} Niveles ganados: #{@level}"
    end
  end

end