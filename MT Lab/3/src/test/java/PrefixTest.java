import antlr.PrefixLexer;
import antlr.PrefixParser;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CommonTokenStream;
import org.junit.jupiter.api.Test;

import static org.antlr.v4.runtime.CharStreams.fromString;
import static org.junit.jupiter.api.Assertions.*;

public class PrefixTest {
    private String parse(final String pref) {
        final CharStream cs = fromString(pref);
        final PrefixLexer lexer = new PrefixLexer(cs);
        final CommonTokenStream token = new CommonTokenStream(lexer);
        final PrefixParser parser = new PrefixParser(token);
        final PrefixParser.ProgramContext context = parser.program();
        return context.val;
    }

    private void test(final String pref) {
        System.out.println("========== input ==========");
        System.out.println(pref);
        System.out.println("========== result ==========");
        System.out.println(parse(pref));
    }

    @Test
    public void sample() {
        test("if > 2 3 print 3 if > 4 - 7 2 print + 3 4");
    }

    @Test
    public void allFeatures() {
        test("= a b");
        test("print and > 1 b or <= - a 1 dd < 0 c");
        test("= sum + + + + + + + + + a b c d e f g h i j");
        test("if not not not not not or == c + a b != b - a c print 0 print 1");
    }

    @Test
    public void modificationTests() {
        test("while < a 1919 = a + a 1");
        test("if not > a 0 while < a -5 if >= a -3 print a = a + a 1 print 0");
        test("while < a 1919 = a + a 1 = a + a 1");
    }
}
