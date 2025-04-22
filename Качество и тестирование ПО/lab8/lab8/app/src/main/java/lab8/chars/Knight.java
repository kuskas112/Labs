package lab8.chars;
import lab8.*;
public class Knight extends lab8.Character {
    public Knight(WeaponBehavior wb) {
        super(wb);
    }
    @Override
    public void display() {
        System.out.println("Knight");
    }

    @Override
    public String getCharType() {
        return "Knight";
    }
}