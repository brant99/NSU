import java.io.*;
import java.util.*;
import static java.util.Map.Entry.comparingByValue;
import static java.util.stream.Collectors.toMap;

public class Counter {
    Parser parser;
    int Count=0;
    Map<String,Integer> WordCont;

    public Counter(String Filename) throws IOException {
        WordCont=new HashMap<>();
        if (Filename.contains(".txt")) {
            parser = new TXTParser(Filename);
        }
    }

    public void count() throws IOException {
        String word;
        while((word=parser.parse())!=null){
            if(WordCont.containsKey(word))
                WordCont.put(word,WordCont.get(word)+1);
            else
                WordCont.put(word,1);
            Count++;
        }
        WordCont=WordCont.entrySet().stream().
                sorted(Collections.reverseOrder(comparingByValue())).
                collect(toMap(e->e.getKey(),e->e.getValue(),(e1,e2)->e2, LinkedHashMap::new));
    }

    public Map<String,Integer> getData(){
        return WordCont;
    }
    public int getAmount(){
        return Count;
    }
}