import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Map;


public class CSVWriter implements Writer{
    PrintWriter file;
    CSVWriter(String FileName) throws IOException{
        file=new PrintWriter(new FileWriter(FileName));
    }
    public void write(Map<String, Integer> data,int Count)  {
        file.printf("Words;%%\n");
        for(Map.Entry<String,Integer> entry : data.entrySet())
            file.printf("%s;%f\n",entry.getKey(),(double)100*entry.getValue()/Count);
        file.close();
    }
}
