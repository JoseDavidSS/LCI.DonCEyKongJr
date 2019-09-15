package tec.ac.cr.server.logic;

public class DKJr extends Entity {

    public DKJr(){
        super(0, 0);
        this.lives = 3;
        this.currentPoints = 0;
    }

    private Integer lives;
    private Integer currentPoints;

    public Integer getLives() {
        return lives;
    }

    public void setLives(Integer lives) {
        this.lives = lives;
    }

    public Integer getCurrentPoints() {
        return currentPoints;
    }

    public void setCurrentPoints(Integer currentPoints) {
        this.currentPoints = currentPoints;
    }

    void lostLife(){
        this.lives --;
    }

    void wonLife(){
        this.lives ++;
    }

    void checkCurrentPoints(){

    }

    void addPoints(Integer points){
        this.currentPoints += points;
    }
}
