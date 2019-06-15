/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package NapakalakiGame;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

/**
 *
 * @author nestor
 */
public class CardDealer {

    private static CardDealer instance = null;
    private ArrayList<Monster> unusedMonsters;
    private ArrayList<Monster> usedMonsters;
    private ArrayList<Treasure> unusedTreasures;
    private ArrayList<Treasure> usedTreasures;
    private ArrayList<Cultist> unusedCultists;

    private static int currentCultistIndex = 0;

    private CardDealer() {
        unusedMonsters = new ArrayList();
        usedMonsters = new ArrayList();
        unusedTreasures = new ArrayList();
        usedTreasures = new ArrayList();
        unusedCultists = new ArrayList();
    }

    private void initTreasureCardDeck() {
        Treasure t1 = new Treasure("¡Sí mi amo!", 4, TreasureKind.HELMET);
        unusedTreasures.add(t1);

        Treasure t2 = new Treasure("Botas de investigación", 3, TreasureKind.SHOES);
        unusedTreasures.add(t2);

        Treasure t3 = new Treasure("Capucha de Cthulhu", 3, TreasureKind.HELMET);
        unusedTreasures.add(t3);

        Treasure t4 = new Treasure("A prueba de babas", 2, TreasureKind.ARMOR);
        unusedTreasures.add(t4);

        Treasure t5 = new Treasure("Botas de lluvia ácida", 1, TreasureKind.BOTHHANDS);
        unusedTreasures.add(t5);

        Treasure t6 = new Treasure("Casco minero", 2, TreasureKind.HELMET);
        unusedTreasures.add(t6);

        Treasure t7 = new Treasure("Ametralladora Thompson", 2, TreasureKind.BOTHHANDS);
        unusedTreasures.add(t7);

        Treasure t8 = new Treasure("Camiseta de la UGR", 1, TreasureKind.ARMOR);
        unusedTreasures.add(t8);

        Treasure t9 = new Treasure("Clavo de rail ferroviario", 3, TreasureKind.ONEHAND);
        unusedTreasures.add(t9);

        Treasure t10 = new Treasure("Cuchillo de sushi arcano", 2, TreasureKind.ONEHAND);
        unusedTreasures.add(t10);

        Treasure t11 = new Treasure("Fez alópodo", 3, TreasureKind.HELMET);
        unusedTreasures.add(t11);

        Treasure t12 = new Treasure("Hacha prehistórica", 2, TreasureKind.ONEHAND);
        unusedTreasures.add(t12);

        Treasure t13 = new Treasure("El aparato del Pr. Tesla", 4, TreasureKind.ARMOR);
        unusedTreasures.add(t13);

        Treasure t14 = new Treasure("Gaita", 4, TreasureKind.BOTHHANDS);
        unusedTreasures.add(t14);

        Treasure t15 = new Treasure("Insecticida", 2, TreasureKind.ONEHAND);
        unusedTreasures.add(t15);

        Treasure t16 = new Treasure("Escopeta de 3 cañones", 4, TreasureKind.BOTHHANDS);
        unusedTreasures.add(t16);

        Treasure t17 = new Treasure("Garabato mistico", 2, TreasureKind.ONEHAND);
        unusedTreasures.add(t17);

        Treasure t18 = new Treasure("La rebeca metálica", 2, TreasureKind.ARMOR);
        unusedTreasures.add(t18);

        Treasure t19 = new Treasure("Lanzallamas", 4, TreasureKind.BOTHHANDS);
        unusedTreasures.add(t19);

        Treasure t20 = new Treasure("Necro-comicón", 1, TreasureKind.ONEHAND);
        unusedTreasures.add(t20);

        Treasure t21 = new Treasure("Necronomicón", 5, TreasureKind.BOTHHANDS);
        unusedTreasures.add(t21);

        Treasure t22 = new Treasure("Linterna a 2 manos", 3, TreasureKind.BOTHHANDS);
        unusedTreasures.add(t22);

        Treasure t23 = new Treasure("Necro-gnomicón", 2, TreasureKind.ONEHAND);
        unusedTreasures.add(t23);

        Treasure t24 = new Treasure("Necrotelecom", 2, TreasureKind.HELMET);
        unusedTreasures.add(t24);

        Treasure t25 = new Treasure("Mazo de los antiguos", 3, TreasureKind.ONEHAND);
        unusedTreasures.add(t25);

        Treasure t26 = new Treasure("Necro-playboycón", 3, TreasureKind.ONEHAND);
        unusedTreasures.add(t26);

        Treasure t27 = new Treasure("Porra preternatural", 2, TreasureKind.ONEHAND);
        unusedTreasures.add(t27);

        Treasure t28 = new Treasure("Shogulador", 1, TreasureKind.BOTHHANDS);
        unusedTreasures.add(t28);

        Treasure t29 = new Treasure("Varita de atizamiento", 3, TreasureKind.ONEHAND);
        unusedTreasures.add(t29);

        Treasure t30 = new Treasure("Tentácula de pega", 2, TreasureKind.HELMET);
        unusedTreasures.add(t30);

        Treasure t31 = new Treasure("Zapato deja-amigos", 1, TreasureKind.SHOES);
        unusedTreasures.add(t31);

        this.shuffleTreasures();
    }

