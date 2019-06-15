//
// YodafyServidorIterativo
// (CC) jjramos, 2012
//

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.logging.Level;
import java.util.logging.Logger;

public class YodafyClienteTCP {

    public static void main(String[] args) throws SocketException {

        int puerto = 8989;
        InetAddress direccion = null;
        DatagramPacket paquete;
        byte[] bufer = new byte[256];
        DatagramSocket socket;
        socket = new DatagramSocket();
        try {
            direccion = InetAddress.getByName("localhost");
        } catch (UnknownHostException ex) {
            Logger.getLogger(YodafyClienteTCP.class.getName()).log(Level.SEVERE, null, ex);
        }
        //cadena a enviar
        String cadenaEnvio = "Al monte del volcan debes ir sin demora";

        bufer = cadenaEnvio.getBytes();

        paquete = new DatagramPacket(bufer, bufer.length, direccion, puerto);
        try {
            socket.send(paquete);
        } catch (IOException ex) {
            Logger.getLogger(YodafyClienteTCP.class.getName()).log(Level.SEVERE, null, ex);
        }

        paquete = new DatagramPacket(bufer, bufer.length);
        try {
            socket.receive(paquete);
        } catch (IOException ex) {
            Logger.getLogger(YodafyClienteTCP.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        byte [] cadenaLeida = paquete.getData();
        
        // MOstremos la cadena de caracteres recibidos:
        System.out.println("Recibido: ");
        for (int i = 0; i < cadenaLeida.length; i++) {
            System.out.print((char) cadenaLeida[i]);
        }

        // Una vez terminado el servicio, cerramos el socket
        socket.close(); 
        //////////////////////////////////////////////////////
        //////////////////////////////////////////////////////
        
    }
}
