import javax.swing.*;

public class Main {
    public static void main(String args[]){
        Desk s=new Desk();
        JFrame frame = new JFrame("FrameDemo");
        frame.add(s);
        frame.setVisible(true);
        frame.setSize(1024,600);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //frame.getContentPane().add(emptyLabel, BorderLayout.CENTER);
    }
}
