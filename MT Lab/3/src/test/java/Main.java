import antlr.PrefixLexer;
import antlr.PrefixParser;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;

import java.io.IOException;
import java.util.*;
import java.util.stream.Collectors;

import static org.antlr.v4.runtime.CharStreams.fromFileName;

public class Main {
    public static void main(final String[] args) {
        try {
            final String source = "test.pr";
            final CharStream cs = fromFileName(source);
            final PrefixLexer lexer = new PrefixLexer(cs);
            final CommonTokenStream token = new CommonTokenStream(lexer);
            final PrefixParser parser = new PrefixParser(token);
            final PrefixParser.ProgramContext context = parser.program();
            final ParseTree tree = context;
            System.out.println(context.val);
        } catch (final Exception e) {
            System.err.println(e.getClass());
            System.err.println(e.getCause());
            System.err.println(e.getMessage());
        }

//        Set<String> set = new HashSet<>();
//        Set<String> emp = null;
//        set.add("a");
//        set.add("b");
//        set.addAll(emp);
//        System.out.println(String.join(", ", set));
    }
}
