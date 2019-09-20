package logic;

public abstract class Entity {

    protected Entity(Integer posI, Integer posJ){
        this.velocity = 1;
        this.onScreen = true;
        this.posI = posI;
        this.posJ = posJ;
    }

    Integer velocity;
    Boolean onScreen;
    Integer posI;
    Integer posJ;

    public Integer getVelocity() {
        return velocity;
    }

    public void setVelocity(Integer velocity) {
        this.velocity = velocity;
    }

    public Boolean getOnScreen() {
        return onScreen;
    }

    public void setOnScreen(Boolean onScreen) {
        this.onScreen = onScreen;
    }

    public Integer getPosI() {
        return posI;
    }

    public void setPosI(Integer posI) {
        this.posI = posI;
    }

    public Integer getPosJ() {
        return posJ;
    }

    public void setPosJ(Integer posJ) {
        this.posJ = posJ;
    }

    void checkCurrentPos(){

    }

}
