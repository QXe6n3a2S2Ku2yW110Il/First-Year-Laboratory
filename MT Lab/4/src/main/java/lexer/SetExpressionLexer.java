package lexer;

public class SetExpressionLexer {
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

    public SetExpressionLexer(final String s) {
        this.s = s;
        position = 0;
    }

    public enum Token {
        OR,
        XOR,
        AND,
        IN,
        NOT_IN,
        NOT,
        VAR,
        LP,
        RP,
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

        if (position + 2 <= s.length() && s.startsWith("or", position)) {
            tokenStr = s.substring(position, position + 2);
            position += 2;
            curToken = Token.OR;
            return;
        }

        if (position + 3 <= s.length() && s.startsWith("xor", position)) {
            tokenStr = s.substring(position, position + 3);
            position += 3;
            curToken = Token.XOR;
            return;
        }

        if (position + 3 <= s.length() && s.startsWith("and", position)) {
            tokenStr = s.substring(position, position + 3);
            position += 3;
            curToken = Token.AND;
            return;
        }

        if (position + 2 <= s.length() && s.startsWith("in", position)) {
            tokenStr = s.substring(position, position + 2);
            position += 2;
            curToken = Token.IN;
            return;
        }

        if (position + 6 <= s.length() && s.startsWith("not in", position)) {
            tokenStr = s.substring(position, position + 6);
            position += 6;
            curToken = Token.NOT_IN;
            return;
        }

        if (position + 3 <= s.length() && s.startsWith("not", position)) {
            tokenStr = s.substring(position, position + 3);
            position += 3;
            curToken = Token.NOT;
            return;
        }

        for (int i = s.length(); i >= position; --i) {
            if (s.substring(position, i).matches("[a-z]")) {
                tokenStr = s.substring(position, i);
                position = i;
                curToken = Token.VAR;
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

        curToken = Token.EPS;
    }
}
