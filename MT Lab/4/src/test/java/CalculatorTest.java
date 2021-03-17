import generator.Generator;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import parser.CalculatorParser;
import parser.CalculatorPowParser;
import parser.InitParser;

import static org.junit.jupiter.api.Assertions.*;

public class CalculatorTest {
    private final CalculatorParser parser = new CalculatorParser();

    @BeforeAll
    public static void init() {
        final String[] args = {"calculator.my"};
        Generator.main(args);
        args[0] = "calculatorPow.my";
        Generator.main(args);
    }

    @Test
    public void simple() {
        assertEquals(123, parser.parse("123").val);
        assertEquals(-114.514, parser.parse("-114.514").val);
        assertThrows(AssertionError.class, () -> parser.parse("()"));
        assertEquals(34, parser.parse("----(-((---(((--(34.000000000)))))))").val);
    }

    @Test
    public void arithmetic() {
        assertEquals(55.0, parser.parse("1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10").val);
        assertEquals(-53.0, parser.parse("1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10").val);
        assertEquals(6.2, parser.parse("1 + 2 * 3 - 4 / 5").val);
        assertEquals(-905.0, parser.parse("1 + 2 * (3 + 4 * (4 - 10) * 19)").val);
        assertEquals(400.0, parser.parse("138.6 - 1.9 + 211.4 + 51.9").val);
        assertEquals(6, parser.parse("10 - 6 + 2").val);
        assertEquals(2, parser.parse("10 - (6 + 2)").val);
        assertEquals(2, parser.parse("10 / (-6 + 3 * 3 + (3 - 1))").val);
        assertEquals(19, parser.parse("2 + 3 * 4 + 5").val);
    }

    @Test
    public void pow() {
        final CalculatorPowParser pparser = new CalculatorPowParser();
        assertEquals(512, pparser.parse("2 ** 3 ** 2").val);
        assertEquals(64, pparser.parse("(2 ** 3) ** 2").val);
        assertEquals(810, pparser.parse("2 * 3 ** 4 * 5").val);
        assertEquals(72, pparser.parse("2 ** 3 * 3 ** 2").val);
        assertEquals(-4, pparser.parse("1 - 2 - 3").val);
        assertEquals(1, pparser.parse("8 / 4 / 2").val);
        assertNotEquals(1, pparser.parse("2 ** 3 ** 3").val);
    }

    @Test
    public void initTest() {
        final InitParser init = new InitParser();
        assertEquals("real a = 0, b = 0, c = 0;", init.parse("real a, b, c").s);
        assertEquals("int x = 0;", init.parse("int x").s);
        assertThrows(AssertionError.class, () -> init.parse("int 0, 1"));
    }
}
