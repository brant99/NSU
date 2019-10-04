import java.util.*;

class Tuple{
    public Integer left;
    public Integer right;
    public Tuple(int l,int r){
        left=l;
        right=r;
    }
    public boolean contains(int dot){
        return dot>=left && dot<= right;
    }

}

class Main {
    static Set<Tuple> set;
    static List<Integer>dots;

    static List<Integer> makeDots(){
        dots=new ArrayList<Integer>(){
            @Override
            public String toString() {
                String str="";
                for(Integer val:this){
                    str+=val.toString()+" ";
                }
                return str;
            }
        };
        Tuple t = set.iterator().next();
        while(true ){
            int curDot=t.right;
            dots.add(curDot);
            while(t.contains(curDot)) {
                set.remove(t);
                if(!set.isEmpty())
                    t = set.iterator().next();
                else
                    return dots;
            }
        }
    }

    public static void main(String[] args) {
        Scanner in =new Scanner(System.in);
        int n = in.nextInt();
        Comparator<Tuple> comparator= new Comparator<Tuple>(){
            @Override
            public int compare(Tuple item1,Tuple item2) {
                if(item1.right.compareTo(item2.right)==0){
                    return item1.left.compareTo(item2.left);
                }
                else
                    return item1.right.compareTo(item2.right);
            }
        };
        set=new TreeSet<Tuple>(comparator);
        for (int i = 0; i < n; i++) {
            set.add(new Tuple(in.nextInt(),in.nextInt()));
        }
        dots=makeDots();
        System.out.println(dots.size());
        System.out.println(dots);
    }
}