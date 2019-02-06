import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.lang.ref.Reference;
import java.util.Map;


public class WordWriter {
    public void execute(Map<String, Integer> data,int Count) throws IOException {
        FileWriter file=new FileWriter("/home/anton/Documents/dataForPrograms/java/output.csv");
        PrintWriter fileOut=new PrintWriter(file);
        fileOut.printf("Words;%%\n");
        for(Map.Entry<String,Integer> entry : data.entrySet())
            fileOut.printf("%s;%f\n",entry.getKey(),(double)100*entry.getValue()/Count);
        fileOut.close();
    }
}
