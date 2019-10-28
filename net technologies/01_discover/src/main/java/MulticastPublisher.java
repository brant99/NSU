import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.ByteBuffer;
import java.time.Instant;

public class MulticastPublisher {
    private DatagramSocket socket;
    private InetAddress group;
    private byte[] buf;
    private final int timeSend=5000;

    public MulticastPublisher(String ip) throws IOException{
        group = InetAddress.getByName(ip);
        socket = new DatagramSocket();
    };

    public void multicast() throws Exception {
        while(true){
            buf = ByteBuffer.allocate(Long.BYTES).putLong(Instant.now().getEpochSecond()).array();
            socket.send(new DatagramPacket(buf, buf.length, group, 4446));
            Thread.sleep(timeSend);
        }
    }
}

