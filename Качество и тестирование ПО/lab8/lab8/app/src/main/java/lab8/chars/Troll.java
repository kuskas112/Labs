package lab8.chars;
import lab8.*;
public class Troll extends lab8.Character {
    public Troll(WeaponBehavior wb) {
        super(wb);
    }
    @Override
    public void display() {
        System.out.println("Troll");
    }

    @Override
    public String getCharType() {
        return "Troll";
    }
}