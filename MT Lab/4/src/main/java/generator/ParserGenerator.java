package generator;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;
import java.util.stream.Collectors;

import static generator.Generator.*;

public class ParserGenerator {
    private final List<String> lines;
    private final String lexerName;
    private final String parserName;

    private final StringBuilder code = new StringBuilder();
    private final static String DIR = "src/main/java/parser/";

    private final Set<String> lexers = new HashSet<>();
    private final Map<String, Rule> parsers = new HashMap<>();

    private final Set<String> terminals = new HashSet<>();
    private final Set<String> nonTerminals = new HashSet<>();

    private final Map<String, Set<String>> first = new HashMap<>();
    private final Map<String, Set<String>> follow = new HashMap<>();

    private static class Rule {
        private final String takes;
        private final String returns;
        private final List<Possibility> to;

        private Rule(final String takes, final String returns) {
            this.takes = takes;
            this.returns = returns;
            to = new ArrayList<>();
        }

        private Rule(final String takes, final String returns, final List<Possibility> to) {
            this.takes = takes;
            this.returns = returns;
            this.to = to;
        }

        private boolean add(final Possibility possibility) {
            return to.add(possibility);
        }
    }

    private static class Possibility {
        private final List<Token> tokens;
        private final List<String> codeLines;

        private Possibility(final List<Token> tokens) {
            this.tokens = new ArrayList<>(tokens);
            codeLines = new ArrayList<>();
        }

        private Possibility(final List<Token> tokens, final List<String> codeLines) {
            this.tokens = new ArrayList<>(tokens);
            this.codeLines = new ArrayList<>(codeLines);
        }
    }

    private static class Token {
        private final String name;
        private final String consumes;

        private Token(final String name, final String consumes) {
            this.name = name;
            this.consumes = consumes;
        }

        private Token(final String name) {
            this.name = name;
            this.consumes = "";
        }
    }

    public ParserGenerator(final List<String> lines, final String name) {
        this.lines = lines;
        lexerName = capitalize(name) + "Lexer";
        parserName = capitalize(name) + "Parser";
    }

    private void println() {
        code.append(System.lineSeparator());
    }

    private void println(final String str) {
        code.append(str).append(System.lineSeparator());
    }

    private void println(final int tab, final String str) {
        code.append("    ".repeat(tab)).append(str).append(System.lineSeparator());
    }

    private void println(final int tab, final String... strings) {
        for (final String s : strings) {
            code.append("    ".repeat(tab)).append(s).append(System.lineSeparator());
        }
    }

    private void printFn(final int tab, final String... strings) {
        println(tab, strings[0]);
        for (int i = 1; i < strings.length - 1; ++i) {
            code.append("    ".repeat(tab + 1)).append(strings[i]).append(System.lineSeparator());
        }
        if (strings.length > 1) {
            println(tab, strings[strings.length - 1]);
        }
    }

    private String replaceCode(final String line, final List<String> curResults, final int possNum) {
        String replacedCode = line;
        for (int i = 0; i < line.length(); ++i) {
            if (line.charAt(i) == '$' && i + 1 < line.length()) {
                if (Character.isDigit(line.charAt(i + 1))) {
                    int j = i + 2;
                    while (j < line.length() && Character.isDigit(line.charAt(j))) {
                        ++j;
                    }
                    final String digit = line.substring(i + 1, j);
                    final int num = Integer.parseInt(digit);
                    replacedCode = replacedCode.replace("$" + digit, curResults.get(num));
                    i = j;
                } else {
                    assert Character.isLetter(line.charAt(i + 1));
                    int j = i + 2;
                    while (j < line.length() && Character.isLetter(line.charAt(j))) {
                        ++j;
                    }
                    final String word = line.substring(i + 1, j);
                    replacedCode = replacedCode.replace("$" + word,
                            String.format("res%d.%s", possNum, word));
                }
            }
        }
        return replacedCode;
    }

