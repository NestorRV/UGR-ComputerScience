import monitor.*;

class Barberia extends AbstractMonitor {
    private Condition sala = makeCondition();
    private Condition barbero = makeCondition();
    private Condition silla = makeCondition();

    //Invocado por los clientes para cortarse el pelo
    public void cortarPelo() {
        enter();
        if (!silla.isEmpty()) {
            System.out.println("Silla ocupada.");
            sala.await();
        }
        //El barbero empieza a afeitar
        barbero.signal();
        System.out.println("Cliente pelandose.");
        //La silla pasa a estar ocupada
        silla.await();
        leave();
    }

    //Invocado por el barbero para esperar (si procede) a un nueve cliente
    //y sentarlo para el corte
    public void siguienteCliente() {
        enter();
        if (sala.isEmpty() && silla.isEmpty()) {
            System.out.println("Barbero durmiendo.");
            barbero.await();
        }
        System.out.println("Barbero trabajando.");
        sala.signal();
        leave();
    }

    //Invocado por el barbero para indicar que ha terminado de cortar el pelo
    public void finCliente() {
        enter();
        System.out.println("Barbero termina de cortar.");
        silla.signal();
        leave();
    }
}

class Cliente implements Runnable {
    private Barberia barberia;
    public Thread thr;

    public Cliente(Barberia b) {
        barberia = b;
        thr = new Thread(this, "cliente");
    }

    public void run() {
        while (true) {
            barberia.cortarPelo();  //el cliente espera (si procede) y se corta el pelo
            aux.dormir_max(2000); //el cliente esta fuera de la barberia un tiempo
        }
    }
}

class Barbero implements Runnable {
    private Barberia barberia;
    public Thread thr;

    public Barbero(Barberia mon) {
        barberia = mon;
        thr = new Thread(this, "barbero");
    }

    public void run() {
        while (true) {
            barberia.siguienteCliente();
            aux.dormir_max(2500); //el barbero esta cortando el pelo
            barberia.finCliente();
        }
    }
}

class MainBarbero {
    public static void main(String[] args) {
        Barberia barberia = new Barberia();

        Barbero barbero = new Barbero(barberia);
        Cliente[] clientes = new Cliente[5];
        for (int i = 0; i < 5; i++) {
            clientes[i] = new Cliente(barberia);
        }

        barbero.thr.start();
        for (int i = 0; i < 5; i++) {
            clientes[i].thr.start();
        }
    }
}
