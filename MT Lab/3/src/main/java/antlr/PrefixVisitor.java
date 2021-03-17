// Generated from /home/donaldo/Documents/MT/3/src/main/java/Prefix.g4 by ANTLR 4.9.1
package antlr;

    import java.util.Set;
    import java.util.HashSet;

import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link PrefixParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface PrefixVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link PrefixParser#program}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProgram(PrefixParser.ProgramContext ctx);
	/**
	 * Visit a parse tree produced by {@link PrefixParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExpr(PrefixParser.ExprContext ctx);
	/**
	 * Visit a parse tree produced by {@link PrefixParser#whileBody}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitWhileBody(PrefixParser.WhileBodyContext ctx);
	/**
	 * Visit a parse tree produced by {@link PrefixParser#ifBody}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIfBody(PrefixParser.IfBodyContext ctx);
	/**
	 * Visit a parse tree produced by {@link PrefixParser#elseBody}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitElseBody(PrefixParser.ElseBodyContext ctx);
	/**
	 * Visit a parse tree produced by {@link PrefixParser#print}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPrint(PrefixParser.PrintContext ctx);
	/**
	 * Visit a parse tree produced by {@link PrefixParser#assign}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAssign(PrefixParser.AssignContext ctx);
	/**
	 * Visit a parse tree produced by {@link PrefixParser#rvalue}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRvalue(PrefixParser.RvalueContext ctx);
	/**
	 * Visit a parse tree produced by {@link PrefixParser#logic}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLogic(PrefixParser.LogicContext ctx);
	/**
	 * Visit a parse tree produced by {@link PrefixParser#cmpOp}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCmpOp(PrefixParser.CmpOpContext ctx);
	/**
	 * Visit a parse tree produced by {@link PrefixParser#logicOp}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLogicOp(PrefixParser.LogicOpContext ctx);
	/**
	 * Visit a parse tree produced by {@link PrefixParser#calc}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCalc(PrefixParser.CalcContext ctx);
	/**
	 * Visit a parse tree produced by {@link PrefixParser#mathOp}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMathOp(PrefixParser.MathOpContext ctx);
}