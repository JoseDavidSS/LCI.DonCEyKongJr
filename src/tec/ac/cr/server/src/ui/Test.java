package ui;

import static logic.Game.p1Fruit;
import static logic.Game.p1Kremlin;

public class Test extends Thread {

    @Override
    public void run() {
        while (true){
            if (p1Kremlin != null){
                System.out.println(p1Kremlin.getPosI());
                System.out.println(p1Kremlin.getPosJ());
                System.out.println(p1Kremlin.getType());
                p1Kremlin = null;
            }
        }
    }
}
