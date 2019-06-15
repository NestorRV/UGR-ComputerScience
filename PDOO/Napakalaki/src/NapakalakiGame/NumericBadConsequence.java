/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package NapakalakiGame;

import java.util.ArrayList;

/**
 *
 * @author nestor
 */
public class NumericBadConsequence extends BadConsequence {

    private int nVisibleTreasures = 0;
    private int nHiddenTreasures = 0;

    public NumericBadConsequence(String t, int l, int nVisible, int nHidden) {
        super(t, l);
        this.nVisibleTreasures = nVisible;
        this.nHiddenTreasures = nHidden;
    }

    public boolean isEmpty() {
        boolean resultado = false;

        if (nVisibleTreasures == 0 && nHiddenTreasures == 0) {
            resultado = true;
        }

        return resultado;
    }

    public int getNVisibleTreasures() {
        return nVisibleTreasures;
    }

    public int getNHiddenTreasures() {
        return nHiddenTreasures;
    }
    
    public ArrayList<TreasureKind> getSpecificVisibleTreasures() {
        return new ArrayList();
    }

    public ArrayList<TreasureKind> getSpecificHiddenTreasures() {
        return new ArrayList();
    }
    
    public boolean getDeath() {
        return false;
    }

    public void substractVisibleTreasure(Treasure t) {
        nVisibleTreasures--;
        if (nVisibleTreasures < 0) {
            nVisibleTreasures = 0;
        }
    }

    public void substractHiddenTreasure(Treasure t) {
        nHiddenTreasures--;
        if (nHiddenTreasures < 0) {
            nHiddenTreasures = 0;
        }
    }

    public BadConsequence adjustToFitTreasureLists(ArrayList<Treasure> v, ArrayList<Treasure> h) {
        int nV = 0, nH = 0;

        if (this.nVisibleTreasures >= v.size()) {
            nV = v.size();
        } else {
            nV = this.nVisibleTreasures;
        }
        if (this.nHiddenTreasures >= h.size()) {
            nH = h.size();
        } else {
            nH = this.nHiddenTreasures;
        }
        return new NumericBadConsequence(this.getText(), 0, nV, nH);
    }

    public String toString() {
        return super.toString() + " Visible Treasures = " + Integer.toString(nVisibleTreasures)
                + " Hidden Treasures = " + Integer.toString(nHiddenTreasures) + "\n";
    }
}
