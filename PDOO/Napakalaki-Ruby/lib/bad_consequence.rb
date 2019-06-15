#encoding: UTF-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module NapakalakiGame

  require_relative "treasure_kind.rb"
  require_relative "player.rb"

  class BadConsequence
    
    @@MAXTREASURES=10
    def initialize (aText, someLevels)
      @text = aText
      @levels = someLevels
    end
  
    def getText
      return @text
    end
  
    def getLevels
      return @levels
    end
  
    def to_s
      return "Text: #{@text} Levels: #{@levels} "
    end

  end

end
