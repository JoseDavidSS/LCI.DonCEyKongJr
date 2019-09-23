package socket;

import logic.Game;

import java.io.IOException;

public class Sala implements Runnable {

    private Integer puerto;
    private String jsonMatrix = "";
    public String ips[] = {"", "", ""};
    private Integer player = 0;
    private Integer turno = 0;
    private Sockets socket = new Sockets();
    private static Sala sala1 = null;
    private static Sala sala2 = null;

    public static Sala getInstance(Integer sala){
        if (sala == 1){
            if (sala1 == null){
                sala1 = new Sala(1, 8082);
            }
            return sala1;
        }else{
            if (sala2 == null){
                sala2 = new Sala(2, 8083);
            }
            return sala2;
        }
    }

    private Sala(Integer player, Integer puerto){
        this.player = player;
        this.puerto = puerto;
    }

    public void agregarJugador(String ip){
        ips[turno] = ip;

    }

    @Override
    public void run() {
        while(true){
            jsonMatrix = socket.escuchar(puerto);
            for (int i = 1; i < ips.length ; i++){
                try{
                    if (!ips[i].equals("")){
                        socket.enviar(ips[i], puerto, jsonMatrix);
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            try {
                Thread.sleep(1000);
                if (this.player == 1){
                    if (Game.p1Kremlin != null){
                        socket.enviar(ips[0], puerto, Game.p1Kremlin);
                        Game.p1Kremlin = null;
                    }if (Game.p1Fruit != null){
                        socket.enviar(ips[0], puerto, Game.p1Fruit);
                        Game.p1Fruit = null;
                    }
                }else{
                    if (Game.p2Kremlin != null){
                        socket.enviar(ips[0], puerto, Game.p1Kremlin);
                        Game.p2Kremlin = null;
                    }if (Game.p2Fruit != null){
                        socket.enviar(ips[0], puerto, Game.p1Fruit);
                        Game.p2Fruit = null;
                    }
                }
            }catch (IOException | InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
