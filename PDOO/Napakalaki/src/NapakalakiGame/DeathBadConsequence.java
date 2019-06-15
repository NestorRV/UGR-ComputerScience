/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package NapakalakiGame;

/**
 *
 * @author nestor
 */
public class DeathBadConsequence extends NumericBadConsequence {

    private boolean death;

    public DeathBadConsequence(String t, boolean death) {
        super(t, Player.MAXLEVEL, MAXTREASURES, MAXTREASURES);
        this.death = death;
    }

    public boolean getDeath() {
        return death;
    }
    
    public String toString() {
        return "Text = " + super.getText() + ": Estás muerto.";
    }
}
