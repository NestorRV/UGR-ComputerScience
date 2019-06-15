/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package NapakalakiGame;

import java.util.ArrayList;

/**
 *
 * @author Alejandro
 */
public abstract class BadConsequence {

    static final int MAXTREASURES = 10;
    private String text;
    private int levels;
    private int nVisibleTreasures = 0;
    private int nHiddenTreasures = 0;
    private boolean death;
    private ArrayList<TreasureKind> specificHiddenTreasures = new ArrayList();
    private ArrayList<TreasureKind> specificVisibleTreasures = new ArrayList();

    public BadConsequence(String t, int l) {
        this.text = t;
        this.levels = l;
    }

    public String getText() {
        return text;
    }

    public int getLevels() {
        return levels;
    }

    public abstract boolean isEmpty();
    
    public abstract int getNVisibleTreasures();
    
    public abstract int getNHiddenTreasures();
    
    public abstract ArrayList<TreasureKind> getSpecificVisibleTreasures();
    
    public abstract ArrayList<TreasureKind> getSpecificHiddenTreasures();
    
    public abstract boolean getDeath();

    public abstract void substractVisibleTreasure(Treasure t);

    public abstract void substractHiddenTreasure(Treasure t);

    public abstract BadConsequence adjustToFitTreasureLists(ArrayList<Treasure> v, ArrayList<Treasure> h);

    public String toString() {
        return "Text = " + text + " Levels = " + Integer.toString(levels);
    }
}
