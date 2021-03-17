package generator;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;
import java.util.stream.Collectors;

public class Generator {
    private static final String DIR = "src/main/java/grammar/";

    public static String capitalize(final String str) {
        return Character.toUpperCase(str.charAt(0)) + str.substring(1);
    }

    public static boolean isLex(final String line) {
        return Character.isUpperCase(line.charAt(0));
    }

    public static boolean isPar(final String line) {
        return Character.isLowerCase(line.charAt(0));
    }

    public static void main(final String[] args) {
        if (args == null || args.length != 1) {
            System.err.println("Usage: Generator <grammar file>");
            return;
        }

        try {
            final List<String> lines = Files.readAllLines(Path.of(DIR, args[0]))
                    .stream()
                    .filter(s -> !s.isEmpty())
                    .map(String::trim)
                    .collect(Collectors.toList());
            final String name = args[0].split("\\.")[0];
            new ParserGenerator(lines, name).generate();
            new LexerGenerator(lines, name).generate();
        } catch (final IOException e) {
            System.err.println("Couldn't find file " + args[0] + " in " + DIR);
        }
    }
}
