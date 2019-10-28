
public class Main {
    public static void main(String[] args) throws Exception {
        MulticastPublisher mp=new MulticastPublisher(args[0]);
        MulticastReceiver mr=new MulticastReceiver(args[0]);
        mr.start();
        mp.multicast();
    }
}
