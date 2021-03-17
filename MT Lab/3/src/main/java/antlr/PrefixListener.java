// Generated from /home/donaldo/Documents/MT/3/src/main/java/Prefix.g4 by ANTLR 4.9.1
package antlr;

    import java.util.Set;
    import java.util.HashSet;

import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link PrefixParser}.
 */
public interface PrefixListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link PrefixParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(PrefixParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrefixParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(PrefixParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrefixParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExpr(PrefixParser.ExprContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrefixParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExpr(PrefixParser.ExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrefixParser#whileBody}.
	 * @param ctx the parse tree
	 */
	void enterWhileBody(PrefixParser.WhileBodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrefixParser#whileBody}.
	 * @param ctx the parse tree
	 */
	void exitWhileBody(PrefixParser.WhileBodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrefixParser#ifBody}.
	 * @param ctx the parse tree
	 */
	void enterIfBody(PrefixParser.IfBodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrefixParser#ifBody}.
	 * @param ctx the parse tree
	 */
	void exitIfBody(PrefixParser.IfBodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrefixParser#elseBody}.
	 * @param ctx the parse tree
	 */
	void enterElseBody(PrefixParser.ElseBodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrefixParser#elseBody}.
	 * @param ctx the parse tree
	 */
	void exitElseBody(PrefixParser.ElseBodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrefixParser#print}.
	 * @param ctx the parse tree
	 */
	void enterPrint(PrefixParser.PrintContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrefixParser#print}.
	 * @param ctx the parse tree
	 */
	void exitPrint(PrefixParser.PrintContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrefixParser#assign}.
	 * @param ctx the parse tree
	 */
	void enterAssign(PrefixParser.AssignContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrefixParser#assign}.
	 * @param ctx the parse tree
	 */
	void exitAssign(PrefixParser.AssignContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrefixParser#rvalue}.
	 * @param ctx the parse tree
	 */
	void enterRvalue(PrefixParser.RvalueContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrefixParser#rvalue}.
	 * @param ctx the parse tree
	 */
	void exitRvalue(PrefixParser.RvalueContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrefixParser#logic}.
	 * @param ctx the parse tree
	 */
	void enterLogic(PrefixParser.LogicContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrefixParser#logic}.
	 * @param ctx the parse tree
	 */
	void exitLogic(PrefixParser.LogicContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrefixParser#cmpOp}.
	 * @param ctx the parse tree
	 */
	void enterCmpOp(PrefixParser.CmpOpContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrefixParser#cmpOp}.
	 * @param ctx the parse tree
	 */
	void exitCmpOp(PrefixParser.CmpOpContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrefixParser#logicOp}.
	 * @param ctx the parse tree
	 */
	void enterLogicOp(PrefixParser.LogicOpContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrefixParser#logicOp}.
	 * @param ctx the parse tree
	 */
	void exitLogicOp(PrefixParser.LogicOpContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrefixParser#calc}.
	 * @param ctx the parse tree
	 */
	void enterCalc(PrefixParser.CalcContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrefixParser#calc}.
	 * @param ctx the parse tree
	 */
	void exitCalc(PrefixParser.CalcContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrefixParser#mathOp}.
	 * @param ctx the parse tree
	 */
	void enterMathOp(PrefixParser.MathOpContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrefixParser#mathOp}.
	 * @param ctx the parse tree
	 */
	void exitMathOp(PrefixParser.MathOpContext ctx);
}