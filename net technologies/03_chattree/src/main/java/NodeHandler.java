import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.*;
import java.time.Instant;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CopyOnWriteArrayList;

public class NodeHandler extends Thread {
    enum MessageType{
        SEND,
        VERIFY,
        RECIEVE,
        BINDSEND,
        BINDRECIVE;

        public static MessageType fromInt(int x){
            switch (x) {
                case 0:
                    return SEND;
                case 1:
                    return VERIFY;
                case 2:
                    return RECIEVE;
                case 3:
                    return BINDSEND;
                case 4:
                    return BINDRECIVE;
            }
            return null;
        }
    }
    private final int timeOut=15;
    private Map<SocketAddress,Long> mates;
    private List<Map.Entry<DatagramPacket,Long>> queueSend;

    private String name;
    private SocketAddress father;
    private SocketAddress stepfather;
    private NodePublisher sender;
    private NodeReciever reciever;
    private DatagramSocket socket;

    public NodeHandler(String name, int port, int losses) throws IOException {
        this.name=name;
        socket=new DatagramSocket(new InetSocketAddress(port));
        sender=new NodePublisher(this);
        reciever=new NodeReciever(this,losses);
        mates=new ConcurrentHashMap<>();
        queueSend=new CopyOnWriteArrayList<>();
    }

    public void startChat(){
        this.start();
        reciever.start();
        sender.start();
    }

    @Override
    public void run() {
        try {
            new Thread(() -> {
                Scanner scanner=new Scanner(System.in);
                try {
                    while(true) {
                        if (scanner.hasNext()) {
                            String message = scanner.nextLine();
                            long guid=createGuid(message);
                            for (Map.Entry<SocketAddress, Long> entry : mates.entrySet()) {
                                queueSend.add(complectPackage(entry.getKey(),name + ":" + message,guid , MessageType.SEND));
                            }
                            sender.send();
                        }
                    }
                }
                catch (IOException ex){
                    scanner.close();
                    socket.close();
                    ex.printStackTrace();
                }
            }).start();
            while (true) {
                for (Map.Entry<SocketAddress, Long> entry : mates.entrySet()) {
                        if (Instant.now().getEpochSecond() - entry.getValue() > timeOut) {
                            System.out.println("System:disconnected "+entry.getKey());
                            if (entry.getKey().equals(father)) {
                                if (stepfather != null)
                                    bindWithParent(stepfather);
                                father = stepfather;
                                stepfather = null;
                            }
                            reciever.remMessages(entry.getKey());
                        }
                }
               Thread.sleep(5000);
            }
        }
        catch (Exception ex){
            socket.close();
            ex.printStackTrace();
        }
        finally {
            socket.close();
        }
    }

    public DatagramSocket getSocket(){
        return socket;
    }



    public long createGuid(String message) throws IOException{
        return UUID.nameUUIDFromBytes((name+":"+message + Instant.now().getEpochSecond()).getBytes("UTF-8")).getMostSignificantBits();
    }

    public Map.Entry<DatagramPacket,Long> complectPackage(SocketAddress address,String message,long guid,MessageType type) throws IOException{
        ByteArrayOutputStream data=new ByteArrayOutputStream();
        DataOutputStream dataWrite=new DataOutputStream(data);
        dataWrite.writeInt(new Random().nextInt(100));//?
        dataWrite.writeInt(type.ordinal());
        dataWrite.writeLong(guid);
        if(type!=MessageType.RECIEVE && type!=MessageType.VERIFY)
            dataWrite.writeUTF(message);
        dataWrite.flush();
        data.flush();
        dataWrite.close();//?
        data.close();//?
        return new java.util.AbstractMap.SimpleEntry<>(new DatagramPacket(data.toByteArray(),data.toByteArray().length,address),guid);
    }

    public void bindWithParent(SocketAddress parent) throws IOException{
        mates.put(parent,Instant.now().getEpochSecond());
        String message="System:connected with "+socket.getLocalSocketAddress();
        queueSend.add(complectPackage(parent,message,createGuid(message),MessageType.BINDSEND));
    }


    public synchronized void setParents(SocketAddress stepfather,SocketAddress father) {
        this.stepfather=stepfather;
        this.father=father;
    }



    public SocketAddress getFather(){
        return father;
    }

    public Map<SocketAddress,Long> getMates(){
        return mates;
    }

    public List<Map.Entry<DatagramPacket,Long>> getQueue(){
        return queueSend;
    }


}
