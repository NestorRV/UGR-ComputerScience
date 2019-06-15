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
public class SpecificBadConsequence extends BadConsequence {

    private ArrayList<TreasureKind> specificHiddenTreasures = new ArrayList();
    private ArrayList<TreasureKind> specificVisibleTreasures = new ArrayList();

    public SpecificBadConsequence(String t, int l, ArrayList<TreasureKind> v, ArrayList<TreasureKind> h) {
        super(t, l);
        this.specificHiddenTreasures = h;
        this.specificVisibleTreasures = v;
    }

    public boolean isEmpty() {
        boolean resultado = false;

        if (specificHiddenTreasures == null && specificVisibleTreasures == null) {
            resultado = true;
        } else if (specificHiddenTreasures.isEmpty() && specificVisibleTreasures.isEmpty()) {
            resultado = true;
        }

        return resultado;
    }
    
    public int getNVisibleTreasures() {
        return 0;
    }

    public int getNHiddenTreasures() {
        return 0;
    }

    public ArrayList<TreasureKind> getSpecificVisibleTreasures() {
        return specificVisibleTreasures;
    }

    public ArrayList<TreasureKind> getSpecificHiddenTreasures() {
        return specificHiddenTreasures;
    }
    
    public boolean getDeath() {
        return false;
    }

    public void substractVisibleTreasure(Treasure t) {
        if (specificVisibleTreasures != null && !specificVisibleTreasures.isEmpty()) {
            specificVisibleTreasures.remove(t.getType());
        }
    }

    public void substractHiddenTreasure(Treasure t) {
        if (specificHiddenTreasures != null && !specificHiddenTreasures.isEmpty()) {
            specificHiddenTreasures.remove(t.getType());
        }
    }

    public BadConsequence adjustToFitTreasureLists(ArrayList<Treasure> v, ArrayList<Treasure> h) {

        ArrayList<TreasureKind> auxV = new ArrayList();
        ArrayList<TreasureKind> auxV2 = new ArrayList();
        ArrayList<TreasureKind> auxH = new ArrayList();
        ArrayList<TreasureKind> auxH2 = new ArrayList();
        for (Treasure t : v) {
            auxV.add(t.getType());
        }
        for (Treasure t : h) {
            auxH.add(t.getType());
        }

        for (TreasureKind tV : this.specificVisibleTreasures) {
            if (auxV.contains(tV)) {
                auxV2.add(tV);
                auxV.remove(tV);
            }
        }
        for (TreasureKind tH : this.specificHiddenTreasures) {
            if (auxH.contains(tH)) {
                auxH2.add(tH);
                auxH.remove(tH);
            }
        }

        return new SpecificBadConsequence(this.getText(), 0, auxV2, auxH2);
    }

    public String toString() {
        return super.toString() + " Specific Hidden Treasures = " + specificHiddenTreasures.toString()
                + " Specific Visible Treasures = " + specificVisibleTreasures.toString() + "\n";
    }
}
