package lab8.weapons;
import lab8.*;

public class Sword implements WeaponBehavior {
    @Override
    public void useWeapon() {
        System.out.println("Swing attack with Sword");
    }
    public String getWeaponType() {
        return "Sword";
    }
}