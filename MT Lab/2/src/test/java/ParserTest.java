import org.junit.Test;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.text.ParseException;

import static org.junit.jupiter.api.Assertions.*;

public class ParserTest {
    private final Parser parser = new Parser();

    private void doTest(final String test) throws ParseException {
        final InputStream is = new ByteArrayInputStream(test.getBytes(StandardCharsets.UTF_8));
        parser.parse(is);
    }

    private void testNoThrow(final String test) {
        assertDoesNotThrow(() -> doTest(test));
    }

    private void testThrow(final String test) {
        try {
            doTest(test);
            assert(false);
        } catch (final ParseException | AssertionError e) {
            assert(true);
        }
    }

    @Test
    public void sample() {
       testNoThrow("(a in b) or (c not in b)");
    }

    @Test
    public void complexTests() {
        testNoThrow("((a or b) in (a in b)) in (e or f)");
        testNoThrow("(((a in b) in c) in d) or e");
        testNoThrow("((a or b) in (c or d)) in e");
        testNoThrow("((a xor b) or (b in a)) xor b");
        testNoThrow("((a and b) in (c and a)) xor (b or c)");
        testNoThrow("a xor c in b");
        testNoThrow("a in b and c not in d or q in e");
        testNoThrow("not not a not in c");
    }

    @Test
    public void errorTests() {
        testThrow("a b");
        testThrow("(a in)");
        testThrow("lol not in arbidol");
        testThrow("a or not b");
        testThrow("not not not not not b or not not not a");
        testThrow("a in not b");
        testThrow("a xor and b");
        testThrow("()");
    }

    @Test
    public void modificationTests() {
        testNoThrow("a not not in b");
        testNoThrow("not not a not not not in b");
        testThrow("not not a not not in not not b");
    }
}
