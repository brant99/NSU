import java.io.*;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.nio.ByteBuffer;
import java.time.Instant;
import java.util.Hashtable;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;

public class MulticastReceiver extends Thread {

    class Checker extends TimerTask{
        public void run(){
            for (Map.Entry<InetAddress,Long>  entry:  ipMap.entrySet()) {
                if(Instant.now().getEpochSecond()-entry.getValue()>secCheck){
                    ipMap.remove(entry.getKey());
                }
            }
            printMap();
        }
    }
    private final int secCheck=15;
    private MulticastSocket socket;
    private byte[]buf ;
    private DatagramPacket packet;
    private Map<InetAddress,Long> ipMap;
    private Timer timer;

    public MulticastReceiver(String ip) throws IOException {
        buf = new byte[256];
        packet= new DatagramPacket(buf, buf.length);
        socket = new MulticastSocket(4446);
        ipMap=new Hashtable<>();
        socket.joinGroup(InetAddress.getByName(ip));
        timer=new Timer();
    };

    public void run() {
        try{
            timer.schedule(new Checker(),secCheck*1000,secCheck*1000);
            while(true) {
                socket.receive(packet);
                if(ipMap.containsKey(packet.getAddress())) {
                    ipMap.put(packet.getAddress(), ByteBuffer.wrap(packet.getData(), packet.getOffset(), packet.getLength()).getLong());
                } else{
                    ipMap.put(packet.getAddress(), ByteBuffer.wrap(packet.getData(), packet.getOffset(), packet.getLength()).getLong());
                    printMap();
                }
            }
        } catch(IOException ex){
            ex.printStackTrace();
        }
    }
    private void printMap(){
        System.out.println("list of available copies:");
        for (Map.Entry<InetAddress,Long> entry:ipMap.entrySet()) {
            System.out.println(entry.getKey().getHostAddress());
        }
        System.out.println("************************");
    }
}