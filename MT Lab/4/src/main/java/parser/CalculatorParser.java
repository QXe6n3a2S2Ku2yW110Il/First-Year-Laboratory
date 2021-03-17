package parser;

import lexer.CalculatorLexer;
import lexer.CalculatorLexer.Token;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class CalculatorParser {
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

    private CalculatorLexer lexer;

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
        lexer = new CalculatorLexer(s);
        lexer.nextToken();
        return start();
    }

    public static class TTree extends Tree {
        public double val;

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
            case LP:
            case NUM:
            case MINUS:
                final FTree fRes1 = f();
                final T1Tree t1Res1 = t1(fRes1.val);
                final TTree res0 = new TTree("t", fRes1, t1Res1);
                res0.val = t1Res1.val;
                return res0;
            default:
                throw new AssertionError("Expected LP, NUM, MINUS, but found " + lexer.getToken().name());
        }
    }

    public static class ETree extends Tree {
        public double val;

        private ETree(final String node, final Tree... children) {
            super(node, children);
        }

        private ETree(final String node) {
            super(node);
        }
    }
    private ETree e() {
        // System.out.println("e");
        switch (lexer.getToken()) {
            case LP:
            case NUM:
            case MINUS:
                final TTree tRes1 = t();
                final E1Tree e1Res1 = e1(tRes1.val);
                final ETree res0 = new ETree("e", tRes1, e1Res1);
                res0.val = e1Res1.val;
                return res0;
            default:
                throw new AssertionError("Expected LP, NUM, MINUS, but found " + lexer.getToken().name());
        }
    }

    public static class FTree extends Tree {
        public double val;

        private FTree(final String node, final Tree... children) {
            super(node, children);
        }

        private FTree(final String node) {
            super(node);
        }
    }
    private FTree f() {
        // System.out.println("f");
        switch (lexer.getToken()) {
            case NUM:
                final Tree numRes1 = new TerminalTree(consume(Token.NUM));
                final FTree res0 = new FTree("f", numRes1);
                res0.val = Double.parseDouble(numRes1.node);
                return res0;
            case MINUS:
                final Tree minusRes1 = new TerminalTree(consume(Token.MINUS));
                final FTree fRes1 = f();
                final FTree res1 = new FTree("f", minusRes1, fRes1);
                res1.val = -fRes1.val;
                return res1;
            case LP:
                final Tree lpRes1 = new TerminalTree(consume(Token.LP));
                final ETree eRes1 = e();
                final Tree rpRes1 = new TerminalTree(consume(Token.RP));
                final FTree res2 = new FTree("f", lpRes1, eRes1, rpRes1);
                res2.val = eRes1.val;
                return res2;
            default:
                throw new AssertionError("Expected NUM, MINUS, LP, but found " + lexer.getToken().name());
        }
    }

    public static class StartTree extends Tree {
        public double val;

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
            case LP:
            case NUM:
            case MINUS:
                final ETree eRes1 = e();
                final StartTree res0 = new StartTree("start", eRes1);
                res0.val = eRes1.val;
                return res0;
            default:
                throw new AssertionError("Expected LP, NUM, MINUS, but found " + lexer.getToken().name());
        }
    }

    public static class E1Tree extends Tree {
        public double val;

        private E1Tree(final String node, final Tree... children) {
            super(node, children);
        }

        private E1Tree(final String node) {
            super(node);
        }
    }
    private E1Tree e1(double acc) {
        // System.out.println("e1");
        switch (lexer.getToken()) {
            case PLUS:
                final Tree plusRes1 = new TerminalTree(consume(Token.PLUS));
                final TTree tRes1 = t();
                final E1Tree e1Res1 = e1(acc + tRes1.val);
                final E1Tree res0 = new E1Tree("e1", plusRes1, tRes1, e1Res1);
                res0.val = e1Res1.val;
                return res0;
            case MINUS:
                final Tree minusRes1 = new TerminalTree(consume(Token.MINUS));
                final TTree tRes2 = t();
                final E1Tree e1Res2 = e1(acc - tRes2.val);
                final E1Tree res1 = new E1Tree("e1", minusRes1, tRes2, e1Res2);
                res1.val = e1Res2.val;
                return res1;
            case EOF:
            case RP:
                final E1Tree res2 = new E1Tree("e1");
                res2.val = acc;
                return res2;
            default:
                throw new AssertionError("Expected PLUS, MINUS, EOF, RP, but found " + lexer.getToken().name());
        }
    }

    public static class T1Tree extends Tree {
        public double val;

        private T1Tree(final String node, final Tree... children) {
            super(node, children);
        }

        private T1Tree(final String node) {
            super(node);
        }
    }
    private T1Tree t1(double acc) {
        // System.out.println("t1");
        switch (lexer.getToken()) {
            case MUL:
                final Tree mulRes1 = new TerminalTree(consume(Token.MUL));
                final FTree fRes1 = f();
                final T1Tree t1Res1 = t1(acc * fRes1.val);
                final T1Tree res0 = new T1Tree("t1", mulRes1, fRes1, t1Res1);
                res0.val = t1Res1.val;
                return res0;
            case DIV:
                final Tree divRes1 = new TerminalTree(consume(Token.DIV));
                final FTree fRes2 = f();
                final T1Tree t1Res2 = t1(acc / fRes2.val);
                final T1Tree res1 = new T1Tree("t1", divRes1, fRes2, t1Res2);
                res1.val = t1Res2.val;
                return res1;
            case EOF:
            case RP:
            case PLUS:
            case MINUS:
                final T1Tree res2 = new T1Tree("t1");
                res2.val = acc;
                return res2;
            default:
                throw new AssertionError("Expected MUL, DIV, EOF, RP, PLUS, MINUS, but found " + lexer.getToken().name());
        }
    }

}
