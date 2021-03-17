import guru.nidi.graphviz.attribute.Color;
import guru.nidi.graphviz.attribute.Label;
import guru.nidi.graphviz.attribute.Rank;
import guru.nidi.graphviz.attribute.Style;
import guru.nidi.graphviz.engine.Format;
import guru.nidi.graphviz.engine.Graphviz;
import guru.nidi.graphviz.model.Graph;
import guru.nidi.graphviz.model.Node;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import static guru.nidi.graphviz.model.Factory.graph;
import static guru.nidi.graphviz.model.Factory.node;

public class Drawer {
    private int num;
    private Node dfs(final Tree tree) {
        Node vertex = node(tree.getNode() + " [" + (++num) + "]");
//        tree.setNum(num);
//        List<Integer> vertices = new ArrayList<>();
        for (final Tree ch : tree.getChildren()) {
            vertex = vertex.link(dfs(ch));
//            vertices.add(ch.getNum());
        }
//        System.out.println(tree.getNum() + " -> " + vertices);
        if (tree.getChildren().isEmpty() && !tree.getNode().equals("eps")) {
            vertex = vertex.with(Style.FILLED, Color.BLUE);
        }

        return vertex;
    }

    public void draw(final Tree tree, final String name) {
        num = 0;
        final Graph g = graph(name).directed().graphAttr().with(Rank.dir(Rank.RankDir.TOP_TO_BOTTOM))
                .with(dfs(tree));
        try {
            Graphviz.fromGraph(g).render(Format.PNG).toFile(new File(name));
        } catch (final IOException e) {
            e.printStackTrace();
        }
    }
}