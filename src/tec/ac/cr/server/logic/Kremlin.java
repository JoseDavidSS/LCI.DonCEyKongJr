package tec.ac.cr.server.logic;

public abstract class Kremlin extends Entity {

    public Kremlin(Integer posI, Integer posJ){
        super(posI, posJ);
        this.inVine = false;
    }

    private Boolean inVine;

    public Boolean getInVine() {
        return inVine;
    }

    public void setInVine(Boolean inVine) {
        this.inVine = inVine;
    }

    public void upgradeVelocity(){
        this.velocity += 1;
    }

    public void moveIPos(Integer i){
        this.posI += i;
    }

    public void moveJPos(Integer j){

    }

    public void choseVine(){

    }

    public abstract void checkVineEnd();
}
