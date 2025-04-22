package lab8.chars;
import lab8.*;
public class King extends lab8.Character {
    public King(WeaponBehavior wb) {
        super(wb);
    }
    @Override
    public void display() {
        System.out.println("King");
    }

    @Override
    public String getCharType() {
        return "King";
    }
}