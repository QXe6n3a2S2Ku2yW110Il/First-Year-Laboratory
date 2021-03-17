import generator.Generator;
import lexer.SetExpressionLexer;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import parser.SetExpressionParser;

import static org.junit.jupiter.api.Assertions.*;

public class SetExpressionTest {
    private final SetExpressionParser parser = new SetExpressionParser();

    @BeforeAll
    public static void init() {
        final String[] args = {"SetExpression.my"};
        Generator.main(args);
    }

    private void doTest(final String test) {
        parser.parse(test);
    }

    private void testNoThrow(final String test) {
        assertDoesNotThrow(() -> doTest(test));
    }

    private void testThrow(final String test) {
        try {
            doTest(test);
            assert(false);
        } catch (final AssertionError e) {
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
}
