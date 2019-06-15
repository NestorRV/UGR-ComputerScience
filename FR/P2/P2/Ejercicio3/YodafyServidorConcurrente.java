
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

//
// YodafyServidorConcurrente
// (CC) jjramos, 2012
//
public class YodafyServidorConcurrente {

    public static void main(String[] args) {

        // Puerto de escucha
        int port = 8989;

        // Abrimos el socket en modo pasivo, escuchando el en puerto indicado por "port"
        //////////////////////////////////////////////////
        ServerSocket socketPuerto = null;
        try {
            socketPuerto = new ServerSocket(port);
        } catch (IOException e) {
            System.out.println("Error: no se pudo atender en el puerto " + port);
        }
        //////////////////////////////////////////////////
        // Mientras ... siempre!
        Hebrita h = null;
        do {

            // Aceptamos una nueva conexión con accept()
            /////////////////////////////////////////////////
            Socket socketServicio = null;
            try {
                socketServicio = socketPuerto.accept();
            } catch (IOException e) {
                System.out.println("Error: no se pudo aceptar la conexión solicitada");
            }

            //////////////////////////////////////////////////
            // Creamos un objeto de la clase ProcesadorYodafy, pasándole como 
            // argumento el nuevo socket, para que realice el procesamiento
            // Este esquema permite que se puedan usar hebras más fácilmente.
            ProcesadorYodafy procesador = new ProcesadorYodafy(socketServicio);
            h = new Hebrita(procesador);
            h.start();
            

        } while (true);
    }

}
