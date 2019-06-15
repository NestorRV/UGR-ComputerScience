/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package NapakalakiGame;

import java.util.Random;

public class CultistPlayer extends Player {

    private static int totalCultistPlayers = 0;
    private Cultist myCultistCard = null;

    public CultistPlayer(Player p, Cultist c) {
        super(p.getName());
        this.copyPlayer(p);
        myCultistCard = c;
        totalCultistPlayers++;
    }

    public static int getTotalCultistPlayers() {
        return totalCultistPlayers;
    }

    public int getCombatLevel() {
        double valor = super.getCombatLevel();
        valor += valor * 0.2;
        valor += (myCultistCard.getGainedLevels() * CultistPlayer.getTotalCultistPlayers());
        return (int) valor;
    }

    protected int getOponentLevel(Monster m) {
        return m.getCombatLevelAgainstCultistPlayer();
    }

    protected boolean shouldConvert() {
        return false;
    }

    private Treasure giveMeATreasure() {
        if (canYouGiveMeATreasure()) {
            Random r = new Random();
            int indice = r.nextInt(this.getVisibleTreasures().size()) + 1;
            Treasure tesoro = this.getVisibleTreasures().get(indice);
            getVisibleTreasures().remove(indice);
            return tesoro;
        } else {
            return null;
        }
    }

    private boolean canYouGiveMeATreasure() {
        if (getVisibleTreasures().size() > 0) {
            return true;
        } else {
            return false;
        }
    }

}
