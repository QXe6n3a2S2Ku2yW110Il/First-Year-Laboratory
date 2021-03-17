package lexer;

public class CalculatorLexer {
    private Token curToken;
    private int position = 0;
    private final String s;
    private String tokenStr;

    public Token getToken() {
        return curToken;
    }

    public String getStr() {
        return tokenStr;
    }

    public CalculatorLexer(final String s) {
        this.s = s;
        position = 0;
    }

    public enum Token {
        NUM,
        LP,
        RP,
        PLUS,
        MINUS,
        MUL,
        DIV,
        EPS,
        EOF
    }

    public void nextToken() {
        for (int i = s.length(); i >= position; --i) {
            if (s.substring(position, i).matches("[ \t\r\n]+")) {
                position = i;
                break;
            }
        }
        if (position == s.length()) {
            curToken = Token.EOF;
            return;
        }

        for (int i = s.length(); i >= position; --i) {
            if (s.substring(position, i).matches("[\\d]+(.[\\d]+)?")) {
                tokenStr = s.substring(position, i);
                position = i;
                curToken = Token.NUM;
                return;
            }
        }

        if (position + 1 <= s.length() && s.startsWith("(", position)) {
            tokenStr = s.substring(position, position + 1);
            position += 1;
            curToken = Token.LP;
            return;
        }

        if (position + 1 <= s.length() && s.startsWith(")", position)) {
            tokenStr = s.substring(position, position + 1);
            position += 1;
            curToken = Token.RP;
            return;
        }

        if (position + 1 <= s.length() && s.startsWith("+", position)) {
            tokenStr = s.substring(position, position + 1);
            position += 1;
            curToken = Token.PLUS;
            return;
        }

        if (position + 1 <= s.length() && s.startsWith("-", position)) {
            tokenStr = s.substring(position, position + 1);
            position += 1;
            curToken = Token.MINUS;
            return;
        }

        if (position + 1 <= s.length() && s.startsWith("*", position)) {
            tokenStr = s.substring(position, position + 1);
            position += 1;
            curToken = Token.MUL;
            return;
        }

        if (position + 1 <= s.length() && s.startsWith("/", position)) {
            tokenStr = s.substring(position, position + 1);
            position += 1;
            curToken = Token.DIV;
            return;
        }

        curToken = Token.EPS;
    }
}
