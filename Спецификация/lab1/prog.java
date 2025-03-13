import java.util.Scanner;

public class prog {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String neibs = "123456789876543210";
        int from = in.nextInt();
        int to = in.nextInt();
        for(int i = from; i <= to; i++){
            if(neibs.contains(Integer.toString(i))){
                System.out.println(i);
            }
        }
    }
}