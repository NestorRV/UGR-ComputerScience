/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package NapakalakiGame;

public class Monster {

    private String name;
    private int combatLevel;
    private Prize prize;
    private BadConsequence badconsequence;
    private int levelChangeAgainstCultistPlayer;

    public Monster(String name, int level, BadConsequence bc, Prize prize) {
        this.name = name;
        combatLevel = level;
        this.prize = prize;
        this.badconsequence = bc;
    }

    public Monster(String name, int level, BadConsequence bc, Prize prize, int lC) {
        this.name = name;
        combatLevel = level;
        this.prize = prize;
        this.badconsequence = bc;
        levelChangeAgainstCultistPlayer = lC;
    }

    public String getName() {
        return name;
    }

    public int getCombatLevel() {
        return combatLevel;
    }

    public int getCombatLevelAgainstCultistPlayer() {
        return combatLevel + levelChangeAgainstCultistPlayer;
    }

    public Prize getPrize() {
        return prize;
    }

    public BadConsequence getBadConsequence() {
        return badconsequence;
    }

    public int getLevelsGained() {
        int levels = 0;
        levels = prize.getLevel();
        return levels;
    }

    public int getTreasuresGained() {
        int treasures = 0;
        treasures = prize.getTreasures();
        return treasures;
    }

    public String toString() {
        return "Monster = " + name + "; combatLevel = " + Integer.toString(combatLevel) + ";\nPrize: " + prize.toString() + ";\nBadConsequence: " + badconsequence.toString();
    }
}
