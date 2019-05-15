import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ball extends JPanel implements ActionListener {
    int x=1;
    int y=500;
    int velx=2;
    int vely=2;
    ball(Dimension d){
        setSize(d);
        Timer t=new Timer(3,this);
        t.start();
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        if(x>=this.getWidth() || x<=0)
            velx*=(-1);
        if(y>=this.getHeight() || y<=0)
            vely*=(-1);
        x+=velx;
        y+=vely;
        repaint();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.fillOval(x,y,20,20);
    }
}