    public void generate() throws IOException {
        filter();
        // System.out.println(first);
        // System.out.println(follow);

        println("package parser;");
        println();
        println(String.format("import lexer.%s;", lexerName));
        println(String.format("import lexer.%s.Token;", lexerName));
        println();
        println("import java.util.ArrayList;");
        println("import java.util.Arrays;");
        println("import java.util.List;");
        println();
        println(String.format("public class %s {", parserName));
        println(1, "private static abstract class Tree {");
        println(2, "protected final String node;");
        println(2, "protected final List<Tree> children;");
        println();
        printFn(2, "private Tree(final String node, final Tree... children) {",
                "this.node = node;",
                "this.children = Arrays.asList(children);",
                "}");
        println();
        printFn(2, "private Tree(final String node) {",
                "this.node = node;",
                "children = new ArrayList<>();",
                "}");
        println(1, "}");
        println();
        println(1, "private class TerminalTree extends Tree {");
        printFn(2, "private TerminalTree(final String node) {",
                "super(node);",
                "}");
        println(1, "}");
        println();
        println(1, String.format("private %s lexer;", lexerName));
        println();
        println(1, "private String consume(final Token token) {");
        println(2, "// System.out.println(\"consumed \" + token.name());");
        printFn(2, "if (lexer.getToken() != token) {",
                "throw new AssertionError(\"Expected \" + token.name() + \", but found \" " +
                        "+ lexer.getToken().name());",
                "}"
                );
        println(2, "final String res = lexer.getStr();");
        println(2, "lexer.nextToken();");
        println(2, "return res;");
        println(1, "}");
        println();
        printFn(1, "public StartTree parse(final String s) {",
                "// System.out.println(\"new parser\");",
                String.format("lexer = new %s(s);", lexerName),
                "lexer.nextToken();",
                "return start();",
                "}");
        println();

        for (final String non : parsers.keySet()) {
            // Node
            println(1, String.format("public static class %sTree extends Tree {", capitalize(non)));
            if (!parsers.get(non).returns.isEmpty()) {
                final String[] vars = parsers.get(non).returns.split(",");
                for (final String var : vars) {
                    println(2, String.format("public %s;", var));
                }
                println();
            }
            printFn(2, String.format("private %sTree(final String node, final Tree... children) {",
                        capitalize(non)),
                    "super(node, children);",
                    "}");
            println();
            printFn(2, String.format("private %sTree(final String node) {", capitalize(non)),
                    "super(node);",
                    "}");
            println(1, "}");
            // parse method
            println(1, String.format("private %sTree %s(%s) {", capitalize(non), non, parsers.get(non).takes));
            println(2, String.format("// System.out.println(\"%s\");", non));
            println(2, "switch (lexer.getToken()) {");
            Possibility firstHasEps = null;
            int possNum = 0;
            final Map<String, Integer> allResults = new HashMap<>();
            final List<String> cases = new ArrayList<>();
            for (final Possibility poss : parsers.get(non).to) {
                // cases
                if (first.get(poss.tokens.get(0).name).contains("EPS")) {
                    assert poss.tokens.get(0).name.equals("EPS") && poss.tokens.size() == 1;
                    firstHasEps = poss;
                    continue;
                }
                for (final String term : first.get(poss.tokens.get(0).name)) {
                    println(3, String.format("case %s:", term));
                    cases.add(term);
                }
                // case body
                final List<String> curResults = new ArrayList<>();
                for (final Token token : poss.tokens) {
                    final String name = token.name;
                    if (isPar(name)) {
                        allResults.putIfAbsent(name, 0);
                        allResults.put(name, allResults.get(name) + 1);
                        println(4, String.format("final %sTree %sRes%d = %s(%s);",
                                capitalize(name), name, allResults.get(name),
                                name, replaceCode(token.consumes, curResults, possNum)));
                        curResults.add(name + "Res" + allResults.get(name));
                    } else {
                        assert isLex(name);
                        final String var = name.toLowerCase();
                        allResults.putIfAbsent(var, 0);
                        allResults.put(var, allResults.get(var) + 1);
                        println(4, String.format("final Tree %sRes%d = new TerminalTree(%s);",
                                var, allResults.get(var), String.format("consume(Token.%s)", name)));
                        curResults.add(var + "Res" + allResults.get(var));
                    }
                }
                // result init
                println(4, String.format("final %sTree res%d = new %sTree(\"%s\", %s);",
                        capitalize(non), possNum, capitalize(non), non, String.join(", ", curResults)));
                // code paste
                for (final String line : poss.codeLines) {
                    println(4, replaceCode(line, curResults, possNum));
                }
                println(4, String.format("return res%d;", possNum));
                ++possNum;
            }
            // last case
            if (firstHasEps != null) {
                for (final String term : follow.get(non)) {
                    println(3, String.format("case %s:", term));
                    cases.add(term);
                }
                println(4, String.format("final %sTree res%d = new %sTree(\"%s\");",
                        capitalize(non), possNum, capitalize(non), non));
                for (final String line : firstHasEps.codeLines) {
                    println(4, replaceCode(line, null, possNum));
                }
                println(4, String.format("return res%d;", possNum));
            }
            // default
            println(3, "default:");
            println(4, String.format("throw new AssertionError(\"Expected %s, but found \" " +
                    "+ lexer.getToken().name());", String.join(", ", cases)));
            println(2, "}");
            println(1, "}");
            println();
        }
        println("}");

        Files.write(Path.of(DIR, parserName + ".java"), code.toString().getBytes(StandardCharsets.UTF_8));
    }

