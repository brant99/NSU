import java.io.*;
import java.util.*;
import static java.util.Map.Entry.comparingByValue;
import static java.util.stream.Collectors.toMap;

public class Table {
    private Map<String,Integer> ReadWords(String FileName) throws IOException{
        Map<String,Integer> WordCont=new HashMap<>();
        BufferedReader input=new BufferedReader(new FileReader(FileName));
        String line;
        while((line=input.readLine())!=null){
            StringTokenizer word=new StringTokenizer(line);
            while(word.hasMoreTokens()){
                String curWord=word.nextToken(" .,;/!@#$%^&*(){}[]-=+*~`");
                if(WordCont.containsKey(curWord))
                    WordCont.put(curWord,WordCont.get(curWord)+1);
                else
                    WordCont.put(curWord,1);
            }
        }
        input.close();
        return WordCont;
    }

    public void execute(String FileName) throws IOException{
        Double sum=0.0;
        FileWriter file=new FileWriter("/home/anton/Documents/dataForPrograms/java/output.csv");
        PrintWriter fileOut=new PrintWriter(file);
        Map<String,Integer> data=ReadWords(FileName).entrySet().stream().
                sorted(Collections.reverseOrder(comparingByValue())).
                collect(toMap(e->e.getKey(),e->e.getValue(),(e1,e2)->e2, LinkedHashMap::new));

        for (String key: data.keySet())
            sum += data.get(key);
        fileOut.printf("Words;%%\n");
        for(Map.Entry<String,Integer> entry : data.entrySet())
            fileOut.printf("%s;%f\n",entry.getKey(),100*entry.getValue()/sum);
        fileOut.close();
    }
}