    private void initMonsterCardDeck() {
        Prize p1 = new Prize(2, 1);
        BadConsequence bc1 = new SpecificBadConsequence("Pierdes tu armadura visible y otra oculta.", 0, new ArrayList(Arrays.asList(TreasureKind.ARMOR)), new ArrayList(Arrays.asList(TreasureKind.ARMOR)));
        unusedMonsters.add(new Monster("3 Byakhess de bonanza", 8, bc1, p1));

        Prize p2 = new Prize(1, 1);
        BadConsequence bc2 = new SpecificBadConsequence("Embobados con el lindo primigenio te descartas de tu casco visible.", 0, new ArrayList(Arrays.asList(TreasureKind.HELMET)), new ArrayList());
        unusedMonsters.add(new Monster("Chibithulhu", 2, bc2, p2));

        Prize p3 = new Prize(1, 1);
        BadConsequence bc3 = new SpecificBadConsequence("El primordial bostezo contagioso. Pierdes el calzado visible", 0, new ArrayList(Arrays.asList(TreasureKind.SHOES)), new ArrayList());
        unusedMonsters.add(new Monster("El sopor de Dunwich", 2, bc3, p3));

        Prize p4 = new Prize(4, 1);
        BadConsequence bc4 = new SpecificBadConsequence("Te atrapan para llevarte de fiesta y te dejan caer en mitad del vuelo. Descarta 1 mano visible y 1 mano oculta", 0, new ArrayList(Arrays.asList(TreasureKind.ONEHAND)), new ArrayList(Arrays.asList(TreasureKind.ONEHAND)));
        unusedMonsters.add(new Monster("Ángeles de la noche ibicenca", 14, bc4, p4));

        Prize p5 = new Prize(3, 1);
        BadConsequence bc5 = new SpecificBadConsequence("Pierdes todos tus tesoros visibles", 0, new ArrayList(Arrays.asList(TreasureKind.ARMOR, TreasureKind.ONEHAND, TreasureKind.ONEHAND, TreasureKind.BOTHHANDS, TreasureKind.HELMET, TreasureKind.SHOES)), new ArrayList());
        unusedMonsters.add(new Monster("El gorrón en el umbral", 10, bc5, p5));

        Prize p6 = new Prize(2, 1);
        BadConsequence bc6 = new SpecificBadConsequence("Pierdes la armadura visible", 0, new ArrayList(Arrays.asList(TreasureKind.ARMOR)), new ArrayList());
        unusedMonsters.add(new Monster("H.P. Munchcraft", 6, bc6, p6));

        Prize p7 = new Prize(1, 1);
        BadConsequence bc7 = new SpecificBadConsequence("Sientes bichos bajo la ropa. Descarta la armadura visible", 0, new ArrayList(Arrays.asList(TreasureKind.ARMOR)), new ArrayList());
        unusedMonsters.add(new Monster("Bichgooth", 2, bc7, p7));

        Prize p8 = new Prize(4, 2);
        BadConsequence bc8 = new NumericBadConsequence("Pierdes 5 niveles y 3 tesoros visibles", 5, 3, 0);
        unusedMonsters.add(new Monster("El rey de rosa", 13, bc8, p8));

        Prize p9 = new Prize(1, 1);
        BadConsequence bc9 = new NumericBadConsequence("Toses los pulmones y pierdes 2 niveles", 2, 0, 0);
        unusedMonsters.add(new Monster("La que redacta en las tinieblas", 2, bc9, p9));

        Prize p10 = new Prize(2, 1);
        BadConsequence bc10 = new DeathBadConsequence("Estos monstruos resultan bastante superficiales y te aburren mortalmente. Estas muerto.", true);
        unusedMonsters.add(new Monster("Los hondos", 8, bc10, p10));

        Prize p11 = new Prize(2, 1);
        BadConsequence bc11 = new NumericBadConsequence("Pierdes 2 niveles y 2  tesoros ocultos.", 2, 0, 2);
        unusedMonsters.add(new Monster("Semillas Cthulhu", 4, bc11, p11));

        Prize p12 = new Prize(2, 1);
        BadConsequence bc12 = new SpecificBadConsequence("Te intentas escaquear. Pierdes una mano visible.", 0, new ArrayList(Arrays.asList(TreasureKind.ONEHAND)), new ArrayList());
        unusedMonsters.add(new Monster("Dameargo", 1, bc12, p12));

        Prize p13 = new Prize(1, 1);
        BadConsequence bc13 = new NumericBadConsequence("Da mucho asquito. Pierdes 3 niveles", 3, 0, 0);
        unusedMonsters.add(new Monster("Pillopólito Volante", 3, bc13, p13));

        Prize p14 = new Prize(3, 1);
        BadConsequence bc14 = new DeathBadConsequence("No le hace gracia que pronuncien mal su nombre. Estás muerto.", true);
        unusedMonsters.add(new Monster("Yskhtihyssg-Goth", 12, bc14, p14));

        Prize p15 = new Prize(4, 1);
        BadConsequence bc15 = new DeathBadConsequence("La familia te atrapa. Estás muerto", true);
        unusedMonsters.add(new Monster("Familia Feliz", 1, bc15, p15));

        Prize p16 = new Prize(2, 1);
        BadConsequence bc16 = new SpecificBadConsequence("La quinta directiva primaria te obliga a perder 2 niveles y un tesoro 2 manos visible", 2, new ArrayList(Arrays.asList(TreasureKind.BOTHHANDS)), new ArrayList());
        unusedMonsters.add(new Monster("Roboggoth", 8, bc16, p16));

        Prize p17 = new Prize(1, 1);
        BadConsequence bc17 = new SpecificBadConsequence("Te asusta en la noche. Pierdes un casco visible", 0, new ArrayList(Arrays.asList(TreasureKind.HELMET)), new ArrayList());
        unusedMonsters.add(new Monster("El Espía", 5, bc17, p17));

        Prize p18 = new Prize(1, 1);
        BadConsequence bc18 = new NumericBadConsequence("Menudo susto te llevas. Pierdes 2 niveles y 5 tesoros visibles.", 2, 5, 0);
        unusedMonsters.add(new Monster("El Lenguas", 20, bc18, p18));

        Prize p19 = new Prize(1, 1);
        BadConsequence bc19 = new SpecificBadConsequence("Te faltan manos para tanta cabeza. Pierdes 3 niveles y tus tesoros visibles de las manos", 3, new ArrayList(Arrays.asList(TreasureKind.ONEHAND, TreasureKind.ONEHAND, TreasureKind.BOTHHANDS)), new ArrayList());
        unusedMonsters.add(new Monster("Bicéfalo", 20, bc19, p19));

        Prize p20 = new Prize(3, 1);
        BadConsequence bc20 = new SpecificBadConsequence("Pierdes 1 mano visible", 0, new ArrayList(Arrays.asList(TreasureKind.ONEHAND)), new ArrayList());
        unusedMonsters.add(new Monster("El mal indecible impronunciable", 10, bc20, p20, -2));

        Prize p21 = new Prize(2, 1);
        BadConsequence bc21 = new SpecificBadConsequence("Pierdes tus tesoros visibles. Jajaja", 0, new ArrayList(Arrays.asList(TreasureKind.ARMOR, TreasureKind.ONEHAND, TreasureKind.ONEHAND, TreasureKind.BOTHHANDS, TreasureKind.HELMET, TreasureKind.SHOES)), new ArrayList());
        unusedMonsters.add(new Monster("Testigos Oculares", 6, bc21, p21, 2));

        Prize p22 = new Prize(2, 5);
        BadConsequence bc22 = new DeathBadConsequence("Hoy no es tu día de suerte. Mueres", true);
        unusedMonsters.add(new Monster("El gran cthulhu", 20, bc22, p22, 4));

        Prize p23 = new Prize(2, 1);
        BadConsequence bc23 = new NumericBadConsequence("Tu gobierno te recorta 2 niveles.", 2, 0, 0);
        unusedMonsters.add(new Monster("Serpiente Político", 8, bc23, p23, -2));

        Prize p24 = new Prize(4, 2);
        BadConsequence bc24 = new SpecificBadConsequence("Pierdes tu casco y tu armadura visible. Pierdes tus manos ocultas.", 0, new ArrayList(Arrays.asList(TreasureKind.HELMET, TreasureKind.ARMOR)), new ArrayList(Arrays.asList(TreasureKind.ONEHAND, TreasureKind.ONEHAND, TreasureKind.BOTHHANDS)));
        unusedMonsters.add(new Monster("Felpuggoth", 2, bc24, p24, 5));

        Prize p25 = new Prize(1, 1);
        BadConsequence bc25 = new NumericBadConsequence("Pierdes 2 niveles.", 2, 0, 0);
        unusedMonsters.add(new Monster("Shoggoth", 16, bc25, p25, -4));

        Prize p26 = new Prize(1, 1);
        BadConsequence bc26 = new NumericBadConsequence("Pintalabios negro. Pierdes 2 niveles.", 3, 0, 0);
        unusedMonsters.add(new Monster("Lolitagooth", 2, bc26, p26, 3));

        this.shuffleMonsters();
    }

