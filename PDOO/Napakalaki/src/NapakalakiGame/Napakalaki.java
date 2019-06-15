/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package NapakalakiGame;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Random;

/**
 *
 * @author nestor
 */
public class Napakalaki {

    private static Napakalaki instance = null;
    private Monster currentMonster;
    private CardDealer dealer;
    private ArrayList<Player> players;
    private Player currentPlayer;
    private int currentPlayerIndex;

    private Random r;

    private Napakalaki() {
        currentMonster = null;
        dealer = CardDealer.getInstance();
        players = new ArrayList();
        currentPlayer = null;
        currentPlayerIndex = 0;

        r = new Random();
    }

    private void initPlayers(ArrayList<String> names) {
        for (String name : names) {
            Player player = new Player(name);
            players.add(player);
        }
    }

    private void setEnemies() {
        Player enemigo;
        for (Player player : players) {
            int numero_aleatorio = r.nextInt(players.size());
            enemigo = players.get(numero_aleatorio);

            if (player == enemigo) {
                enemigo = players.get((numero_aleatorio + 1) % players.size());
            }
            player.setEnemy(enemigo);
        }
    }

    public static Napakalaki getInstance() {
        if (instance == null) {
            instance = new Napakalaki();
        }
        return instance;
    }

    public Player nextPlayer() {
        Player jugador;
        if (currentPlayer == null && currentPlayerIndex == 0) {
            int numero_aleatorio = r.nextInt(players.size());
            currentPlayerIndex = numero_aleatorio;
            jugador = players.get(numero_aleatorio);
        } else {
            jugador = players.get((currentPlayerIndex + 1) % players.size());
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        }

        return jugador;
    }

    public boolean nextTurnAllowed() {
        boolean allowed;
        if (currentPlayer == null) {
            allowed = true;
        } else {
            allowed = currentPlayer.validState();
        }
        return allowed;
    }

    public CombatResult developCombat() {
        CombatResult combatResult = currentPlayer.combat(currentMonster);
        dealer.giveMonsterBack(currentMonster);
        if (combatResult == CombatResult.LOSEANDCONVERT) {
            Cultist nC = dealer.nextCultist();
            CultistPlayer cP = new CultistPlayer(currentPlayer, nC);
            players.set(currentPlayerIndex, cP);
            for(Player p : players){
                if(p.enemy == currentPlayer)
                    p.setEnemy(cP);
            }
            currentPlayer = cP;           
        }
        return combatResult;
    }

    public void discardVisibleTreasures(ArrayList<Treasure> treasures) {
        Iterator<Treasure> it = treasures.iterator();
        while (it.hasNext()) {
            Treasure treasure = it.next();
            currentPlayer.discardVisibleTreasure(treasure);
            dealer.giveTreasureBack(treasure);
        }
    }

    public void discardHiddenTreasures(ArrayList<Treasure> treasures) {
        Iterator<Treasure> it = treasures.iterator();
        while (it.hasNext()) {
            Treasure treasure = it.next();
            currentPlayer.discardHiddenTreasure(treasure);
            dealer.giveTreasureBack(treasure);
        }
    }

    public void makeTreasuresVisible(ArrayList<Treasure> treasures) {
        Iterator<Treasure> it = treasures.iterator();
        while (it.hasNext()) {
            Treasure t = it.next();
            currentPlayer.makeTreasureVisible(t);
        }
    }

    public void initGame(ArrayList<String> players) {
        this.initPlayers(players);
        this.setEnemies();
        dealer.initCards();
        this.nextTurn();
    }

    public Player getCurrentPlayer() {
        return currentPlayer;
    }

    public Monster getCurrentMonster() {
        return currentMonster;
    }

    public boolean nextTurn() {
        boolean stateOK = this.nextTurnAllowed();
        if (stateOK) {
            currentMonster = dealer.nextMonster();
            currentPlayer = this.nextPlayer();
            boolean dead = currentPlayer.isDead();
            if (dead) {
                currentPlayer.initTreasures();
            }
        }
        return stateOK;
    }

    public boolean endOfGame(CombatResult result) {
        boolean resultado;
        if (result == CombatResult.WINGAME) {
            resultado = true;
        } else {
            resultado = false;
        }
        return resultado;
    }
}
