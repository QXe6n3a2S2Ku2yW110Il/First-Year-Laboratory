package parser;

import lexer.SetExpressionLexer;
import lexer.SetExpressionLexer.Token;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class SetExpressionParser {
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

    private SetExpressionLexer lexer;

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
        lexer = new SetExpressionLexer(s);
        lexer.nextToken();
        return start();
    }

    public static class A1Tree extends Tree {
        private A1Tree(final String node, final Tree... children) {
            super(node, children);
        }

        private A1Tree(final String node) {
            super(node);
        }
    }
    private A1Tree a1() {
        // System.out.println("a1");
        switch (lexer.getToken()) {
            case OR:
                final Tree orRes1 = new TerminalTree(consume(Token.OR));
                final BTree bRes1 = b();
                final A1Tree a1Res1 = a1();
                final A1Tree res0 = new A1Tree("a1", orRes1, bRes1, a1Res1);
                return res0;
            case EOF:
            case RP:
                final A1Tree res1 = new A1Tree("a1");
                return res1;
            default:
                throw new AssertionError("Expected OR, EOF, RP, but found " + lexer.getToken().name());
        }
    }

    public static class ATree extends Tree {
        private ATree(final String node, final Tree... children) {
            super(node, children);
        }

        private ATree(final String node) {
            super(node);
        }
    }
    private ATree a() {
        // System.out.println("a");
        switch (lexer.getToken()) {
            case NOT:
            case LP:
            case VAR:
                final BTree bRes1 = b();
                final A1Tree a1Res1 = a1();
                final ATree res0 = new ATree("a", bRes1, a1Res1);
                return res0;
            default:
                throw new AssertionError("Expected NOT, LP, VAR, but found " + lexer.getToken().name());
        }
    }

    public static class BTree extends Tree {
        private BTree(final String node, final Tree... children) {
            super(node, children);
        }

        private BTree(final String node) {
            super(node);
        }
    }
    private BTree b() {
        // System.out.println("b");
        switch (lexer.getToken()) {
            case NOT:
            case LP:
            case VAR:
                final CTree cRes1 = c();
                final B1Tree b1Res1 = b1();
                final BTree res0 = new BTree("b", cRes1, b1Res1);
                return res0;
            default:
                throw new AssertionError("Expected NOT, LP, VAR, but found " + lexer.getToken().name());
        }
    }

    public static class CTree extends Tree {
        private CTree(final String node, final Tree... children) {
            super(node, children);
        }

        private CTree(final String node) {
            super(node);
        }
    }
    private CTree c() {
        // System.out.println("c");
        switch (lexer.getToken()) {
            case NOT:
            case LP:
            case VAR:
                final DTree dRes1 = d();
                final C1Tree c1Res1 = c1();
                final CTree res0 = new CTree("c", dRes1, c1Res1);
                return res0;
            default:
                throw new AssertionError("Expected NOT, LP, VAR, but found " + lexer.getToken().name());
        }
    }

    public static class DTree extends Tree {
        private DTree(final String node, final Tree... children) {
            super(node, children);
        }

        private DTree(final String node) {
            super(node);
        }
    }
    private DTree d() {
        // System.out.println("d");
        switch (lexer.getToken()) {
            case NOT:
                final Tree notRes1 = new TerminalTree(consume(Token.NOT));
                final DTree dRes1 = d();
                final DTree res0 = new DTree("d", notRes1, dRes1);
                return res0;
            case LP:
            case VAR:
                final ETree eRes1 = e();
                final DTree res1 = new DTree("d", eRes1);
                return res1;
            default:
                throw new AssertionError("Expected NOT, LP, VAR, but found " + lexer.getToken().name());
        }
    }

    public static class ETree extends Tree {
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
            case VAR:
                final FTree fRes1 = f();
                final E1Tree e1Res1 = e1();
                final ETree res0 = new ETree("e", fRes1, e1Res1);
                return res0;
            default:
                throw new AssertionError("Expected LP, VAR, but found " + lexer.getToken().name());
        }
    }

    public static class FTree extends Tree {
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
            case VAR:
                final Tree varRes1 = new TerminalTree(consume(Token.VAR));
                final FTree res0 = new FTree("f", varRes1);
                return res0;
            case LP:
                final Tree lpRes1 = new TerminalTree(consume(Token.LP));
                final ATree aRes1 = a();
                final Tree rpRes1 = new TerminalTree(consume(Token.RP));
                final FTree res1 = new FTree("f", lpRes1, aRes1, rpRes1);
                return res1;
            default:
                throw new AssertionError("Expected VAR, LP, but found " + lexer.getToken().name());
        }
    }

    public static class StartTree extends Tree {
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
            case NOT:
            case LP:
            case VAR:
                final ATree aRes1 = a();
                final StartTree res0 = new StartTree("start", aRes1);
                return res0;
            default:
                throw new AssertionError("Expected NOT, LP, VAR, but found " + lexer.getToken().name());
        }
    }

    public static class E1Tree extends Tree {
        private E1Tree(final String node, final Tree... children) {
            super(node, children);
        }

        private E1Tree(final String node) {
            super(node);
        }
    }
    private E1Tree e1() {
        // System.out.println("e1");
        switch (lexer.getToken()) {
            case IN:
                final Tree inRes1 = new TerminalTree(consume(Token.IN));
                final FTree fRes1 = f();
                final E1Tree res0 = new E1Tree("e1", inRes1, fRes1);
                return res0;
            case NOT_IN:
                final Tree not_inRes1 = new TerminalTree(consume(Token.NOT_IN));
                final FTree fRes2 = f();
                final E1Tree res1 = new E1Tree("e1", not_inRes1, fRes2);
                return res1;
            case OR:
            case AND:
            case XOR:
            case EOF:
            case RP:
                final E1Tree res2 = new E1Tree("e1");
                return res2;
            default:
                throw new AssertionError("Expected IN, NOT_IN, OR, AND, XOR, EOF, RP, but found " + lexer.getToken().name());
        }
    }

    public static class C1Tree extends Tree {
        private C1Tree(final String node, final Tree... children) {
            super(node, children);
        }

        private C1Tree(final String node) {
            super(node);
        }
    }
    private C1Tree c1() {
        // System.out.println("c1");
        switch (lexer.getToken()) {
            case AND:
                final Tree andRes1 = new TerminalTree(consume(Token.AND));
                final DTree dRes1 = d();
                final C1Tree c1Res1 = c1();
                final C1Tree res0 = new C1Tree("c1", andRes1, dRes1, c1Res1);
                return res0;
            case OR:
            case XOR:
            case EOF:
            case RP:
                final C1Tree res1 = new C1Tree("c1");
                return res1;
            default:
                throw new AssertionError("Expected AND, OR, XOR, EOF, RP, but found " + lexer.getToken().name());
        }
    }

    public static class B1Tree extends Tree {
        private B1Tree(final String node, final Tree... children) {
            super(node, children);
        }

        private B1Tree(final String node) {
            super(node);
        }
    }
    private B1Tree b1() {
        // System.out.println("b1");
        switch (lexer.getToken()) {
            case XOR:
                final Tree xorRes1 = new TerminalTree(consume(Token.XOR));
                final CTree cRes1 = c();
                final B1Tree b1Res1 = b1();
                final B1Tree res0 = new B1Tree("b1", xorRes1, cRes1, b1Res1);
                return res0;
            case OR:
            case EOF:
            case RP:
                final B1Tree res1 = new B1Tree("b1");
                return res1;
            default:
                throw new AssertionError("Expected XOR, OR, EOF, RP, but found " + lexer.getToken().name());
        }
    }

}
