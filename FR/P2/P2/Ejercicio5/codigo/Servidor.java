/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author nestor
 */
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class Servidor {

    public static void main(String[] args) throws IOException {
        ArrayList<Socket> usuarios = new ArrayList<>();
        System.out.println("Servidor en funcionamiento! Hay " + usuarios.size() + " usuarios conetados al servidor.");
        ServerSocket servidor = new ServerSocket(8989);
        while (true) {
            Socket c = servidor.accept();
            usuarios.add(c);
            System.out.println("Se ha conectado un nuevo usuario. Hay " + usuarios.size() + " usuario/s conectados al servidor.");
            Runnable run = new Hebrita(c, usuarios);
            Thread hilo = new Thread(run);
            hilo.start();
        }
    }
}
