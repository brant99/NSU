import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.geom.Rectangle2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;


public class Desk extends JPanel implements KeyListener {
    double x=400;
    double y=600;
    Desk(){
        addKeyListener(this);
        setFocusable(true);
        setFocusTraversalKeysEnabled(true);
    }
    public void paintComponent(Graphics g) {
        try {
            super.paintComponent(g);
            Graphics2D g2 = (Graphics2D) g;
            Rectangle2D rec = new Rectangle2D.Double(x, y, 100, 20);
            BufferedImage img = ImageIO.read(new File("/home/anton/projects/NSU/java/swingTest/pictures/desk.jpeg"));
            TexturePaint desk = new TexturePaint(img, new Rectangle.Double(x,y,100,20));
            g2.setPaint(desk);
            g2.fill(rec);
        }
        catch(IOException ex){

        }
    }

    @Override
    public void keyTyped(KeyEvent e) {
    }
    @Override
    public void keyPressed(KeyEvent e){
        if(e.getKeyCode()==KeyEvent.VK_ENTER) {
            x += 2;
            this.repaint();
        }

    }
    @Override
    public void keyReleased(KeyEvent e) {

    }
}
