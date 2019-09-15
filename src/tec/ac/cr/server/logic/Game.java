package tec.ac.cr.server.logic;

public class Game {

    private Game(){}

    private static Game game = null;
    private DKJr player1 = new DKJr();
    private DKJr player2 = new DKJr();
    private Kremlin[] enemiesAliveArray1;
    private Kremlin[] EnemiesAliveArray2;
    private Fruit[] onScreenFruitsArray1;
    private Fruit[] onScreenFruitsArray2;
    private Integer[][] gameMatrix1;
    private Integer[][] gameMatrix2;
    private Integer rows = 30;
    private Integer columns = 30;

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

    public Kremlin[] getEnemiesAliveArray1() {
        return enemiesAliveArray1;
    }

    public void setEnemiesAliveArray1(Kremlin[] enemiesAliveArray1) {
        this.enemiesAliveArray1 = enemiesAliveArray1;
    }

    public Kremlin[] getEnemiesAliveArray2() {
        return EnemiesAliveArray2;
    }

    public void setEnemiesAliveArray2(Kremlin[] enemiesAliveArray2) {
        EnemiesAliveArray2 = enemiesAliveArray2;
    }

    public Fruit[] getOnScreenFruitsArray1() {
        return onScreenFruitsArray1;
    }

    public void setOnScreenFruitsArray1(Fruit[] onScreenFruitsArray1) {
        this.onScreenFruitsArray1 = onScreenFruitsArray1;
    }

    public Fruit[] getOnScreenFruitsArray2() {
        return onScreenFruitsArray2;
    }

    public void setOnScreenFruitsArray2(Fruit[] onScreenFruitsArray2) {
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
            for (int j = 0; j < columns; j++){
                gameMatrix[i][j] = 0;
            }
        }
    }

    public void addEnemy(Kremlin kremlin, Integer[] enemiesAliveArray){

    }

    public void addFruit(Fruit fruit, Integer[] onScreenFruitsArray){

    }

    public void deleteFruit(Integer posI, Integer posJ, Integer[] onScreenFruitsArray){

    }

    public void updateGameMatrix(Integer[][] gameMatrix){

    }

    public String serializeMatrixToJson(Integer[][] gameMatrix){
        return "json";
    }

    public Integer[][] deserializeMatrixFromJson(String json){
        return this.gameMatrix1;
    }
}
