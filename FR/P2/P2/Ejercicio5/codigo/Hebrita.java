/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author nestor
 */
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.ArrayList;

public class Hebrita implements Runnable {

    private final Socket socket;
    private DataInputStream in;
    private DataOutputStream out;
    private ArrayList<Socket> usuarios = new ArrayList<Socket>();

    public Hebrita(Socket socket, ArrayList usuarios) {
        this.socket = socket;
        this.usuarios = usuarios;
    }

    @Override
    public void run() {
        try {
            in = new DataInputStream(socket.getInputStream());
            out = new DataOutputStream(socket.getOutputStream());
            while (true) {
                String recibido = in.readUTF();
                for (int i = 0; i < usuarios.size(); i++) {
                    out = new DataOutputStream(usuarios.get(i).getOutputStream());
                    out.writeUTF(recibido);
                }
            }
        } catch (IOException ex) {
            for (int i = 0; i < usuarios.size(); i++) {
                if (usuarios.get(i) == socket) {
                    usuarios.remove(i);
                    break;
                }
            }
            System.out.println("Se ha desconectado un usuario. Hay " + usuarios.size() + " usuario/s conectados al servidor.");
        }
    }
}
