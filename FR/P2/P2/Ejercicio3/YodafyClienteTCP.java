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
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.logging.Level;
import java.util.logging.Logger;

public class YodafyClienteTCP {

    public static void main(String[] args) {

        // Nombre del host donde se ejecuta el servidor:
        String host = "localhost";
        // Puerto en el que espera el servidor:
        int port = 8989;

        String id = args[0];

        // Socket para la conexión TCP
        Socket socketServicio = null;

        try {
            // Creamos un socket que se conecte a "host" y "port":
            //////////////////////////////////////////////////////
            socketServicio = new Socket(host, port);
            //////////////////////////////////////////////////////

            //Leer y escribir con objetos String
            PrintWriter outPrinter = null;
            BufferedReader inReader = null;
            try {
                outPrinter = new PrintWriter(socketServicio.getOutputStream(), true);
                inReader = new BufferedReader(new InputStreamReader(socketServicio.getInputStream()));
            } catch (IOException ex) {
                Logger.getLogger(YodafyClienteTCP.class.getName()).log(Level.SEVERE, null, ex);
            }

            //cadena a enviar
            String cadenaEnvio = "Al monte del volcan debes ir sin demora" +id;

            

            // Enviamos el string por el outPrinter;
            //////////////////////////////////////////////////////
            outPrinter.println(cadenaEnvio);
            //////////////////////////////////////////////////////

            //////////////////////////////////////////////////////
            
            // Leemos la respuesta del servidor. Para ello le pasamos un array de bytes, que intentará
            // rellenar. El método "read(...)" devolverá el número de bytes leídos.
            //////////////////////////////////////////////////////
            String cadenaLeida = "";
            cadenaLeida = inReader.readLine();
            //////////////////////////////////////////////////////

            // MOstremos la cadena de caracteres recibidos:
            System.out.println("Recibido: ");
            for (int i = 0; i < cadenaLeida.length(); i++) {
                System.out.print((char) cadenaLeida.charAt(i));
            }

            // Una vez terminado el servicio, cerramos el socket (automáticamente se cierran
            // el inpuStream  y el outputStream)
            //////////////////////////////////////////////////////
            socketServicio.close();
            //////////////////////////////////////////////////////

            // Excepciones:
        } catch (UnknownHostException e) {
            System.err.println("Error: Nombre de host no encontrado.");
        } catch (IOException e) {
            System.err.println("Error de entrada/salida al abrir el socket.");
        }
    }
}
