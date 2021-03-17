import java.io.IOException;
import java.io.InputStream;
import java.text.ParseException;

public class LexicalAnalyzer {
    private final InputStream is;
    private int curChar;
    private int curPos;
    private Token curToken;
    private String reserve = "";
    private String curWord = "";

    public String getCurWord() {
        return curWord;
    }

    public LexicalAnalyzer(final InputStream is) throws ParseException {
        this.is = is;
        curPos = 0;
        nextChar();
    }

    private boolean isBlank(final int c) {
        return c == ' ' || c == '\r' || c == '\n' || c == '\t';
    }

    private void nextChar() throws ParseException {
        ++curPos;
        try {
            curChar = is.read();
        } catch (final IOException e) {
            throw new ParseException(e.getMessage(), curPos);
        }
    }

    private String getWord() throws ParseException {
        StringBuilder wordBuilder = new StringBuilder();
        while (!Character.isLetter(curChar)) {
            nextChar();
        }
        while (Character.isLetter(curChar)) {
            wordBuilder.append((char) curChar);
            nextChar();
        }
        return wordBuilder.toString();
    }

    public void nextToken() throws ParseException {
        if (reserve.isEmpty()) {
            while (isBlank(curChar)) {
                nextChar();
            }
        }

        if (!reserve.isEmpty() || Character.isLetter(curChar)) {
            final String word = reserve.isEmpty() ? getWord() : reserve;
            reserve = "";
            if (word.length() == 1) {
                curToken = Token.VAR;
                curWord = word;
                return;
            }
            switch (word) {
                case "or":
                    curToken = Token.OR;
                    break;
                case "xor":
                    curToken = Token.XOR;
                    break;
                case "and":
                    curToken = Token.AND;
                    break;
                case "in":
                    curToken = Token.IN;
                    break;
                case "not":
                    String expectIn = getWord();
                    boolean not = true;
                    while (expectIn.equals("not")) {
                        expectIn = getWord();
                        not = !not;
                    }
                    if (expectIn.equals("in")) {
                        if (not) {
                            curToken = Token.NOT_IN;
                        } else {
                            curToken = Token.IN;
                        }
                    } else {
                        if (not) {
                            curToken = Token.NOT;
                        } else {
                            curToken = Token.NOT_NOT;
                        }
                        reserve = expectIn;
                    }
                    break;
                default:
                    throw new ParseException("Illegal token '" + word + "'", curPos);
            }
            return;
        }
        switch (curChar) {
            case '(':
                nextChar();
                curToken = Token.LPAREN;
                break;
            case ')':
                nextChar();
                curToken = Token.RPAREN;
                break;
            case -1:
                curToken = Token.END;
                break;
            default:
                throw new ParseException("Illegal character '" + (char) curChar + "'", curPos);
        }
    }

    public Token getCurToken() {
        return curToken;
    }

    public int getCurPos() {
        return curPos;
    }
}
