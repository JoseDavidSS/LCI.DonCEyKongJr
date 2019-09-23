package logic;

import socket.Serializer;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Game {

    private Game(){}

    private static Game game = null;
    public static volatile String p1Kremlin = null;
    public static volatile String p2Kremlin = null;
    public static volatile String p1Fruit = null;
    public static volatile String p2Fruit = null;

    public static Game getInstance(){
        if (game == null){
            game = new Game();
        }
        return game;
    }

    public void addEnemy(Kremlin kremlin, Integer player) throws IOException {
        System.out.println("Kremlin agregado");
        if (player == 1){
            p1Kremlin = Serializer.serializeKremlin(kremlin);
        }else{
            p2Kremlin = Serializer.serializeKremlin(kremlin);
        }
    }

    public void addFruit(Fruit fruit, Integer player) throws IOException {
        System.out.println("Fruta agregada");
        if (player == 1){
            p1Fruit = Serializer.serializeFruit(fruit);
        }else{
            p2Fruit = Serializer.serializeFruit(fruit);
        }
    }
}
