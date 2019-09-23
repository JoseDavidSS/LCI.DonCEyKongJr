package logic;

public abstract class Entity {

    public Entity(Integer posI, Integer posJ){
        this.velocity = 1;
        this.posI = posI;
        this.posJ = posJ;
    }

    public Integer velocity;
    public Integer posI;
    public Integer posJ;

    public Integer getVelocity() {
        return velocity;
    }

    public void setVelocity(Integer velocity) {
        this.velocity = velocity;
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

}
