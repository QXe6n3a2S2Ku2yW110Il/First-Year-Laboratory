import java.io.InputStream;
import java.text.ParseException;

public class Parser {
    private LexicalAnalyzer lex;

    private void consume(final Token token) throws ParseException {
        if (lex.getCurToken() != token) {
            throw new AssertionError("Expected " + token.name() +  ", but found " + lex.getCurToken().name());
        }
//         System.out.println("Consumed " + token.name());
        lex.nextToken();
    }

    private Tree A() throws ParseException {
        System.out.println("A");
        switch (lex.getCurToken()) {
            case NOT:
            case NOT_NOT:
            case VAR:
            case LPAREN:
                final Tree b = B();
                final Tree aPrime = APrime();
                return new Tree("A", b, aPrime);
            default:
                throw new AssertionError("Expected not | var | (, but found " + lex.getCurToken().name());
        }
    }

    private Tree APrime() throws ParseException {
        System.out.println("A'");
        switch (lex.getCurToken()) {
            case OR:
                consume(Token.OR);
                final Tree or = new Tree("or", false);
                final Tree b = B();
                final Tree aPrime = APrime();
                return new Tree("A'", or, b, aPrime);
            case END:
            case RPAREN:
                return new Tree("A'", true);
            default:
                throw new AssertionError("Expected or | $ | ), but found " + lex.getCurToken().name());
        }
    }

    private Tree B() throws ParseException {
        System.out.println("B");
        switch (lex.getCurToken()) {
            case NOT:
            case NOT_NOT:
            case VAR:
            case LPAREN:
                final Tree c = C();
                final Tree bPrime = BPrime();
                return new Tree("C", c, bPrime);
            default:
                throw new AssertionError("Expected not | var | (, but found " + lex.getCurToken().name());
        }
    }

    private Tree BPrime() throws ParseException {
        System.out.println("B'");
        switch (lex.getCurToken()) {
            case XOR:
                consume(Token.XOR);
                final Tree xor = new Tree("xor", false);
                final Tree c = C();
                final Tree bPrime = BPrime();
                return new Tree("B'", xor, c, bPrime);
            case OR:
            case END:
            case RPAREN:
                return new Tree("B'", true);
            default:
                throw new AssertionError("Expected xor | or | $ | ), but found " + lex.getCurToken().name());
        }
    }

    private Tree C() throws ParseException {
        System.out.println("C");
        switch (lex.getCurToken()) {
            case NOT:
            case NOT_NOT:
            case VAR:
            case LPAREN:
                final Tree d = D();
                final Tree cPrime = CPrime();
                return new Tree("C", d, cPrime);
            default:
                throw new AssertionError("Expected not | var | (, but found " + lex.getCurToken().name());
        }
    }

    private Tree CPrime() throws ParseException {
        System.out.println("C'");
        switch (lex.getCurToken()) {
            case AND:
                consume(Token.AND);
                final Tree and = new Tree("and", false);
                final Tree d = D();
                final Tree cPrime = CPrime();
                return new Tree("C'", and, d, cPrime);
            case XOR:
            case OR:
            case END:
            case RPAREN:
                return new Tree("C'", true);
            default:
                throw new AssertionError("Expected and | xor | or | $ | ), but found " + lex.getCurToken().name());
        }
    }

    private Tree D() throws ParseException {
        System.out.println("D");
        switch (lex.getCurToken()) {
            case NOT:
                consume(Token.NOT);
                final Tree not = new Tree("not", false);
                final Tree d = D();
                return new Tree("D", not, d);
            case NOT_NOT:
                consume(Token.NOT_NOT);
                final Tree notNot = new Tree("not not", false);
                final Tree d1 = D();
                return new Tree("D", notNot, d1);
            case VAR:
            case LPAREN:
                final Tree e = E();
                return new Tree("D", e);
            default:
                throw new AssertionError("Expected not | var | (, but found " + lex.getCurToken().name());
        }
    }

    private Tree E() throws ParseException {
        System.out.println("E");
        switch (lex.getCurToken()) {
            case VAR:
            case LPAREN:
                final Tree f = F();
                final Tree ePrime = EPrime();
                return new Tree("E", f, ePrime);
            default:
                throw new AssertionError("Expected var | (, but found " + lex.getCurToken().name());
        }
    }

    private Tree EPrime() throws ParseException {
        System.out.println("E'");
        switch (lex.getCurToken()) {
            case IN:
                consume(Token.IN);
                final Tree in = new Tree("in");
                final Tree f = F();
                return new Tree("E'", in, f);
            case NOT_IN:
                consume(Token.NOT_IN);
                final Tree notIn = new Tree("not in");
                final Tree f1 = F();
                return new Tree("E'", notIn, f1);
            case AND:
            case XOR:
            case OR:
            case END:
            case RPAREN:
                return new Tree("E'", true);
            default:
                throw new AssertionError("Expected in | not in, but found " + lex.getCurToken().name());
        }
    }

    private Tree F() throws ParseException {
        System.out.println("F");
        switch (lex.getCurToken()) {
            case VAR:
                consume(Token.VAR);
                final Tree var = new Tree("var " + lex.getCurWord());
                return new Tree("F", var);
            case LPAREN:
                consume(Token.LPAREN);
                final Tree lParen = new Tree("(", false);
                final Tree a = A();
                consume(Token.RPAREN);
                final Tree rParen = new Tree(")", false);
                return new Tree("F", lParen, a, rParen);
            default:
                throw new AssertionError("Expected var | ), but found " + lex.getCurToken().name());
        }
    }

    public Tree parse(final InputStream is) throws ParseException {
//        System.out.println("new parser");
        lex = new LexicalAnalyzer(is);
        lex.nextToken();
        return A();
    }
}
