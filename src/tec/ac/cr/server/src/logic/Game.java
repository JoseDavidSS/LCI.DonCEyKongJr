package logic;

import java.util.ArrayList;
import java.util.List;

public class Game {

    private Game(){
        gameMatrix = new Integer[this.rows][this.columns];
        baseMatrix = new Integer[this.rows][this.columns];
        enemiesAliveArray = new ArrayList<>();
        onScreenFruitsArray = new ArrayList<>();
    }

    private static Game game = null;
    private DKJr player = new DKJr();
    private List<Kremlin> enemiesAliveArray;
    private List<Fruit> onScreenFruitsArray;
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

    public DKJr getPlayer() {
        return player;
    }

    public void setPlayer(DKJr player) {
        this.player = player;
    }

    public List<Kremlin> getEnemiesAliveArray() {
        return enemiesAliveArray;
    }

    public void setEnemiesAliveArray(List<Kremlin> enemiesAliveArray) {
        this.enemiesAliveArray = enemiesAliveArray;
    }

    public List<Fruit> getOnScreenFruitsArray() {
        return onScreenFruitsArray;
    }

    public void setOnScreenFruitsArray(List<Fruit> onScreenFruitsArray) {
        this.onScreenFruitsArray = onScreenFruitsArray;
    }

    public Integer[][] getGameMatrix() {
        return gameMatrix;
    }

    public void setGameMatrix(Integer[][] gameMatrix) {
        this.gameMatrix = gameMatrix;
    }

    public Integer getRows() {
        return rows;
    }

    public void setRows(Integer rows) {
        this.rows = rows;
    }

    public Integer getColumns() {
        return columns;
    }

    public void setColumns(Integer columns) {
        this.columns = columns;
    }

    public void initializeServer(){

    }

    public void initializeGameMatrix(Integer[][] gameMatrix){
        for (int i = 0; i < this.rows; i++){
            for (int j = 0; j < this.columns; j++){
                if ((i == 20 && (j >= 12 && j <= 14)) || (i == 21 && (j == 4 || (j >= 9 && j <= 11))) || (i == 22 && (j >= 5 && j <= 8)) || (i == 23 && j <= 2)){
                    //Arbol
                    gameMatrix[i][j] = 11;
                }else if ((i == 4 && (j >= 4 && j <= 5)) || (i == 4 && j <= 8) || (i == 5 && (j >= 8 && j <= 11)) || (i == 9 && j == 2) || (i == 13 && j >= 11) || (i == 15 && (j >= 2 && j <= 3))){
                    //Piso
                    gameMatrix[i][j] = 12;
                }else if ((j == 0 && (i >= 5 && i <= 20)) || (j == 2 && ((i >= 10 && i <= 14) || (i >= 16 && i <= 20))) || (j == 4 && (i >= 5 && i <= 17)) || (j == 7 && (i <= 1 || (i >= 5 && i <= 13))) || (j == 8 && (i >= 6 && i <= 17)) || (j == 9 && i == 0) || (j == 10 && (i >= 6 && i <= 15)) || ((j == 12 || j == 14) && (i <= 12 || (i >= 14 && i <= 17)))){
                    //Liana
                    gameMatrix[i][j] = 13;
                }else if (i == 22 && j == 0){
                    //DKJr
                    gameMatrix[i][j] = 4;
                }else{
                    //Nada
                    gameMatrix[i][j] = 0;
                }
            }
        }
    }

    public void addEnemy(Kremlin kremlin, List<Kremlin> enemiesAliveArray, Integer[][] gameMatrix){
        enemiesAliveArray.add(kremlin);
        System.out.println("Kremlin agregado");
        gameMatrix[3][5] = kremlin.getType();
    }

    public void addFruit(Fruit fruit, List<Fruit> onScreenFruitsArray, Integer[][] gameMatrix){
        onScreenFruitsArray.add(fruit);
        System.out.println("Fruta agregada");
        gameMatrix[fruit.getPosI()][fruit.getPosJ()] = 3;
    }

    public void deleteFruit(Integer posI, Integer posJ, List<Fruit> onScreenFruitsArray, Integer[][] gameMatrix){
        Fruit fruit;
        for (int i = 0; i < onScreenFruitsArray.size(); i++){
            fruit = onScreenFruitsArray.get(i);
            if (fruit.getPosI().equals(posI) && fruit.getPosJ().equals(posJ)){
                onScreenFruitsArray.remove(i);
                gameMatrix[posI][posJ] = this.baseMatrix[posI][posJ];
            }
        }
        System.out.println("Fruta eliminada");
    }

    public String serializeMatrixToJson(Integer[][] gameMatrix){
        return "json";
    }

    public Integer[][] deserializeMatrixFromJson(String json){
        return this.gameMatrix;
    }

    public void printMatrix(Integer[][] gameMatrix){
        for(int i = 0; i < this.rows; i++){
            for (int j = 0; j < this.columns; j++){
                System.out.print(gameMatrix[i][j] + " ");
            }
            System.out.println("");
        }
    }

    public static void main(String args[]){
        Game game = getInstance();
        System.out.println("Hola");
    }
}
