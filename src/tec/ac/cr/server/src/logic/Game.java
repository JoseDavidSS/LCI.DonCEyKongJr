package logic;

import java.util.ArrayList;
import java.util.List;

public class Game {

    private Game(){
        gameMatrix = new Integer[this.rows][this.columns];
        baseMatrix = new Integer[this.rows][this.columns];
    }

    private static Game game = null;
    public static volatile Kremlin p1Kremlin = null;
    public static volatile Kremlin p2Kremlin = null;
    public static volatile Fruit p1Fruit = null;
    public static volatile Fruit p2Fruit = null;
    private Integer[][] gameMatrix;
    private Integer[][] baseMatrix;
    private Integer rows = 24;
    private Integer columns = 16;

    public static Game getInstance(){
        if (game == null){
            game = new Game();
        }
        return game;
    }

    public void addEnemy(Kremlin kremlin, Integer player){
        System.out.println("Kremlin agregado");
        if (player == 1){
            p1Kremlin = kremlin;
        }else{
            p2Kremlin = kremlin;
        }
    }

    public void addFruit(Fruit fruit, Integer player){
        System.out.println("Fruta agregada");
        if (player == 1){
            p1Fruit = fruit;
        }else{
            p2Fruit = fruit;
        }
    }
}
