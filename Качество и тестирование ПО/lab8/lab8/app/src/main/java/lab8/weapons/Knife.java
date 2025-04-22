package lab8.weapons;
import lab8.*;

public class Knife implements WeaponBehavior {
    @Override
    public void useWeapon() {
        System.out.println("Stabbing attack with Knife");
    }
    public String getWeaponType() {
        return "Knife";
    }
}