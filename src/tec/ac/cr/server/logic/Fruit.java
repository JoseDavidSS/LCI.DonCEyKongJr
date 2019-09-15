package tec.ac.cr.server.logic;

public class Fruit extends Entity {

    public Fruit(Integer posI, Integer posJ){
        super(posI, posJ);
        this.pointsValue = 0;
    }

    private Integer pointsValue;

    public Integer getPointsValue() {
        return pointsValue;
    }

    public void setPointsValue(Integer pointsValue) {
        this.pointsValue = pointsValue;
    }
}
