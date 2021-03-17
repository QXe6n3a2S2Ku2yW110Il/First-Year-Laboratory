import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.text.ParseException;

public class Main {
    public static void main(final String[] args) {
        final String test = "(a in b) or (c not in b)";
        final InputStream is = new ByteArrayInputStream(test.getBytes(StandardCharsets.UTF_8));
        try {
            final Tree tree = new Parser().parse(is);
            new Drawer().draw(tree, "example");
        } catch (ParseException e) {
            e.printStackTrace();
        }
    }
}
