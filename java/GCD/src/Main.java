import java.util.Scanner;

public class Main {
    static int GCD(int a,int b){
        if(a!=0 && b!=0){
            while(a!=0 && b!=0){
                if(a>b)
                    a%=b;
                else if(a==b)
                    return a;
                else
                    b%=a;
            }
        }
        if(a==0)
            return b;
        else
            return a;
    }
    public static void main(String[] args) {
        Scanner in=new Scanner(System.in);
        System.out.println(GCD(in.nextInt(),in.nextInt()));
    }
}