/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package NapakalakiGame;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Random;
import GUI.*;

/**
 *
 * @author nestor
 */
public class Player {

    static final int MAXLEVEL = 10;
    private String name;
    private int level;
    private boolean dead;
    private boolean canISteal;

    //Relaciones:
    protected Player enemy;
    private ArrayList<Treasure> hiddenTreasures;
    private ArrayList<Treasure> visibleTreasures;
    private BadConsequence pendingBadConsequence;

    public Player(String name) {
        this.name = name;
        this.level = 1;
        this.dead = true;
        this.canISteal = true;
        this.enemy = null;
        this.hiddenTreasures = new ArrayList();
        this.visibleTreasures = new ArrayList();
        this.pendingBadConsequence = null;
    }

    public void copyPlayer(Player p) {
        this.name = p.name;
        this.level = p.level;
        this.dead = p.dead;
        this.canISteal = p.canISteal;
        this.enemy = p.enemy;
        this.hiddenTreasures = p.hiddenTreasures;
        this.visibleTreasures = p.visibleTreasures;
        this.pendingBadConsequence = p.pendingBadConsequence;
    }

    protected int getOponentLevel(Monster m) {
        return m.getCombatLevel();
    }

    protected boolean shouldConvert() {
        Dice d = Dice.getInstance();
        int aux = d.nextNumber();
        return (aux == 1);
    }

    public String getName() {
        return name;
    }

    private void bringToLife() {
        dead = false;
    }

    public int getCombatLevel() {
        int total = 0;
        int bonus = 0;

        for (int i = 0; i < visibleTreasures.size(); i++) {
            bonus = bonus + visibleTreasures.get(i).getBonus();
        }
        total = level + bonus;
        return total;
    }

    public Player getEnemy() {
        return enemy;
    }

    private void incrementLevels(int i) {
        if (level + i <= MAXLEVEL) {
            level = level + i;
        } else {
            level = MAXLEVEL;
        }
    }

    private void decrementLevels(int i) {
        if (level - i >= 1) {
            level = level - i;
        } else {
            level = 1;
        }
    }

    private void setPendingBadConsequence(BadConsequence b) {
        pendingBadConsequence = b;
    }

    private void applyPrize(Monster m) {
        int nLevels = m.getLevelsGained();
        this.incrementLevels(nLevels);
        int nTreasures = m.getTreasuresGained();
        if (nTreasures > 0) {
            CardDealer dealer = CardDealer.getInstance();
            Treasure treasure = null;
            for (int i = 0; i < nTreasures; i++) {
                treasure = dealer.nextTreasure();
                this.hiddenTreasures.add(treasure);
            }
        }
    }

    private void applyBadConsequence(Monster m) {
        BadConsequence badConsequence = m.getBadConsequence();
        int nLevels = badConsequence.getLevels();
        this.decrementLevels(nLevels);
        BadConsequence pendingBad = badConsequence.adjustToFitTreasureLists(visibleTreasures, hiddenTreasures);
        this.setPendingBadConsequence(pendingBad);

    }

    private boolean canMakeTreasureVisible(Treasure t) {
        boolean can_make = true;
        if (t.getType() == TreasureKind.BOTHHANDS) {
            for (int i = 0; i < visibleTreasures.size(); i++) {
                if ((visibleTreasures.get(i).getType() == t.getType() || visibleTreasures.get(i).getType() == TreasureKind.ONEHAND) && can_make) {
                    can_make = false;
                }
            }
        } else if (t.getType() == TreasureKind.ONEHAND && can_make) {
            int contador = 0;
            for (int i = 0; i < visibleTreasures.size(); i++) {
                if (visibleTreasures.get(i).getType() == TreasureKind.BOTHHANDS) {
                    can_make = false;
                }
                if (visibleTreasures.get(i).getType() == t.getType() && can_make) {
                    contador++;
                    if (contador == 2) {
                        can_make = false;
                    }
                }
            }

        } else if (can_make) {
            for (int i = 0; i < visibleTreasures.size(); i++) {
                if (visibleTreasures.get(i).getType() == t.getType() && can_make) {
                    can_make = false;
                }
            }
        }

        return can_make;
    }

    private int howManyTreasureVisible(TreasureKind tKind) {
        int contador = 0;

        for (int i = 0; i < visibleTreasures.size(); i++) {
            if (visibleTreasures.get(i).getType() == tKind) {
                contador++;
            }
        }

        return contador;
    }

    private void dieIfNoTreasures() {
        if (visibleTreasures.size() == 0 && hiddenTreasures.size() == 0) {
            dead = true;
        }
    }

