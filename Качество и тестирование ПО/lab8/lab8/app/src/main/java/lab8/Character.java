package lab8;
public abstract class Character {
    private WeaponBehavior weaponBehavior;
    public Character(WeaponBehavior wb) {
        this.weaponBehavior = wb;
    }
    public void setWeapon(WeaponBehavior wb) {
        this.weaponBehavior = wb;
    }
    public WeaponBehavior getWeapon() {
        return weaponBehavior;
    }
    public String getWeaponType(){
        return weaponBehavior.getWeaponType();
    }
    public abstract void display();
    public abstract String getCharType();
    public void performWeapon() {
        weaponBehavior.useWeapon();
    }
}
