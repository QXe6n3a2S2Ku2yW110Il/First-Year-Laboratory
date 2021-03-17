package parser;

import lexer.InitLexer;
import lexer.InitLexer.Token;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class InitParser {
    private static abstract class Tree {
        protected final String node;
        protected final List<Tree> children;

        private Tree(final String node, final Tree... children) {
            this.node = node;
            this.children = Arrays.asList(children);
        }

        private Tree(final String node) {
            this.node = node;
            children = new ArrayList<>();
        }
    }

    private class TerminalTree extends Tree {
        private TerminalTree(final String node) {
            super(node);
        }
    }

    private InitLexer lexer;

    private String consume(final Token token) {
        // System.out.println("consumed " + token.name());
        if (lexer.getToken() != token) {
            throw new AssertionError("Expected " + token.name() + ", but found " + lexer.getToken().name());
        }
        final String res = lexer.getStr();
        lexer.nextToken();
        return res;
    }

    public StartTree parse(final String s) {
        // System.out.println("new parser");
        lexer = new InitLexer(s);
        lexer.nextToken();
        return start();
    }

    public static class TTree extends Tree {
        public String s;

        private TTree(final String node, final Tree... children) {
            super(node, children);
        }

        private TTree(final String node) {
            super(node);
        }
    }
    private TTree t() {
        // System.out.println("t");
        switch (lexer.getToken()) {
            case INT:
                final Tree intRes1 = new TerminalTree(consume(Token.INT));
                final TTree res0 = new TTree("t", intRes1);
                res0.s = "int";
                return res0;
            case REAL:
                final Tree realRes1 = new TerminalTree(consume(Token.REAL));
                final TTree res1 = new TTree("t", realRes1);
                res1.s = "real";
                return res1;
            default:
                throw new AssertionError("Expected INT, REAL, but found " + lexer.getToken().name());
        }
    }

    public static class L1Tree extends Tree {
        public String s;

        private L1Tree(final String node, final Tree... children) {
            super(node, children);
        }

        private L1Tree(final String node) {
            super(node);
        }
    }
    private L1Tree l1(String acc) {
        // System.out.println("l1");
        switch (lexer.getToken()) {
            case COMMA:
                final Tree commaRes1 = new TerminalTree(consume(Token.COMMA));
                final Tree idRes1 = new TerminalTree(consume(Token.ID));
                final L1Tree l1Res1 = l1(acc + ", " + idRes1.node + " = 0");
                final L1Tree res0 = new L1Tree("l1", commaRes1, idRes1, l1Res1);
                res0.s = l1Res1.s;
                return res0;
            case EOF:
                final L1Tree res1 = new L1Tree("l1");
                res1.s = acc;
                return res1;
            default:
                throw new AssertionError("Expected COMMA, EOF, but found " + lexer.getToken().name());
        }
    }

    public static class StartTree extends Tree {
        public String s;

        private StartTree(final String node, final Tree... children) {
            super(node, children);
        }

        private StartTree(final String node) {
            super(node);
        }
    }
    private StartTree start() {
        // System.out.println("start");
        switch (lexer.getToken()) {
            case REAL:
            case INT:
                final TTree tRes1 = t();
                final LTree lRes1 = l();
                final StartTree res0 = new StartTree("start", tRes1, lRes1);
                res0.s = tRes1.s + " " + lRes1.s + ";";
                return res0;
            default:
                throw new AssertionError("Expected REAL, INT, but found " + lexer.getToken().name());
        }
    }

    public static class LTree extends Tree {
        public String s;

        private LTree(final String node, final Tree... children) {
            super(node, children);
        }

        private LTree(final String node) {
            super(node);
        }
    }
    private LTree l() {
        // System.out.println("l");
        switch (lexer.getToken()) {
            case ID:
                final Tree idRes1 = new TerminalTree(consume(Token.ID));
                final L1Tree l1Res1 = l1(idRes1.node + " = 0");
                final LTree res0 = new LTree("l", idRes1, l1Res1);
                res0.s = l1Res1.s;
                return res0;
            default:
                throw new AssertionError("Expected ID, but found " + lexer.getToken().name());
        }
    }

}
