#encoding: UTF-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module NapakalakiGame

  require 'singleton'

  class Dice
  
    include Singleton
  
    def initialize
    
    end
  
    def self.getInstance
    
    end
  
    def nextNumber
      numero_aleatorio=rand(6)+1
      return numero_aleatorio
    end
    private_class_method:new
  end
end