    private List<String> split(final String line) {
        // rule (...) [...] : next1 (...) next2 (...) ... {?
        // } next3 (...) ... {
        // }
        List<String> res = new ArrayList<>();
        int currPos = 0, copy;
        if (line.charAt(0) == '}') {
            res.add("}");
            ++currPos;
            while (currPos < line.length() && Character.isWhitespace(line.charAt(currPos))) {
                ++currPos;
            }
        } else {
            if (Character.isUpperCase(line.charAt(0))) {
                return Arrays.asList(line.split("\\s+").clone());
            }
            while (currPos < line.length() && !Character.isWhitespace(line.charAt(currPos))) {
                ++currPos;
            }
            res.add(line.substring(0, currPos));
            while (currPos < line.length() && Character.isWhitespace(line.charAt(currPos))) {
                ++currPos;
            }

            copy = currPos;
            assert line.charAt(copy) == '(';
            ++currPos;
            while (currPos < line.length() && line.charAt(currPos) != ')') {
                ++currPos;
            }
            ++currPos;
            res.add(line.substring(copy, currPos));
            while (currPos < line.length() && Character.isWhitespace(line.charAt(currPos))) {
                ++currPos;
            }

            copy = currPos;
            assert line.charAt(copy) == '[';
            ++currPos;
            while (currPos < line.length() && line.charAt(currPos) != ']') {
                ++currPos;
            }
            ++currPos;
            res.add(line.substring(copy, currPos));
            while (currPos < line.length() && Character.isWhitespace(line.charAt(currPos))) {
                ++currPos;
            }

            assert line.charAt(currPos) == ':';
            res.add(Character.toString(line.charAt(currPos)));
            ++currPos;
            while (currPos < line.length() && Character.isWhitespace(line.charAt(currPos))) {
                ++currPos;
            }
        }

        while (currPos < line.length()) {
            if (Character.isLowerCase(line.charAt(currPos))) {
                copy = currPos;
                while (currPos < line.length() && !Character.isWhitespace(line.charAt(currPos))) {
                    ++currPos;
                }
                res.add(line.substring(copy, currPos));
                while (currPos < line.length() && Character.isWhitespace(line.charAt(currPos))) {
                    ++currPos;
                }

                copy = currPos;
                assert line.charAt(copy) == '(';
                ++currPos;
                while (currPos < line.length() && line.charAt(currPos) != ')') {
                    ++currPos;
                }
                ++currPos;
                res.add(line.substring(copy, currPos));
                while (currPos < line.length() && Character.isWhitespace(line.charAt(currPos))) {
                    ++currPos;
                }
            } else if (Character.isUpperCase(line.charAt(currPos))){
                copy = currPos;
                while (currPos < line.length() && !Character.isWhitespace(line.charAt(currPos))) {
                    ++currPos;
                }
                res.add(line.substring(copy, currPos));
                while (currPos < line.length() && Character.isWhitespace(line.charAt(currPos))) {
                    ++currPos;
                }
            } else {
                res.add(Character.toString(line.charAt(currPos)));
                ++currPos;
                while (currPos < line.length() && Character.isWhitespace(line.charAt(currPos))) {
                    ++currPos;
                }
            }
        }

        return res;
    }

