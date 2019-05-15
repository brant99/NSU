package Data;

import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Rectangle2D;
import java.util.Random;


public class Model {
    private static Model model;
    private static Ball ball;
    private static Desk desk;
    private static Bricks bricks;
    private Dimension dimension;

    public static Model getInstance(){
        if(model==null)
            model=new Model();
        return model;
    }

    public void setDim(Dimension d) {
        dimension=d;
    }

    public void init(){
        ball=new Ball( (double) 2*dimension.width/3,(double) 2*dimension.height/5,6,(double)dimension.height/50);
        desk=new Desk((double)dimension.width/2, (double)((9*dimension.height)/10));
        bricks=new Bricks((double) dimension.width,(double)dimension.height/4);
    }

    public Dimension getDim(){
        return new Dimension(dimension);
    }


    public static class Ball {
        private static double x,y,diameter;
        private static double []vector=new double[2];

        private Ball(double initX,double initY,double speed,double diameter){
            x=initX;
            y=initY;
            Random r=new Random();
            vector[0]=(-speed*Math.sqrt(2))*r.nextDouble();
            vector[1]=-Math.sqrt(speed*2*speed-vector[0]*vector[0]);
            Ball.diameter=diameter;
        }


        static void moveBall(int keyPressed){
            if(y>=Model.getInstance().getDim().height-diameter || !Bricks.existBricks()) {
                vector[0] = 0;
                vector[1] = 0;
            }
            else {
                double epsilon=getSpeed();
                if (x >= Model.getInstance().getDim().width - diameter || x <= diameter)
                    vector[0] *= (-1);

                if (y <= diameter)
                    vector[1] *= (-1);

                if (intersectDesk()) {
                    if (y + diameter - epsilon <= Desk.y) {
                        if (keyPressed == KeyEvent.VK_LEFT) {
                            if (vector[0] >= 0)
                                vector[0] -= 0.5;
                            else
                                vector[0] += 0.5;
                        } else if (keyPressed == KeyEvent.VK_RIGHT) {
                            if (vector[0] < 0)
                                vector[0] -= 0.5;
                            else
                                vector[0] += 0.5;
                        }
                        vector[1] = Math.sqrt(epsilon * epsilon - vector[0] * vector[0]);
                        vector[1] *= (-1);
                        if ((x - Desk.x +diameter/2 <= Desk.width / 2 && vector[0] > 0) ||
                                (x - Desk.x +diameter/2 > Desk.width / 2 && vector[0] < 0))
                            vector[0] *= (-1);
                    }

                    else if(y-diameter/2-epsilon<Desk.y+Desk.height)
                    {
                        double shift=20;
                        if (x - Desk.x <= Desk.width / 2 && x+ diameter - Desk.x >= 0)
                            x -= shift;
                        else if(x-Desk.x < Desk.width)
                            x += shift;
                        vector[0] *= (-1);
                    }
                }

                if (y -epsilon <= (double) Model.getInstance().getDim().height / 3) {
                    int removeBrick;
                    if ((removeBrick=intersectBricks())!=-1) {
                        Bricks.removeBrick(removeBrick);
                        if (y +epsilon >= Bricks.intersctMaxY  ||
                                y-epsilon <= Bricks.intersctMinY - diameter)
                            vector[1] *= (-1);
                        else
                            vector[0] *= (-1);
                    }
                }
                x += vector[0];
                y += vector[1];
            }
        }

        private static boolean intersectDesk(){
            return getShape().intersects(Desk.getShape());
        }

        private static int intersectBricks(){
            Rectangle2D.Double brick;
            for (int i = 0; i < 80; i++) {
                brick=Bricks.getShape(i);
                if(brick!=null && getShape().intersects(brick)){
                    return i;
                }
            }
            return -1;
        }

        static double getSpeed(){
            return Math.sqrt(vector[0]*vector[0]+vector[1]*vector[1]);
        }

        public static Ellipse2D.Double getShape(){return new Ellipse2D.Double(x,y,diameter,diameter);}


    }



    public static class Desk {
        private static double width,height,x,y,vel;

        public static Rectangle2D.Double getShape() { return new Rectangle2D.Double(x,y,width,height);}
        private Desk(double x,double y){
            Desk.x=x;
            Desk.y=y;
            width=x/4;
            height=y/40;
            vel=x/60;
        }

        static void moveLeft(){
            if(!( x-vel<0))
                x-=vel;
            else
                x=0;
        }

        static void moveRight(){
            if(!(x+vel+width>Model.getInstance().getDim().width ))
                x+=vel;
            else
                x=Model.getInstance().getDim().width-width;
        }
    }



    public static class Bricks{
        private static Rectangle2D.Double []bricks=new Rectangle2D.Double[80];
        private static double width,height;
        private static double intersctMaxY,intersctMinY;

        private Bricks(double width,double height){
            double shiftX=0,shiftY=0;
            double epsilon=width/100;
            Bricks.width=width/10;
            Bricks.height=height/8;
            for (int i=0;i<80;i++) {
                bricks[i]=new Rectangle2D.Double(shiftX,shiftY,Bricks.width,Bricks.height);
                if(shiftX+epsilon+Bricks.width>=width) {
                    shiftX = 0;
                    shiftY+=Bricks.height;
                }
                else
                    shiftX+=Bricks.width;
            }
        }

        public static Rectangle2D.Double getShape(int index){
            if(bricks[index]!=null)
                return new Rectangle2D.Double(bricks[index].x,bricks[index].y,bricks[index].width,bricks[index].height);
            return null;
        }

        private static void removeBrick(int index){
            intersctMaxY=bricks[index].getMaxY();
            intersctMinY=bricks[index].getMinY();
            bricks[index]=null;
        }

        static boolean existBricks(){
            for (int i = 0; i < 80; i++) {
                if(bricks[i]!=null)
                    return true;
            }
            return false;
        }
        static int getAmountBricks(){
            int counter=0;
            for (int i = 0; i < 80; i++) {
                if(bricks[i]==null)
                    counter++;
            }
            return counter;
        }
    }
}
