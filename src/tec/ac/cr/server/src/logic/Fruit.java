package logic;

public class Fruit extends Entity {

    public Fruit(Integer posI, Integer posJ, Integer pointsValue, Integer type){
        super(posI, posJ);
        this.pointsValue = pointsValue;
        this.id = 2;
        this.type = type;
        this.placed = 0;
        this.onScreen = 1;
    }

    private Integer pointsValue;
    private Integer id;
    private Integer type;
    private Integer placed;
    private Integer onScreen;

    public Integer getPointsValue() {
        return pointsValue;
    }

    public void setPointsValue(Integer pointsValue) {
        this.pointsValue = pointsValue;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getType() {
        return type;
    }

    public void setType(Integer type) {
        this.type = type;
    }

    public Integer getPlaced() {
        return placed;
    }

    public void setPlaced(Integer placed) {
        this.placed = placed;
    }

    public Integer getOnScreen() {
        return onScreen;
    }

    public void setOnScreen(Integer onScreen) {
        this.onScreen = onScreen;
    }
}
