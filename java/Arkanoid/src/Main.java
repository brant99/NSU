import Data.Controller;

import java.awt.*;

public class Main{
    public static void main(String args[]){
        try {
            Controller game = new Controller(new Dimension(800, 600));
            game.initMenu();
        }
        catch (Exception ex){
            System.err.println(ex.getMessage());
        }
    }
}