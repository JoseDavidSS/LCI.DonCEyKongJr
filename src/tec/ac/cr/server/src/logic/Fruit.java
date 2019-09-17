package logic;

public class Fruit extends Entity {

    public Fruit(Integer posI, Integer posJ, Integer pointsValue){
        super(posI, posJ);
        this.pointsValue = pointsValue;
    }

    private Integer pointsValue;

    public Integer getPointsValue() {
        return pointsValue;
    }

    public void setPointsValue(Integer pointsValue) {
        this.pointsValue = pointsValue;
    }
}
