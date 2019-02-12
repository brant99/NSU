import static org.lwjgl.glfw.GLFW.*;
public class Main  {
    private Thread thread;
    public Main(){
        glfwInit();
        long w=glfwCreateWindow(640,200,"sos",0,0);
        glfwShowWindow(w);
        while ( glfwWindowShouldClose(w)!=true){
            glfwPollEvents();

        }
    }
    public static void main(String []args){
        Main main=new Main();
    }
}
