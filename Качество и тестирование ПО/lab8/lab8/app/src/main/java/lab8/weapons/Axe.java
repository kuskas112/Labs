package lab8.weapons;
import lab8.*;

public class Axe implements WeaponBehavior {
    @Override
    public void useWeapon() {
        System.out.println("Powerful attack with Axe");
    }

    public String getWeaponType() {
        return "Axe";
    }
}