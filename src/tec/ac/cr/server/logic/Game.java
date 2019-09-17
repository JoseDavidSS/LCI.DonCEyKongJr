package tec.ac.cr.server.logic;

import java.util.ArrayList;
import java.util.List;

public class Game {

    private Game(){
        gameMatrix1 = new Integer[this.rows][this.columns];
        gameMatrix2 = new Integer[this.rows][this.columns];
        baseMatrix = new Integer[this.rows][this.columns];
        enemiesAliveArray1 = new ArrayList<>();
        enemiesAliveArray2 = new ArrayList<>();
        onScreenFruitsArray1 = new ArrayList<>();
        onScreenFruitsArray2 = new ArrayList<>();
    }

    private static Game game = null;
    private DKJr player1 = new DKJr();
    private DKJr player2 = new DKJr();
    private List<Kremlin> enemiesAliveArray1;
    private List<Kremlin> enemiesAliveArray2;
    private List<Fruit> onScreenFruitsArray1;
    private List<Fruit> onScreenFruitsArray2;
    private Integer[][] gameMatrix1;
    private Integer[][] gameMatrix2;
    private Integer[][] baseMatrix;
    private Integer rows = 24;
    private Integer columns = 16;
    private Boolean twoGames = false;

    public static Game getInstance(){
        if (game == null){
            game = new Game();
        }
        return game;
    }

    public DKJr getPlayer1() {
        return player1;
    }

    public void setPlayer1(DKJr player1) {
        this.player1 = player1;
    }

    public DKJr getPlayer2() {
        return player2;
    }

    public void setPlayer2(DKJr player2) {
        this.player2 = player2;
    }

    public List<Kremlin> getEnemiesAliveArray1() {
        return enemiesAliveArray1;
    }

    public void setEnemiesAliveArray1(List<Kremlin> enemiesAliveArray1) {
        this.enemiesAliveArray1 = enemiesAliveArray1;
    }

    public List<Kremlin> getEnemiesAliveArray2() {
        return enemiesAliveArray2;
    }

    public void setEnemiesAliveArray2(List<Kremlin> enemiesAliveArray2) {
        this.enemiesAliveArray2 = enemiesAliveArray2;
    }

    public List<Fruit> getOnScreenFruitsArray1() {
        return onScreenFruitsArray1;
    }

    public void setOnScreenFruitsArray1(List<Fruit> onScreenFruitsArray1) {
        this.onScreenFruitsArray1 = onScreenFruitsArray1;
    }

    public List<Fruit> getOnScreenFruitsArray2() {
        return onScreenFruitsArray2;
    }

    public void setOnScreenFruitsArray2(List<Fruit> onScreenFruitsArray2) {
        this.onScreenFruitsArray2 = onScreenFruitsArray2;
    }

    public Integer[][] getGameMatrix1() {
        return gameMatrix1;
    }

    public void setGameMatrix1(Integer[][] gameMatrix1) {
        this.gameMatrix1 = gameMatrix1;
    }

    public Integer[][] getGameMatrix2() {
        return gameMatrix2;
    }

    public void setGameMatrix2(Integer[][] gameMatrix2) {
        this.gameMatrix2 = gameMatrix2;
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

    public void addEnemy(Kremlin kremlin, Integer player){
        switch (player){
            case 1:
                enemiesAliveArray1.add(kremlin);
                System.out.println("Kremlin agregado al p1");
                gameMatrix1[3][5] = kremlin.getType();
                break;
            case 2:
                enemiesAliveArray2.add(kremlin);
                System.out.println("Kremlin agregado al p2");
                gameMatrix2[3][5] = kremlin.getType();
                break;
        }
    }

    public void addFruit(Fruit fruit, Integer player){
        switch (player){
            case 1:
                onScreenFruitsArray1.add(fruit);
                System.out.println("Fruta agregada al p1");
                gameMatrix1[fruit.getPosI()][fruit.getPosJ()] = 3;
                break;
            case 2:
                onScreenFruitsArray2.add(fruit);
                System.out.println("Fruta agregada al p2");
                gameMatrix2[fruit.getPosI()][fruit.getPosJ()] = 3;
                break;
        }
    }

    public void deleteFruit(Integer posI, Integer posJ, Integer player){
        Fruit fruit;
        switch (player){
            case 1:
                for (int i = 0; i < onScreenFruitsArray1.size(); i++){
                    fruit = onScreenFruitsArray1.get(i);
                    if (fruit.getPosI().equals(posI) && fruit.getPosJ().equals(posJ)){
                        onScreenFruitsArray1.remove(i);
                        gameMatrix1[posI][posJ] = baseMatrix[posI][posJ];
                    }
                }
                System.out.println("Fruta eliminada al p1");
                break;
            case 2:
                for (int i = 0; i < onScreenFruitsArray2.size(); i++){
                    fruit = onScreenFruitsArray2.get(i);
                    if (fruit.getPosI().equals(posI) && fruit.getPosJ().equals(posJ)){
                        onScreenFruitsArray2.remove(i);
                        gameMatrix2[posI][posJ] = baseMatrix[posI][posJ];
                    }
                }
                System.out.println("Fruta eliminada al p2");
                break;
        }
    }

    public void updateGameMatrix(Integer[][] gameMatrix){

    }

    public void checkEnemyColition(){

    }

    public String serializeMatrixToJson(Integer[][] gameMatrix){
        return "json";
    }

    public Integer[][] deserializeMatrixFromJson(String json){
        return this.gameMatrix1;
    }

    public void printMatrix(Integer[][] gameMatrix){
        for(int i = 0; i < this.rows; i++){
            for (int j = 0; j < this.columns; j++){
                System.out.print(gameMatrix[i][j] + " ");
            }
            System.out.println("");
        }
    }

    public void initializeGame(){
        initializeGameMatrix(gameMatrix1);
        initializeGameMatrix(gameMatrix2);
        initializeGameMatrix(baseMatrix);
    }

    public static void main(String args[]){
        Game game = getInstance();
        game.initializeGame();
        System.out.println("Hola");
    }
}
