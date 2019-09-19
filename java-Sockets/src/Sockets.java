import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Sockets {
    /*
   Este metodo escuchar  lo que hace es abrir un socket en un epecifico puerto para recibir algo
    */
    public void escuchar(int puerto){
        //mihilo.start();
        try {
            //System.out.println("VOY A EMPEZAR A ESCUCHAR");
            ServerSocket servidor= new ServerSocket(puerto);
            Socket misocket=servidor.accept();
            //System.out.println("LLEGUE AQUI");
            // DataInputStream flujo_entrada=new DataInputStream(misocket.getInputStream());
            InputStreamReader isr =new InputStreamReader(misocket.getInputStream());
            BufferedReader buff=new BufferedReader(isr);
            // String mensaje_texto=flujo_entrada.readUTF();
            System.out.println(buff.readLine());
            //System.out.println("LO QUE ME LLEGO FUE -"+mensaje_texto);
            misocket.close();
            servidor.close();
            //System.out.println("TERMINE DE  ESCUCHAR");


        } catch (IOException e) {

        }
    }
    /*
   Este metodo escuchar  lo que hace es abrir un socket en un epecifico puerto para recibir algo
    */
    public void enviar(String ip ,int puerto,String mensaje) throws IOException {

        Socket misocket=new Socket(ip,puerto);
        //OutputStreamWriter salida=new OutputStreamWriter("HOla");
        PrintWriter pw=new PrintWriter(misocket.getOutputStream());
        pw.flush();
        pw.write(mensaje);
        pw.close();
        misocket.close();
        //InputStreamReader isr =new InputStreamReader(misocket.getInputStream());
        //BufferedReader buff=new BufferedReader(isr);
        // BufferedWriter
        //DataOutputStream flujoSalida=new DataOutputStream(misocket.getOutputStream());
        //flujoSalida.writeUTF("Hola desde el cliente");
        //flujoSalida.close();


    }
}
