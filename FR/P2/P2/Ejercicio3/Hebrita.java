/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.util.Random;
/**
 *
 * @author Míriam
 */
public class Hebrita extends Thread {

    // En este ejemplo almacenamos el número   
    // de ejecuciones del bucle principal.   
    private ProcesadorYodafy procesadorYoda;


    // En el constructor podemos pasarle alguna variable que hayamos creado en otra clase. Así podemos compartir algunos datos.   
    Hebrita(ProcesadorYodafy procesador) {
        this.procesadorYoda = procesador;
    }

    // El contenido de este método se ejecutará tras llamar al método "start()". Se trata del procesamiento de la hebra.
    public void run() {
        //synchronized (procesadorYoda) {
            this.procesadorYoda.procesa();
        //}
    }
}
