import java.io.IOException;
import java.net.DatagramPacket;
import java.util.Map;

public class NodePublisher extends Thread {
    private NodeHandler handler;

    public NodePublisher(NodeHandler handler) throws IOException{
        this.handler=handler;
    }

    @Override
    public void run() {
        try{
            while(true){
                send();
                Thread.sleep(1000);
            }
        }
        catch (Exception ex){
            ex.printStackTrace();
        }
    }
    public void send() throws IOException{
        for (Map.Entry<DatagramPacket,Long> entry:handler.getQueue()) {
            handler.getSocket().send(entry.getKey());
        }
    }
}

