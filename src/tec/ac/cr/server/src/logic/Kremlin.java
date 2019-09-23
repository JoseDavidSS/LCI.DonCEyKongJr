package logic;

public class Kremlin extends Entity {

    public Kremlin(Integer posI, Integer posJ, Integer type){
        super(posI, posJ);
        this.inVine = 0;
        this.type = type;
        this.id = 1;
        this.previousI = -1;
        this.previousJ = -1;
        this.placed = 0;
        this.falling = 0;
        this.onScreen = 1;
    }

    private Integer inVine;
    private Integer type;
    private Integer id;
    private Integer previousI;
    private Integer previousJ;
    private Integer placed;
    private Integer falling;
    private Integer onScreen;

    public Integer getInVine() {
        return inVine;
    }

    public void setInVine(Integer inVine) {
        this.inVine = inVine;
    }

    public Integer getType() {
        return type;
    }

    public void setType(Integer type) {
        this.type = type;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getPreviousI() {
        return previousI;
    }

    public void setPreviousI(Integer previousI) {
        this.previousI = previousI;
    }

    public Integer getPreviousJ() {
        return previousJ;
    }

    public void setPreviousJ(Integer previousJ) {
        this.previousJ = previousJ;
    }

    public Integer getPlaced() {
        return placed;
    }

    public void setPlaced(Integer placed) {
        this.placed = placed;
    }

    public Integer getFalling() {
        return falling;
    }

    public void setFalling(Integer falling) {
        this.falling = falling;
    }

    public Integer getOnScreen() {
        return onScreen;
    }

    public void setOnScreen(Integer onScreen) {
        this.onScreen = onScreen;
    }
}