    private void filter() {
        for (int i = 0; i < lines.size(); ++i) {
            String line = lines.get(i);
            String[] rule = split(line).toArray(String[]::new);

            if (isLex(line)) {
                final String terminal = line.split(":")[0].trim();
                lexers.add(terminal);
                terminals.add(terminal);
            } else {
                // this is parse rule
                final String from = rule[0];
                final String takes = rule[1].substring(1, rule[1].length() - 1);
                final String returns = rule[2].substring(1, rule[2].length() - 1);

                final List<Token> tokens = new ArrayList<>();

                int j = 4;
                parsers.putIfAbsent(from, new Rule(takes, returns));
                nonTerminals.add(from);
                while (j <= rule.length) {
                    if (j == rule.length || rule[j].equals("|")) {
                        if (!tokens.isEmpty()) {
                            parsers.get(from).add(new Possibility(tokens));
                        }
                        tokens.clear();
                    } else if (rule[j].equals("{")) {
                        if (j != rule.length - 1) {
                            throw new IllegalStateException("} must be the end of the line " + line);
                        }
                        final List<String> codeLines = new ArrayList<>();
                        final int prevI = i;
                        ++i;
                        while (i < lines.size() && (prevI == i || !lines.get(i).startsWith("}"))) {
                            codeLines.add(lines.get(i).trim());
                            ++i;
                        }
                        if (i == lines.size()) {
                            throw new IllegalStateException("Couldn't find any } after {");
                        }
                        line = lines.get(i);
                        rule = split(line).toArray(String[]::new);
                        if (!rule[0].equals("}")) {
                            throw new IllegalStateException("After } must be space in line " + line);
                        }
                        j = 0;

                        parsers.get(from).add(new Possibility(tokens, codeLines));
                        tokens.clear();
                    } else {
                        if (isLex(rule[j])) {
                            terminals.add(rule[j]);
                            tokens.add(new Token(rule[j]));
                        } else {
                            assert isPar(rule[j]);
                            nonTerminals.add(rule[j]);
                            tokens.add(new Token(rule[j], rule[j + 1].substring(1, rule[j + 1].length() - 1)));
                            ++j;
                        }
                    }
                    ++j;
                }
            }
        }
        if (!parsers.containsKey("start")) {
            throw new IllegalStateException("Couldn't find start rule");
        }
        nonTerminals.forEach(non -> {
            if (!parsers.containsKey(non)) {
                throw new IllegalStateException("There is unreachable non-terminal " + non);
            }
        });
        findFIRST();
    }

    private void findFIRST() {
        for (final String ter : terminals) {
            first.put(ter, Set.of(ter));
        }
        for (final String non : parsers.keySet()) {
            first.put(non, new HashSet<>());
            if (parsers.get(non).to.stream().anyMatch( arr -> arr.tokens.get(0).name.equals("EPS"))) {
                first.get(non).add("EPS");
            }
        }
        boolean changed = true;
        while (changed) {
            changed = false;
            for (final String from : parsers.keySet()) {
                for (final Possibility poss : parsers.get(from).to) {
                    final List<Token> tokens = poss.tokens;
                    for (int i = 0; i < tokens.size(); ++i) {
                        final String to = tokens.get(i).name;
                        changed |= first.get(from).addAll(first.get(to));
                        if (!first.get(to).contains("EPS")) {
//                            if (i + 1 == toArr.size()) {
//                                changed |= first.get(from).add("EPS");
////                                // System.out.println("added lonely EPS");
//                            }
                            break;
                        }
                    }
                }
            }
        }
//        // System.out.println("first = " + first);

        constructFOLLOW();
    }

