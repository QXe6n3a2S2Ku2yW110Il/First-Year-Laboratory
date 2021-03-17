package generator;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;

import static generator.Generator.capitalize;
import static generator.Generator.isLex;

public class LexerGenerator {
    private final List<String> lines;

    private final StringBuilder code = new StringBuilder();
    private final String lexerName;

    private final List<String> tokens = new ArrayList<>();
    private final Map<String, Rule> rules = new HashMap<>();

    private final static String DIR = "src/main/java/lexer/";

    private static class Rule {
        private final String str;
        private final boolean isRegex;

        public Rule(final String str, final boolean isRegex) {
            this.str = str;
            this.isRegex = isRegex;
        }
    }

    public LexerGenerator(final List<String> lines, final String name) {
        this.lines = lines;
        lexerName = capitalize(name) + "Lexer";
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

    public void generate() throws IOException {
        println("package lexer;");
        println();
        println(String.format("public class %s {", lexerName));
        println(1, "private Token curToken;",
                "private int position = 0;",
                "private final String s;",
                "private String tokenStr;");
        println();
        // Getters
        printFn(1, "public Token getToken() {",
                "return curToken;",
                "}");
        println();
        printFn(1, "public String getStr() {",
                "return tokenStr;",
                "}");
        println();
        // Constructor
        printFn(1, String.format("public %s(final String s) {", lexerName),
                "this.s = s;",
                "position = 0;",
                "}");
        println();

        for (final String line : lines) {
            if (isLex(line)) {
                parseRule(line);
            }
        }

        // Tokens
        println(1, "public enum Token {");
        for (final String token : tokens) {
            println(2, token + ",");
        }
        println(2, "EPS,", "EOF");
        println(1, "}");
        println();

        generateNextToken();
        println("}");

        Files.write(Path.of(DIR, lexerName + ".java"), code.toString().getBytes(StandardCharsets.UTF_8));
    }

    private void parseRule(final String line) {
        final String[] args = Arrays.stream(line.split(":")).map(String::trim).toArray(String[]::new);
        assert args.length == 2;
        tokens.add(args[0]);
        if (args[1].startsWith("\"") || args[1].startsWith("'")) {
            rules.put(args[0], new Rule(args[1].substring(1, args[1].length() - 1), false));
        } else {
            rules.put(args[0], new Rule(args[1], true));
        }
    }

    private void generateNextToken() {
        println(1, "public void nextToken() {");
//        println(2, "int currPos = position + 1;");
//        printFn(2, "while (currPos < s.length() && " +
//                        "s.substring(position, currPos).matches(\"[ \\t\\r\\n]+\")) {",
//                "++currPos;",
//                "}");
//        println(2, "position = currPos == position + 1 ? position : currPos;");
        println(2, "for (int i = s.length(); i >= position; --i) {");
        printFn(3, "if (s.substring(position, i).matches(\"[ \\t\\r\\n]+\")) {",
                "position = i;",
                "break;",
                "}");
        println(2, "}");
        printFn(2, "if (position == s.length()) {",
                "curToken = Token.EOF;",
                "return;",
                "}");
        println();

        for (final String token : tokens) {
            final Rule rule = rules.get(token);
            if (rule.isRegex) {
                final String regex = rule.str;
                println(2, "for (int i = s.length(); i >= position; --i) {");
                printFn(3, String.format("if (s.substring(position, i).matches(\"%s\")) {", regex),
                        "tokenStr = s.substring(position, i);",
                        "position = i;",
                        String.format("curToken = Token.%s;", token),
                        "return;",
                        "}");
                println(2, "}");
            } else {
                final String str = rule.str;
                printFn(2, String.format("if (position + %d <= s.length() && " +
                                "s.startsWith(\"%s\", position)) {",
                        str.length(), str),
                        String.format("tokenStr = s.substring(position, position + %d);",
                                str.length()),
                        String.format("position += %d;", str.length()),
                        String.format("curToken = Token.%s;", token),
                        "return;",
                        "}"
                );
            }
            println();
        }

        println(2, "curToken = Token.EPS;");
        println(1, "}");
    }
}
