import javax.swing.*;
import java.awt.*;

public class Main  {
    public static void main(String []args){
        {
            int a;
        }
        ballextention a=new ballextention();
        /*
        //int a=10;
        Thread thread1=new Thread(()->{
                a.a+=10;
                System.out.println(a.a);
        }
        );
        thread1.start();
        Thread thread2=new Thread(()-> {
            a.a+=10;
            System.out.println(a.a);
        }
        );
        thread2.start();
        System.out.println(a.a);
        Object o=new Object();*/
        ballextention frame =new ballextention() {
            @Override
            public void exec(){
                //super.exec();
                System.out.println("inher");
            }
        };
        ballextention frame1 =new ballextention();
        frame1.exec();
        System.out.println(frame1.getClass().getName());
        another<Integer> eg=new another<>();
        another<Double> fa=new another<>();
        eg=fa;
    }

}
