package logic;

public abstract class Kremlin extends Entity {

    public Kremlin(Integer type){
        super(3, 5);
        this.inVine = false;
        this.type = type;
    }

    private Boolean inVine;
    private Integer type;

    public Boolean getInVine() {
        return inVine;
    }

    public void setInVine(Boolean inVine) {
        this.inVine = inVine;
    }

    public Integer getType() {
        return type;
    }

    public void setType(Integer type) {
        this.type = type;
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