    private void constructFOLLOW() {
        for (final String non : nonTerminals) {
            follow.put(non, new HashSet<>());
        }
        follow.get("start").add("EOF");
        boolean changed = true;
        while (changed) {
            changed = false;
            for (final String from : parsers.keySet()) {
                for (final Possibility possibility : parsers.get(from).to) {
                    final List<Token> tokens = possibility.tokens;
                    // A -> alpha, alpha = beta B gamma
                    for (int i = 0; i < tokens.size(); ++i) {
                        final String to = tokens.get(i).name;
                        if (!isPar(to)) {
                            continue;
                        }

                        if (i + 1 == tokens.size()) {
                            changed |= follow.get(to).addAll(follow.get(from));
                        } else {
                            final Set<String> next = new HashSet<>(first.get(tokens.get(i + 1).name));
                            next.remove("EPS");
                            changed |= follow.get(to).addAll(next);
                        }
//                        final Set<String> firstGamma = new HashSet<>();
//                        if (i + 1 == toArr.size()) {
//                            firstGamma.add("EPS");
//                        } else {
//                            firstGamma.addAll(first.get(toArr.get(i + 1)));
//                        }
//
//                        boolean isEps = firstGamma.remove("EPS");
//                        changed |= follow.get(to).addAll(firstGamma);
//                        if (isEps) {
//                            changed |= follow.get(to).addAll(follow.get(from));
//                        }
                    }
                    if (tokens.size() > 1 && first.get(tokens.get(tokens.size() - 1).name).contains("EPS")) {
                        final String lst = tokens.get(tokens.size() - 2).name;
                        if (isPar(lst)) {
                            changed |= follow.get(lst).addAll(follow.get(from));
                        }
                    }
                }
            }
        }
//        // System.out.println("follow = " + follow);

        checkLL1();
    }

    private void checkLL1() {
        for (final String from : parsers.keySet()) {
            final List<Possibility> tos = parsers.get(from).to;
            if (tos.size() <= 1) {
                continue;
            }
            for (int i = 0; i < tos.size(); ++i) {
                for (int j = i + 1; j < tos.size(); ++j) {
                    final List<Token> a = tos.get(i).tokens;
                    final List<Token> b = tos.get(j).tokens;
                    tryIntersect(from, a, b);
                    tryIntersect(from, b, a);
                }
            }
        }
    }

    private String toString(final List<Token> tokens) {
        final List<String> to = tokens.stream().map(t -> t.name).collect(Collectors.toList());
        return to.toString();
    }

    private void tryIntersect(final String from, final List<Token> a, final List<Token> b) {
//        // System.out.println(from + " -> " + a);
//        // System.out.println(from + " -> " + b);
        final Set<String> alpha = first.get(a.get(0).name);
        final Set<String> beta = first.get(b.get(0).name);
        if (alpha.contains("EPS")) {
            final Set<String> folA = follow.get(from);
            final Set<String> inter = new HashSet<>(folA);
//            // System.out.println("follow = " + folA);
//            // System.out.println("first = " + beta);
            inter.retainAll(beta);
//            // System.out.println("intersect = " + inter);
            if (!inter.isEmpty()) {
                throw new IllegalStateException("intersection of FOLLOW and FIRST is not empty: "
                        + from + " -> " + toString(a) + ", "
                        + from + " -> " + toString(b) + ", "
                        + folA + ", " + beta);
            }
        } else {
            // A -> alpha, A -> beta => FIRST(alpha) doesn't intersect FIRST(beta)
            final Set<String> inter = new HashSet<>(alpha);
//            // System.out.println("first A = " + alpha);
//            // System.out.println("first B = " + beta);
            inter.retainAll(beta);
//            // System.out.println("intersect = " + inter);
            if (!inter.isEmpty()) {
                throw new IllegalStateException("intersection of FIRSTs is not empty: "
                        + from + " -> " + toString(a) + ", "
                        + from + " -> " + toString(b) + ", "
                        + alpha + ", " + beta);
            }
        }
    }
}
