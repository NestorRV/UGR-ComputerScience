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
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JEditorPane;

public class Cliente implements Runnable {

    private final Socket cliente;
    private final DataInputStream in;
    private final DataOutputStream out;
    private final JEditorPane panel;
    private String mensajes = "";

    public Cliente(JEditorPane panel) throws IOException {
        this.panel = panel;
        this.cliente = new Socket("localhost", 8989);
        this.in = new DataInputStream(cliente.getInputStream());
        this.out = new DataOutputStream(cliente.getOutputStream());
    }

    @Override
    public void run() {
        while (true) {
            try {
                mensajes += in.readUTF();
            } catch (IOException ex) {
                Logger.getLogger(Cliente.class.getName()).log(Level.SEVERE, null, ex);
            }
            panel.setText(mensajes);
        }
    }

    public void enviarMsg(String mensajeEnviar) throws IOException {
        out.writeUTF(mensajeEnviar);
    }
}
