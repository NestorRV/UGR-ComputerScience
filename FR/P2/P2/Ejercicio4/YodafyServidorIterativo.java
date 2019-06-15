import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.DatagramSocket;
import java.net.ServerSocket;
import java.net.Socket;

//
// YodafyServidorIterativo
// (CC) jjramos, 2012
//
public class YodafyServidorIterativo {

	public static void main(String[] args) {
	
		// Puerto de escucha
		int port=8989;
		// array de bytes auxiliar para recibir o enviar datos.
		byte []buffer=new byte[256];
		
		try {
			// Abrimos el socket en modo pasivo, escuchando el en puerto indicado por "port"
			//////////////////////////////////////////////////
			DatagramSocket socketServidor=new DatagramSocket(port);
			//////////////////////////////////////////////////
			
			// Mientras ... siempre!
			do {
				// Creamos un objeto de la clase ProcesadorYodafy, pasándole como 
				// argumento el nuevo socket, para que realice el procesamiento
				// Este esquema permite que se puedan usar hebras más fácilmente.
				ProcesadorYodafy procesador=new ProcesadorYodafy(socketServidor);
				procesador.procesa();
			} while (true);
			
		} catch (IOException e) {
			System.err.println("Error al escuchar en el puerto "+port);
		}

	}

}