    public boolean isDead() {
        return dead;
    }

    public ArrayList<Treasure> getHiddenTreasures() {
        return hiddenTreasures;
    }

    public ArrayList<Treasure> getVisibleTreasures() {
        return visibleTreasures;
    }
    
    public BadConsequence getPendingBadConsequence(){
        return pendingBadConsequence;
    }

    public CombatResult combat(Monster m) {
        CombatResult combatResult = null;
        int myLevel = this.getCombatLevel();
        int monsterLevel = this.getOponentLevel(m);
        if (myLevel > monsterLevel) {
            this.applyPrize(m);
            if (this.level >= MAXLEVEL) {
                combatResult = CombatResult.WINGAME;
            } else {
                combatResult = CombatResult.WIN;
            }
        } else {
            this.applyBadConsequence(m);
            if (this.shouldConvert()) {
                combatResult = CombatResult.LOSEANDCONVERT;
            } else {
                combatResult = CombatResult.LOSE;
            }
        }
        return combatResult;
    }

    public void makeTreasureVisible(Treasure t) {
        boolean canI = this.canMakeTreasureVisible(t);
        if (canI) {
            this.visibleTreasures.add(t);
            this.hiddenTreasures.remove(t);
        }

    }

    public void discardVisibleTreasure(Treasure t) {
        this.visibleTreasures.remove(t);
        if (pendingBadConsequence != null && !pendingBadConsequence.isEmpty()) {
            this.pendingBadConsequence.substractVisibleTreasure(t);
        }
        this.dieIfNoTreasures();
    }

    public void discardHiddenTreasure(Treasure t) {
        this.hiddenTreasures.remove(t);
        if (pendingBadConsequence != null && !pendingBadConsequence.isEmpty()) {
            this.pendingBadConsequence.substractHiddenTreasure(t);
        }
        this.dieIfNoTreasures();
    }

    public boolean validState() {
        boolean state;
        if ((pendingBadConsequence == null || pendingBadConsequence.isEmpty()) && hiddenTreasures.size() <= 4) {
            state = true;
        } else {
            state = false;
        }
        return state;
    }

    public void initTreasures() {
        CardDealer dealer = CardDealer.getInstance();
        Dice dice = Dice.getInstance();
        this.bringToLife();
        Treasure treasure = dealer.nextTreasure();
        this.hiddenTreasures.add(treasure);
        int number = dice.nextNumber();
        if (number > 1) {
            treasure = dealer.nextTreasure();
            this.hiddenTreasures.add(treasure);
        }
        if (number == 6) {
            treasure = dealer.nextTreasure();
            this.hiddenTreasures.add(treasure);
        }

    }

    public int getLevels() {
        return level;
    }

    public Treasure stealTreasure() {
        Treasure treasure = null;
        boolean canI = this.canISteal();
        if (canI) {
            boolean canYou = this.enemy.canYouGiveMeATreasure();
            if (canYou) {
                treasure = this.enemy.giveMeATreasure();
                this.hiddenTreasures.add(treasure);
                this.haveStolen();
            }
        }
        return treasure;
    }

    public void setEnemy(Player enemy) {
        this.enemy = enemy;
    }

    private Treasure giveMeATreasure() {
        boolean puede = canYouGiveMeATreasure();
        Treasure t;
        if (puede) {
            Random r = new Random();
            int aleatorio = 0;
            aleatorio = r.nextInt(hiddenTreasures.size());

            t = hiddenTreasures.get(aleatorio);
            hiddenTreasures.remove(aleatorio);
        } else {
            t = null;
        }
        return t;
    }

    public boolean canISteal() {
        return canISteal;
    }

    private boolean canYouGiveMeATreasure() {
        boolean puede;
        puede = hiddenTreasures.size() > 0;
        return puede;
    }

    private void haveStolen() {
        canISteal = false;
    }

    public void discardAllTreasures() {
        ArrayList<Treasure> copiavisible = new ArrayList(visibleTreasures);
        ArrayList<Treasure> copiaoculta = new ArrayList(hiddenTreasures);
        Iterator<Treasure> vit = copiavisible.iterator();
        Iterator<Treasure> hit = copiaoculta.iterator();
        while (vit.hasNext()) {
            Treasure treasure = vit.next();
            this.discardVisibleTreasure(treasure);
        }
        while (hit.hasNext()) {
            Treasure treasure = hit.next();
            this.discardHiddenTreasure(treasure);
        }
    }

    public String toString() {
        return name + ", Level: " + level;
    }
}
