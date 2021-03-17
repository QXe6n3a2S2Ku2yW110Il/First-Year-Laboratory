package lexer;

public class InitLexer {
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

    public InitLexer(final String s) {
        this.s = s;
        position = 0;
    }

    public enum Token {
        INT,
        REAL,
        ID,
        COMMA,
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

        if (position + 3 <= s.length() && s.startsWith("int", position)) {
            tokenStr = s.substring(position, position + 3);
            position += 3;
            curToken = Token.INT;
            return;
        }

        if (position + 4 <= s.length() && s.startsWith("real", position)) {
            tokenStr = s.substring(position, position + 4);
            position += 4;
            curToken = Token.REAL;
            return;
        }

        for (int i = s.length(); i >= position; --i) {
            if (s.substring(position, i).matches("[a-zA-Z]+")) {
                tokenStr = s.substring(position, i);
                position = i;
                curToken = Token.ID;
                return;
            }
        }

        if (position + 1 <= s.length() && s.startsWith(",", position)) {
            tokenStr = s.substring(position, position + 1);
            position += 1;
            curToken = Token.COMMA;
            return;
        }

        curToken = Token.EPS;
    }
}
