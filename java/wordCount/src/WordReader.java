import java.io.*;
import java.lang.ref.Reference;
import java.lang.ref.ReferenceQueue;
import java.lang.ref.WeakReference;
import java.util.*;
import static java.util.Map.Entry.comparingByValue;
import static java.util.stream.Collectors.toMap;

public class WordReader {
    Map<String,Integer> WordCont;
    int Count=0;
    public WordReader(String Filename) throws IOException{
        WordCont=ReadWords(Filename).entrySet().stream().
                sorted(Collections.reverseOrder(comparingByValue())).
                collect(toMap(e->e.getKey(),e->e.getValue(),(e1,e2)->e2, LinkedHashMap::new));
    }

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
                Count++;
            }
        }
        input.close();
        return WordCont;
    }

    public Map<String,Integer> getData(){
        return WordCont;
    }
    public int getAmount(){
        return Count;
    }
}