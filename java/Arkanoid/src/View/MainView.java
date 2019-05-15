package View;

import Data.Model;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Rectangle2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;


public class MainView extends JPanel implements IView {
    private TexturePaint bricksTexture;
    private BufferedImage spaceTexture;
    public MainView(Dimension d) {
        super.setSize(d);
    }

    public void paintComponent(Graphics g)  {
            super.paintComponent(g);
            Graphics2D g2=(Graphics2D) g;
            Ellipse2D.Double ball= Model.Ball.getShape();
            Rectangle2D.Double desk= Model.Desk.getShape();
            Rectangle2D.Double brick;

            g2.drawImage(spaceTexture,0,0,Model.getInstance().getDim().width,Model.getInstance().getDim().height,null);
            g2.setColor(Color.WHITE);
            g2.draw(ball);
            g2.fill(ball);
            g2.setStroke(new BasicStroke(2));
            g2.setColor(Color.lightGray);
            g2.draw(desk);
            g2.fill(desk);
            for (int i = 0; i <80 ; i++) {
                brick=Model.Bricks.getShape(i);
                if(brick!=null) {
                    g2.setColor(Color.black);
                    g2.draw(brick);
                    g2.setPaint(bricksTexture);
                    g2.fill(brick);
                }
            }
    }
    @Override
    public void draw() {
        repaint();
    }

    public void setTexture() throws IOException{
        BufferedImage image= ImageIO.read(new File("/home/anton/projects/NSU/java/Arkanoid/resources/bricks.jpg"));
        bricksTexture=new TexturePaint(image, Model.Bricks.getShape(0).getBounds2D());
        spaceTexture=ImageIO.read(new File("/home/anton/projects/NSU/java/Arkanoid/resources/space.jpg"));
    }
}
