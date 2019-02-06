import java.io.*;
public class Main {
    public static void main(String[]args) throws IOException{
        WordReader CSVreader=new WordReader("/home/anton/Documents/dataForPrograms/java/input.txt");
        WordWriter CSVprinter=new WordWriter();
        CSVprinter.execute(CSVreader.getData(),CSVreader.getAmount());
    }
}
