package lab8.weapons;
import lab8.*;

public class Bow implements WeaponBehavior {
    @Override
    public void useWeapon() {
        System.out.println("Long-distance attack with Bow");
    }
    public String getWeaponType() {
        return "Bow";
    }
}