import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.StringTokenizer;

public class TXTParser implements Parser {
    BufferedReader input;
    StringTokenizer words;
    String delim=" .,;/!@#$%^&*(){}[]-=+*~`";

    public TXTParser(String FileName) throws IOException {
        input = new BufferedReader(new FileReader(FileName));
        String line;
        if ((line = input.readLine()) != null)
            words = new StringTokenizer(line);
    }

    public String parse() throws IOException {
        if (words.hasMoreTokens()) {
            return words.nextToken(delim);
        }
        else {
            String line;
            if ((line = input.readLine()) != null) {
                words = new StringTokenizer(line);
                return words.nextToken(delim);
            }
            input.close();
            return null;
        }
    }
}
