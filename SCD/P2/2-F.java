import monitor.*;

class Estanco extends AbstractMonitor{
    private boolean[] hay = new boolean[3];
    private Condition estanquero = makeCondition();
    private Condition[] fumadores = new Condition[3];

    public Estanco(){
        //Al principio no hay ningun ingrediente
        for (int i=0; i<3; i++)
            hay[i] = false;
        for (int i=0; i<3; i++)
            fumadores[i] = makeCondition();
    }

    //miIngrediente == ingrediente que quiere la hebra
    public void obtenerIngrediente( int miIngrediente ){
        enter();
        //Si no hay el que quiero, espero
        if (hay[miIngrediente] == false){
            fumadores[miIngrediente].await();
        }
        System.out.println("Fumador " + miIngrediente + " fumando.");
        //Ingrediente recogido
        hay[miIngrediente] = false;
        //Aviso al estanquero para que produzca el siguiente
        estanquero.signal();
        leave();
    }

    //ingrediente == ingredieente generado
    public void ponerIngrediente( int ingrediente ){
        enter();
        //Ingrediente no recogido y producido
        hay[ingrediente] = true;
        System.out.println("Estanquero produce: " + ingrediente + ".");
        //El fumador correspondiente puede fumar
        fumadores[ingrediente].signal();
        leave();
    }

    public void esperarRecogidaIngrediente(){
        enter();
        //Si no han recogido el ingrediente alguna de las hebras, espero
        if (hay[0] == true || hay[1] == true || hay[2] == true)
            estanquero.await();
        leave();
    }
}

class Fumador implements Runnable{
    int miIngrediente;
    public Thread thr;
    private Estanco estanco;

    public Fumador(Estanco e, int p_miIngrediente){
        estanco = e;
        miIngrediente = p_miIngrediente;
        thr = new Thread(this, "Fumador " + p_miIngrediente);
    }

    public void run(){
        while ( true ){
            estanco.obtenerIngrediente( miIngrediente );
            aux.dormir_max( 2000 );
            System.out.println("Fumador " + miIngrediente + " ha terminado de fumar.");
        }
    }
}

class Estanquero implements Runnable{
    public Thread thr ;
    private Estanco estanco;

    public Estanquero(Estanco e){
        estanco = e;
        thr = new Thread(this, "Estanquero");
    }

    public void run(){
        int ingrediente;
        while (true){
            ingrediente = (int) (Math.random () * 3.0); // 0,1 o 2
            estanco.ponerIngrediente( ingrediente );
            estanco.esperarRecogidaIngrediente() ;
        }
    }
}

class MainFumadores{
    public static void main(String[] args){
        Estanco estanco = new Estanco();
        Estanquero estanquero = new Estanquero(estanco);
        Fumador[] fumadores = new Fumador[3];

        fumadores[0]= new Fumador(estanco, 0);
        fumadores[1]= new Fumador(estanco, 1);
        fumadores[2]= new Fumador(estanco, 2);

        estanquero.thr.start();
        fumadores[0].thr.start();
        fumadores[1].thr.start();
        fumadores[2].thr.start();
    }
}
