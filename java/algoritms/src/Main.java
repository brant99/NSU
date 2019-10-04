import java.util.ArrayList;
import java.util.Scanner;

class Main {

    public static void main(String[] args) {
        Scanner in=new Scanner(System.in);
        long n=in.nextLong();
        int m=in.nextInt();
        ArrayList<Integer> ar=new ArrayList<>();
        ar.add(0);
        ar.add(1);
        int l=1;
        int i=2;
        while(l!=0){
            ar.add((ar.get(i-1)+ar.get(i-2))%m);
            i++;
            if(i%2==0 && ar.get(i-1).equals(ar.get((i-1)/2))){
                int k=i-1;
                l=(i-1)/2;
                while(l!=-1 && ar.get(k-1).equals(ar.get(l-1))){
                    k--;
                    l--;
                }
                if(l==0)
                    i=k;
            }
        }
        System.out.println(ar.get((int)(n%i)));
    }
}