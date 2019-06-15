//
// YodafyServidorIterativo
// (CC) jjramos, 2012
//
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Random;


//
// Nota: si esta clase extendiera la clase Thread, y el procesamiento lo hiciera el método "run()",
// ¡Podríamos realizar un procesado concurrente! 
//
public class ProcesadorYodafy {
	// Referencia a un socket para enviar/recibir las peticiones/respuestas
	private DatagramSocket socketServicio;
	
	// Para que la respuesta sea siempre diferente, usamos un generador de números aleatorios.
	private Random random;
	
	// Constructor que tiene como parámetro una referencia al socket abierto en por otra clase
	public ProcesadorYodafy(DatagramSocket socketServicio) {
		this.socketServicio=socketServicio;
		random=new Random();
	}
	
	
	// Aquí es donde se realiza el procesamiento realmente:
	void procesa(){
		
		// Como máximo leeremos un bloque de 1024 bytes. Esto se puede modificar.
		byte [] buffer=new byte[1024];
                int port;
                
		try {
			// Obtiene los flujos de escritura/lectura
			DatagramPacket paquete = new DatagramPacket(buffer, buffer.length);
                        socketServicio.receive(paquete);
                        InetAddress direccion = paquete.getAddress();
                        port = paquete.getPort();
                        buffer = paquete.getData();
			
			// Yoda hace su magia:
			// Creamos un String a partir de un array de bytes de tamaño "bytesRecibidos":
			String peticion=new String(buffer,0,buffer.length);
			// Yoda reinterpreta el mensaje:
			String respuesta=yodaDo(peticion);
			// Convertimos el String de respuesta en una array de bytes:
			buffer=respuesta.getBytes();
			
                        // Enviamos la traducción de Yoda:
			////////////////////////////////////////////////////////
			paquete = new DatagramPacket(buffer, buffer.length, direccion, port);
                        socketServicio.send(paquete);
			////////////////////////////////////////////////////////
		} catch (IOException e) {
			System.err.println("Error al obtener los flujso de entrada/salida.");
		}

	}

	// Yoda interpreta una frase y la devuelve en su "dialecto":
	private String yodaDo(String peticion) {
		// Desordenamos las palabras:
		String[] s = peticion.split(" ");
		String resultado="";
		
		for(int i=0;i<s.length;i++){
			int j=random.nextInt(s.length);
			int k=random.nextInt(s.length);
			String tmp=s[j];
			
			s[j]=s[k];
			s[k]=tmp;
		}
		
		resultado=s[0];
		for(int i=1;i<s.length;i++){
		  resultado+=" "+s[i];
		}
		
		return resultado;
	}
}
