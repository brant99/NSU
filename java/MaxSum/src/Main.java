import java.util.*;

class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n=in.nextInt();
        List<Integer> ar=new ArrayList<>(){
            @Override
            public String toString() {
                StringBuilder sb=new StringBuilder();
                for(Integer i:this)
                    sb.append(i+" ");
                return sb.toString();
            }
        };
        int i=1;
        while(n-i>=i+1) {
            ar.add(i);
            n-=i;
            i++;
        }
        ar.add(n);
        System.out.println(ar.size());
        System.out.println(ar);
    }
}