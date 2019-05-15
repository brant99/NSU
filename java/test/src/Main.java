
import javax.swing.*;
import java.awt.*;

public class Main  {
    public static void main(String []args){
        JFrame frame=new JFrame();
        ball mainPanel=new ball(frame.getSize());
        JPanel bricks =new JPanel();
        JButton s=new JButton("lol");

        frame.setSize(800,600);
        bricks.setSize(800,300);
        s.setPreferredSize(bricks.getSize());
        bricks.add(s);
        mainPanel.add(bricks);
        frame.add(mainPanel);

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);


    }
}