    private void shuffleTreasures() {
        Collections.shuffle(unusedTreasures);
    }

    private void shuffleMonsters() {
        Collections.shuffle(unusedMonsters);
    }

    private void shuffleCultists() {
        Collections.shuffle(unusedCultists);
    }

    private void initCultistCardDeck() {
        unusedCultists.add(new Cultist("Sectario", 1));
        unusedCultists.add(new Cultist("Sectario", 2));
        unusedCultists.add(new Cultist("Sectario", 1));
        unusedCultists.add(new Cultist("Sectario", 2));
        unusedCultists.add(new Cultist("Sectario", 1));
        unusedCultists.add(new Cultist("Sectario", 1));
        this.shuffleCultists();
    }

    public Cultist nextCultist() {
        Cultist sig_cultist;
        sig_cultist = unusedCultists.get(currentCultistIndex);
        currentCultistIndex = ((currentCultistIndex + 1) % unusedCultists.size());
        return sig_cultist;
    }

    public static CardDealer getInstance() {
        if (instance == null) {
            instance = new CardDealer();
        }
        return instance;
    }

    public Treasure nextTreasure() {
        if (unusedTreasures.isEmpty()) {
            ArrayList<Treasure> aux;
            aux = usedTreasures;
            usedTreasures = unusedTreasures;
            unusedTreasures = aux;
            Collections.shuffle(unusedTreasures);
        }

        Treasure sig_tesoro;
        sig_tesoro = unusedTreasures.get(0);
        unusedTreasures.remove(0);

        return sig_tesoro;
    }

    public Monster nextMonster() {
        if (unusedMonsters.isEmpty()) {
            ArrayList<Monster> aux;
            aux = usedMonsters;
            usedMonsters = unusedMonsters;
            unusedMonsters = aux;
            Collections.shuffle(unusedMonsters);
        }

        Monster sig_monstruo;
        sig_monstruo = unusedMonsters.get(0);
        unusedMonsters.remove(0);

        return sig_monstruo;
    }

    public void giveTreasureBack(Treasure t) {
        usedTreasures.add(t);
        unusedTreasures.remove(t);
    }

    public void giveMonsterBack(Monster m) {
        usedMonsters.add(m);
        unusedMonsters.remove(m);
    }

    public void initCards() {
        this.initTreasureCardDeck();
        this.initMonsterCardDeck();
        this.initCultistCardDeck();
    }
}
