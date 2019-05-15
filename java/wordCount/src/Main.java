import java.io.*;
public class Main {
    public static void main(String[]args) throws IOException{
        Counter wordCount=new Counter("/home/anton/Documents/dataForPrograms/java/input.txt");
        wordCount.count();
        Writer writer=new CSVWriter("/home/anton/Documents/dataForPrograms/java/output.csv");
        writer.write(wordCount.getData(";"));
    }
}
