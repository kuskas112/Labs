package lab8.chars;
import lab8.*;
public class Queen extends lab8.Character {
    public Queen(WeaponBehavior wb) {
        super(wb);
    }
    @Override
    public void display() {
        System.out.println("Queen");
    }

    @Override
    public String getCharType() {
        return "Queen";
    }
}