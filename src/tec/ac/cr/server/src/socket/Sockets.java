package socket;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Sockets{

    /*
   Este metodo escuchar  lo que hace es abrir un socket en un epecifico puerto para recibir algo
    */
    public String escuchar(int puerto){
        try {
            ServerSocket servidor= new ServerSocket(puerto);
            Socket misocket=servidor.accept();
            InputStreamReader isr =new InputStreamReader(misocket.getInputStream());
            BufferedReader buff=new BufferedReader(isr);
            String mensaje=buff.readLine();
            misocket.close();
            servidor.close();
            return mensaje;
        } catch (IOException e) {
            return "";
        }

    }
    /*
   Este metodo escuchar  lo que hace es abrir un socket en un epecifico puerto para recibir algo
    */
    public void enviar(String ip ,int puerto,String mensaje) throws IOException {
        Socket misocket=new Socket(ip,puerto);
        PrintWriter pw=new PrintWriter(misocket.getOutputStream());
        pw.flush();
        pw.write(mensaje);
        pw.close();
        misocket.close();
    }
}