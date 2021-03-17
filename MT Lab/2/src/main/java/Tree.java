import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class Tree {
    private final String node;
    private final List<Tree> children;

//    private int num;
//
//    public void setNum(final int n) {
//        num = n;
//    }
//
//    public int getNum() {
//        return num;
//    }

    public Tree(final String node, final Tree... children) {
        this.node = node;
        this.children = Arrays.asList(children);
    }

    public Tree(final String node, final boolean eps) {
        this.node = node;
        if (eps) {
            children = List.of(new Tree("eps", false));
        } else {
            children = Collections.emptyList();
        }
    }

    public String getNode() {
        return node;
    }

    public List<Tree> getChildren() {
        return children;
    }
}
