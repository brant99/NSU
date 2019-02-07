import java.io.IOException;
import java.util.Map;

public interface Writer {
    void write(Map<String,Integer> data,int count) throws IOException;
}
