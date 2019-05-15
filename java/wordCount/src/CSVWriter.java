import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class CSVWriter implements Writer{
    PrintWriter file;
    CSVWriter(String FileName) throws IOException{
        file=new PrintWriter(new FileWriter(FileName));
    }
    public void write(String ...strokes)  {
        for(String str:strokes)
            file.printf(str+"\n");
        file.close();
    }
}
