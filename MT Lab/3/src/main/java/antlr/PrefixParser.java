// Generated from /home/donaldo/Documents/MT/3/src/main/java/Prefix.g4 by ANTLR 4.9.1
package antlr;

    import java.util.Set;
    import java.util.HashSet;

import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class PrefixParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.9.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		WHITESPACE=1, NUMBER=2, PLUS=3, MINUS=4, MUL=5, DIV=6, DEF=7, EQUALS=8, 
		NOT_EQUAL=9, LESS=10, LESS_EQUAL=11, GREATER=12, GREATER_EQUAL=13, AND=14, 
		OR=15, NOT=16, TRUE=17, FALSE=18, IF=19, PRINT=20, WHILE=21, VARIABLE=22;
	public static final int
		RULE_program = 0, RULE_expr = 1, RULE_whileBody = 2, RULE_ifBody = 3, 
		RULE_elseBody = 4, RULE_print = 5, RULE_assign = 6, RULE_rvalue = 7, RULE_logic = 8, 
		RULE_cmpOp = 9, RULE_logicOp = 10, RULE_calc = 11, RULE_mathOp = 12;
	private static String[] makeRuleNames() {
		return new String[] {
			"program", "expr", "whileBody", "ifBody", "elseBody", "print", "assign", 
			"rvalue", "logic", "cmpOp", "logicOp", "calc", "mathOp"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, null, null, "'+'", "'-'", "'*'", "'/'", "'='", "'=='", "'!='", 
			"'<'", "'<='", "'>'", "'>='", "'and'", "'or'", "'not'", "'true'", "'false'", 
			"'if'", "'print'", "'while'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "WHITESPACE", "NUMBER", "PLUS", "MINUS", "MUL", "DIV", "DEF", "EQUALS", 
			"NOT_EQUAL", "LESS", "LESS_EQUAL", "GREATER", "GREATER_EQUAL", "AND", 
			"OR", "NOT", "TRUE", "FALSE", "IF", "PRINT", "WHILE", "VARIABLE"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "Prefix.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public PrefixParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class ProgramContext extends ParserRuleContext {
		public String val;
		public String global;
		public ExprContext ex;
		public TerminalNode EOF() { return getToken(PrefixParser.EOF, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).enterProgram(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).exitProgram(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PrefixVisitor ) return ((PrefixVisitor<? extends T>)visitor).visitProgram(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(26);
			((ProgramContext)_localctx).ex = expr(1);
			setState(27);
			match(EOF);

			    // System.out.println("in program ((ProgramContext)_localctx).ex.vars is " + (((ProgramContext)_localctx).ex.vars == null ? "null" : ((ProgramContext)_localctx).ex.vars));
			    ((ProgramContext)_localctx).global =  ((ProgramContext)_localctx).ex.vars.isEmpty() ? "" : "int " + String.join(" = 0, ", ((ProgramContext)_localctx).ex.vars) + " = 0;\n\n";
			    ((ProgramContext)_localctx).val =  String.format("#include <iostream>\n\n%sint main() {\n%s\n\treturn 0;\n}", _localctx.global, ((ProgramContext)_localctx).ex.val);

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExprContext extends ParserRuleContext {
		public int tab;
		public String val;
		public Set<String> vars;
		public IfBodyContext ex;
		public PrintContext pr;
		public AssignContext ass;
		public WhileBodyContext wh;
		public IfBodyContext ifBody() {
			return getRuleContext(IfBodyContext.class,0);
		}
		public PrintContext print() {
			return getRuleContext(PrintContext.class,0);
		}
		public AssignContext assign() {
			return getRuleContext(AssignContext.class,0);
		}
		public WhileBodyContext whileBody() {
			return getRuleContext(WhileBodyContext.class,0);
		}
		public ExprContext(ParserRuleContext parent, int invokingState) { super(parent, invokingState); }
		public ExprContext(ParserRuleContext parent, int invokingState, int tab) {
			super(parent, invokingState);
			this.tab = tab;
		}
		@Override public int getRuleIndex() { return RULE_expr; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).enterExpr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).exitExpr(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PrefixVisitor ) return ((PrefixVisitor<? extends T>)visitor).visitExpr(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ExprContext expr(int tab) throws RecognitionException {
		ExprContext _localctx = new ExprContext(_ctx, getState(), tab);
		enterRule(_localctx, 2, RULE_expr);
		((ExprContext)_localctx).vars =  new HashSet<>();
		try {
			setState(42);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case IF:
				enterOuterAlt(_localctx, 1);
				{
				setState(30);
				((ExprContext)_localctx).ex = ifBody(tab);

				    ((ExprContext)_localctx).val =  ((ExprContext)_localctx).ex.val;
				    ((ExprContext)_localctx).vars =  ((ExprContext)_localctx).ex.vars;

				}
				break;
			case PRINT:
				enterOuterAlt(_localctx, 2);
				{
				setState(33);
				((ExprContext)_localctx).pr = print(tab);

				    ((ExprContext)_localctx).val =  ((ExprContext)_localctx).pr.val + "\n";
				    _localctx.vars.addAll(((ExprContext)_localctx).pr.vars);

				}
				break;
			case DEF:
				enterOuterAlt(_localctx, 3);
				{
				setState(36);
				((ExprContext)_localctx).ass = assign(tab);

				    ((ExprContext)_localctx).val =  ((ExprContext)_localctx).ass.val + "\n";
				    ((ExprContext)_localctx).vars =  ((ExprContext)_localctx).ass.vars;
				    // System.out.println("vars now " + _localctx.vars);

				}
				break;
			case WHILE:
				enterOuterAlt(_localctx, 4);
				{
				setState(39);
				((ExprContext)_localctx).wh = whileBody(tab);

				    ((ExprContext)_localctx).val =  ((ExprContext)_localctx).wh.val + "\n";
				    ((ExprContext)_localctx).vars =  ((ExprContext)_localctx).wh.vars;

				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class WhileBodyContext extends ParserRuleContext {
		public int tab;
		public String val;
		public Set<String> vars;
		public LogicContext l;
		public ExprContext ex;
		public TerminalNode WHILE() { return getToken(PrefixParser.WHILE, 0); }
		public LogicContext logic() {
			return getRuleContext(LogicContext.class,0);
		}
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public WhileBodyContext(ParserRuleContext parent, int invokingState) { super(parent, invokingState); }
		public WhileBodyContext(ParserRuleContext parent, int invokingState, int tab) {
			super(parent, invokingState);
			this.tab = tab;
		}
		@Override public int getRuleIndex() { return RULE_whileBody; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).enterWhileBody(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).exitWhileBody(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PrefixVisitor ) return ((PrefixVisitor<? extends T>)visitor).visitWhileBody(this);
			else return visitor.visitChildren(this);
		}
	}

	public final WhileBodyContext whileBody(int tab) throws RecognitionException {
		WhileBodyContext _localctx = new WhileBodyContext(_ctx, getState(), tab);
		enterRule(_localctx, 4, RULE_whileBody);
		((WhileBodyContext)_localctx).vars =  new HashSet<>();
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(44);
			match(WHILE);
			setState(45);
			((WhileBodyContext)_localctx).l = logic();
			setState(46);
			((WhileBodyContext)_localctx).ex = expr(tab + 1);

			    ((WhileBodyContext)_localctx).val =  String.format("%swhile (%s) {\n%s%s}", "\t".repeat(_localctx.tab), ((WhileBodyContext)_localctx).l.val, ((WhileBodyContext)_localctx).ex.val, "\t".repeat(_localctx.tab));
			    ((WhileBodyContext)_localctx).vars =  ((WhileBodyContext)_localctx).l.vars;
			    _localctx.vars.addAll(((WhileBodyContext)_localctx).ex.vars);

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class IfBodyContext extends ParserRuleContext {
		public int tab;
		public String val;
		public Set<String> vars;
		public LogicContext l;
		public ExprContext ex;
		public ElseBodyContext el;
		public TerminalNode IF() { return getToken(PrefixParser.IF, 0); }
		public LogicContext logic() {
			return getRuleContext(LogicContext.class,0);
		}
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public ElseBodyContext elseBody() {
			return getRuleContext(ElseBodyContext.class,0);
		}
		public IfBodyContext(ParserRuleContext parent, int invokingState) { super(parent, invokingState); }
		public IfBodyContext(ParserRuleContext parent, int invokingState, int tab) {
			super(parent, invokingState);
			this.tab = tab;
		}
		@Override public int getRuleIndex() { return RULE_ifBody; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).enterIfBody(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).exitIfBody(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PrefixVisitor ) return ((PrefixVisitor<? extends T>)visitor).visitIfBody(this);
			else return visitor.visitChildren(this);
		}
	}

	public final IfBodyContext ifBody(int tab) throws RecognitionException {
		IfBodyContext _localctx = new IfBodyContext(_ctx, getState(), tab);
		enterRule(_localctx, 6, RULE_ifBody);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(49);
			match(IF);
			setState(50);
			((IfBodyContext)_localctx).l = logic();
			setState(51);
			((IfBodyContext)_localctx).ex = expr(tab + 1);
			setState(52);
			((IfBodyContext)_localctx).el = elseBody(tab);

			    ((IfBodyContext)_localctx).val =  String.format("%sif (%s) {\n%s%s}%s\n", "\t".repeat(_localctx.tab), ((IfBodyContext)_localctx).l.val, ((IfBodyContext)_localctx).ex.val, "\t".repeat(_localctx.tab), ((IfBodyContext)_localctx).el.val);
			    ((IfBodyContext)_localctx).vars =  ((IfBodyContext)_localctx).l.vars;
			    _localctx.vars.addAll(((IfBodyContext)_localctx).ex.vars);
			    _localctx.vars.addAll(((IfBodyContext)_localctx).el.vars);

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ElseBodyContext extends ParserRuleContext {
		public int tab;
		public String val;
		public Set<String> vars;
		public ExprContext ex;
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public ElseBodyContext(ParserRuleContext parent, int invokingState) { super(parent, invokingState); }
		public ElseBodyContext(ParserRuleContext parent, int invokingState, int tab) {
			super(parent, invokingState);
			this.tab = tab;
		}
		@Override public int getRuleIndex() { return RULE_elseBody; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).enterElseBody(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).exitElseBody(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PrefixVisitor ) return ((PrefixVisitor<? extends T>)visitor).visitElseBody(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ElseBodyContext elseBody(int tab) throws RecognitionException {
		ElseBodyContext _localctx = new ElseBodyContext(_ctx, getState(), tab);
		enterRule(_localctx, 8, RULE_elseBody);
		try {
			setState(59);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,1,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(55);
				((ElseBodyContext)_localctx).ex = expr(tab + 1);

				    ((ElseBodyContext)_localctx).val =  String.format(" else {\n%s%s}", ((ElseBodyContext)_localctx).ex.val, "\t".repeat(_localctx.tab));
				    ((ElseBodyContext)_localctx).vars =  ((ElseBodyContext)_localctx).ex.vars;

				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{

				    ((ElseBodyContext)_localctx).val =  "";
				    ((ElseBodyContext)_localctx).vars =  new HashSet<>();

				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class PrintContext extends ParserRuleContext {
		public int tab;
		public String val;
		public Set<String> vars;
		public RvalueContext v;
		public TerminalNode PRINT() { return getToken(PrefixParser.PRINT, 0); }
		public RvalueContext rvalue() {
			return getRuleContext(RvalueContext.class,0);
		}
		public PrintContext(ParserRuleContext parent, int invokingState) { super(parent, invokingState); }
		public PrintContext(ParserRuleContext parent, int invokingState, int tab) {
			super(parent, invokingState);
			this.tab = tab;
		}
		@Override public int getRuleIndex() { return RULE_print; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).enterPrint(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).exitPrint(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PrefixVisitor ) return ((PrefixVisitor<? extends T>)visitor).visitPrint(this);
			else return visitor.visitChildren(this);
		}
	}

	public final PrintContext print(int tab) throws RecognitionException {
		PrintContext _localctx = new PrintContext(_ctx, getState(), tab);
		enterRule(_localctx, 10, RULE_print);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(61);
			match(PRINT);
			setState(62);
			((PrintContext)_localctx).v = rvalue();

			    ((PrintContext)_localctx).val =  String.format("%sstd::cout << %s << '\\n';", "\t".repeat(_localctx.tab), ((PrintContext)_localctx).v.val);
			    ((PrintContext)_localctx).vars =  ((PrintContext)_localctx).v.vars;
			    // System.out.println("print: " + _localctx.val + ", vars = " + _localctx.vars);

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AssignContext extends ParserRuleContext {
		public int tab;
		public String val;
		public Set<String> vars;
		public Token var;
		public RvalueContext v;
		public TerminalNode DEF() { return getToken(PrefixParser.DEF, 0); }
		public TerminalNode VARIABLE() { return getToken(PrefixParser.VARIABLE, 0); }
		public RvalueContext rvalue() {
			return getRuleContext(RvalueContext.class,0);
		}
		public AssignContext(ParserRuleContext parent, int invokingState) { super(parent, invokingState); }
		public AssignContext(ParserRuleContext parent, int invokingState, int tab) {
			super(parent, invokingState);
			this.tab = tab;
		}
		@Override public int getRuleIndex() { return RULE_assign; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).enterAssign(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).exitAssign(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PrefixVisitor ) return ((PrefixVisitor<? extends T>)visitor).visitAssign(this);
			else return visitor.visitChildren(this);
		}
	}

	public final AssignContext assign(int tab) throws RecognitionException {
		AssignContext _localctx = new AssignContext(_ctx, getState(), tab);
		enterRule(_localctx, 12, RULE_assign);
		((AssignContext)_localctx).vars =  new HashSet<>();
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(65);
			match(DEF);
			setState(66);
			((AssignContext)_localctx).var = match(VARIABLE);
			setState(67);
			((AssignContext)_localctx).v = rvalue();

			    ((AssignContext)_localctx).val =  String.format("%s%s = %s;", "\t".repeat(_localctx.tab), (((AssignContext)_localctx).var!=null?((AssignContext)_localctx).var.getText():null), ((AssignContext)_localctx).v.val);
			    _localctx.vars.add((((AssignContext)_localctx).var!=null?((AssignContext)_localctx).var.getText():null));
			    _localctx.vars.addAll(((AssignContext)_localctx).v.vars);
			    // System.out.println("assign: " + _localctx.val + ", vars = " + _localctx.vars);

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class RvalueContext extends ParserRuleContext {
		public String val;
		public Set<String> vars;
		public Token var;
		public CalcContext num;
		public LogicContext l;
		public TerminalNode VARIABLE() { return getToken(PrefixParser.VARIABLE, 0); }
		public CalcContext calc() {
			return getRuleContext(CalcContext.class,0);
		}
		public LogicContext logic() {
			return getRuleContext(LogicContext.class,0);
		}
		public RvalueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_rvalue; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).enterRvalue(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).exitRvalue(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PrefixVisitor ) return ((PrefixVisitor<? extends T>)visitor).visitRvalue(this);
			else return visitor.visitChildren(this);
		}
	}

	public final RvalueContext rvalue() throws RecognitionException {
		RvalueContext _localctx = new RvalueContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_rvalue);
		((RvalueContext)_localctx).vars =  new HashSet<>();
		try {
			setState(78);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,2,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(70);
				((RvalueContext)_localctx).var = match(VARIABLE);

				    ((RvalueContext)_localctx).val =  (((RvalueContext)_localctx).var!=null?((RvalueContext)_localctx).var.getText():null);
				    _localctx.vars.add(_localctx.val);
				    // System.out.println("rvalue var!");

				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(72);
				((RvalueContext)_localctx).num = calc();

				    ((RvalueContext)_localctx).val =  ((RvalueContext)_localctx).num.val;
				    ((RvalueContext)_localctx).vars =  ((RvalueContext)_localctx).num.vars;
				    // System.out.println("rvalue calc!");

				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(75);
				((RvalueContext)_localctx).l = logic();

				    ((RvalueContext)_localctx).val =  ((RvalueContext)_localctx).l.val;
				    ((RvalueContext)_localctx).vars =  ((RvalueContext)_localctx).l.vars;
				    // System.out.println("rvalue logic!");

				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			/* System.out.println("rvalue = " + $val + ", vars = " + $vars);*/
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LogicContext extends ParserRuleContext {
		public String val;
		public Set<String> vars;
		public CmpOpContext op;
		public CalcContext v1;
		public CalcContext v2;
		public LogicContext l;
		public LogicOpContext op_;
		public LogicContext x1;
		public LogicContext x2;
		public CmpOpContext cmpOp() {
			return getRuleContext(CmpOpContext.class,0);
		}
		public List<CalcContext> calc() {
			return getRuleContexts(CalcContext.class);
		}
		public CalcContext calc(int i) {
			return getRuleContext(CalcContext.class,i);
		}
		public TerminalNode NOT() { return getToken(PrefixParser.NOT, 0); }
		public List<LogicContext> logic() {
			return getRuleContexts(LogicContext.class);
		}
		public LogicContext logic(int i) {
			return getRuleContext(LogicContext.class,i);
		}
		public TerminalNode TRUE() { return getToken(PrefixParser.TRUE, 0); }
		public TerminalNode FALSE() { return getToken(PrefixParser.FALSE, 0); }
		public LogicOpContext logicOp() {
			return getRuleContext(LogicOpContext.class,0);
		}
		public LogicContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_logic; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).enterLogic(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).exitLogic(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PrefixVisitor ) return ((PrefixVisitor<? extends T>)visitor).visitLogic(this);
			else return visitor.visitChildren(this);
		}
	}

	public final LogicContext logic() throws RecognitionException {
		LogicContext _localctx = new LogicContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_logic);
		((LogicContext)_localctx).vars =  new HashSet<>();
		try {
			setState(98);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case EQUALS:
			case NOT_EQUAL:
			case LESS:
			case LESS_EQUAL:
			case GREATER:
			case GREATER_EQUAL:
				enterOuterAlt(_localctx, 1);
				{
				setState(80);
				((LogicContext)_localctx).op = cmpOp();
				setState(81);
				((LogicContext)_localctx).v1 = calc();
				setState(82);
				((LogicContext)_localctx).v2 = calc();

				    ((LogicContext)_localctx).val =  String.format("%s %s %s", ((LogicContext)_localctx).v1.val, ((LogicContext)_localctx).op.op, ((LogicContext)_localctx).v2.val);
				    _localctx.vars.addAll(((LogicContext)_localctx).v1.vars);
				    _localctx.vars.addAll(((LogicContext)_localctx).v2.vars);

				}
				break;
			case NOT:
				enterOuterAlt(_localctx, 2);
				{
				setState(85);
				match(NOT);
				setState(86);
				((LogicContext)_localctx).l = logic();

				    ((LogicContext)_localctx).val =  String.format("!(%s)", ((LogicContext)_localctx).l.val);
				    ((LogicContext)_localctx).vars =  ((LogicContext)_localctx).l.vars;

				}
				break;
			case TRUE:
				enterOuterAlt(_localctx, 3);
				{
				setState(89);
				match(TRUE);
				((LogicContext)_localctx).val =  "true";
				}
				break;
			case FALSE:
				enterOuterAlt(_localctx, 4);
				{
				setState(91);
				match(FALSE);
				((LogicContext)_localctx).val =  "false";
				}
				break;
			case AND:
			case OR:
				enterOuterAlt(_localctx, 5);
				{
				setState(93);
				((LogicContext)_localctx).op_ = logicOp();
				setState(94);
				((LogicContext)_localctx).x1 = logic();
				setState(95);
				((LogicContext)_localctx).x2 = logic();

				    ((LogicContext)_localctx).val =  String.format("(%s %s %s)", ((LogicContext)_localctx).x1.val, ((LogicContext)_localctx).op_.op, ((LogicContext)_localctx).x2.val);
				    _localctx.vars.addAll(((LogicContext)_localctx).x1.vars);
				    _localctx.vars.addAll(((LogicContext)_localctx).x2.vars);

				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class CmpOpContext extends ParserRuleContext {
		public String op;
		public TerminalNode EQUALS() { return getToken(PrefixParser.EQUALS, 0); }
		public TerminalNode NOT_EQUAL() { return getToken(PrefixParser.NOT_EQUAL, 0); }
		public TerminalNode LESS() { return getToken(PrefixParser.LESS, 0); }
		public TerminalNode LESS_EQUAL() { return getToken(PrefixParser.LESS_EQUAL, 0); }
		public TerminalNode GREATER() { return getToken(PrefixParser.GREATER, 0); }
		public TerminalNode GREATER_EQUAL() { return getToken(PrefixParser.GREATER_EQUAL, 0); }
		public CmpOpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_cmpOp; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).enterCmpOp(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).exitCmpOp(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PrefixVisitor ) return ((PrefixVisitor<? extends T>)visitor).visitCmpOp(this);
			else return visitor.visitChildren(this);
		}
	}

	public final CmpOpContext cmpOp() throws RecognitionException {
		CmpOpContext _localctx = new CmpOpContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_cmpOp);
		try {
			setState(112);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case EQUALS:
				enterOuterAlt(_localctx, 1);
				{
				setState(100);
				match(EQUALS);
				((CmpOpContext)_localctx).op =  "==";
				}
				break;
			case NOT_EQUAL:
				enterOuterAlt(_localctx, 2);
				{
				setState(102);
				match(NOT_EQUAL);
				((CmpOpContext)_localctx).op =  "!=";
				}
				break;
			case LESS:
				enterOuterAlt(_localctx, 3);
				{
				setState(104);
				match(LESS);
				((CmpOpContext)_localctx).op =  "<";
				}
				break;
			case LESS_EQUAL:
				enterOuterAlt(_localctx, 4);
				{
				setState(106);
				match(LESS_EQUAL);
				((CmpOpContext)_localctx).op =  "<=";
				}
				break;
			case GREATER:
				enterOuterAlt(_localctx, 5);
				{
				setState(108);
				match(GREATER);
				((CmpOpContext)_localctx).op =  ">";
				}
				break;
			case GREATER_EQUAL:
				enterOuterAlt(_localctx, 6);
				{
				setState(110);
				match(GREATER_EQUAL);
				((CmpOpContext)_localctx).op =  ">=";
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LogicOpContext extends ParserRuleContext {
		public String op;
		public TerminalNode AND() { return getToken(PrefixParser.AND, 0); }
		public TerminalNode OR() { return getToken(PrefixParser.OR, 0); }
		public LogicOpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_logicOp; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).enterLogicOp(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).exitLogicOp(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PrefixVisitor ) return ((PrefixVisitor<? extends T>)visitor).visitLogicOp(this);
			else return visitor.visitChildren(this);
		}
	}

	public final LogicOpContext logicOp() throws RecognitionException {
		LogicOpContext _localctx = new LogicOpContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_logicOp);
		try {
			setState(118);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case AND:
				enterOuterAlt(_localctx, 1);
				{
				setState(114);
				match(AND);
				((LogicOpContext)_localctx).op =  "&&";
				}
				break;
			case OR:
				enterOuterAlt(_localctx, 2);
				{
				setState(116);
				match(OR);
				((LogicOpContext)_localctx).op =  "||";
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class CalcContext extends ParserRuleContext {
		public String val;
		public Set<String> vars;
		public MathOpContext op;
		public CalcContext v1;
		public CalcContext v2;
		public Token num;
		public Token var;
		public MathOpContext mathOp() {
			return getRuleContext(MathOpContext.class,0);
		}
		public List<CalcContext> calc() {
			return getRuleContexts(CalcContext.class);
		}
		public CalcContext calc(int i) {
			return getRuleContext(CalcContext.class,i);
		}
		public TerminalNode NUMBER() { return getToken(PrefixParser.NUMBER, 0); }
		public TerminalNode VARIABLE() { return getToken(PrefixParser.VARIABLE, 0); }
		public CalcContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_calc; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).enterCalc(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).exitCalc(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PrefixVisitor ) return ((PrefixVisitor<? extends T>)visitor).visitCalc(this);
			else return visitor.visitChildren(this);
		}
	}

	public final CalcContext calc() throws RecognitionException {
		CalcContext _localctx = new CalcContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_calc);
		((CalcContext)_localctx).vars =  new HashSet<>();
		try {
			setState(129);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case PLUS:
			case MINUS:
			case MUL:
			case DIV:
				enterOuterAlt(_localctx, 1);
				{
				setState(120);
				((CalcContext)_localctx).op = mathOp();
				setState(121);
				((CalcContext)_localctx).v1 = calc();
				setState(122);
				((CalcContext)_localctx).v2 = calc();

				    ((CalcContext)_localctx).val =  String.format("(%s %s %s)", ((CalcContext)_localctx).v1.val, ((CalcContext)_localctx).op.op, ((CalcContext)_localctx).v2.val);
				    _localctx.vars.addAll(((CalcContext)_localctx).v1.vars);
				    _localctx.vars.addAll(((CalcContext)_localctx).v2.vars);

				}
				break;
			case NUMBER:
				enterOuterAlt(_localctx, 2);
				{
				setState(125);
				((CalcContext)_localctx).num = match(NUMBER);
				((CalcContext)_localctx).val =  (((CalcContext)_localctx).num!=null?((CalcContext)_localctx).num.getText():null);
				}
				break;
			case VARIABLE:
				enterOuterAlt(_localctx, 3);
				{
				setState(127);
				((CalcContext)_localctx).var = match(VARIABLE);

				    ((CalcContext)_localctx).val =  (((CalcContext)_localctx).var!=null?((CalcContext)_localctx).var.getText():null);
				    _localctx.vars.add(_localctx.val);

				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class MathOpContext extends ParserRuleContext {
		public String op;
		public TerminalNode PLUS() { return getToken(PrefixParser.PLUS, 0); }
		public TerminalNode MINUS() { return getToken(PrefixParser.MINUS, 0); }
		public TerminalNode MUL() { return getToken(PrefixParser.MUL, 0); }
		public TerminalNode DIV() { return getToken(PrefixParser.DIV, 0); }
		public MathOpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_mathOp; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).enterMathOp(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrefixListener ) ((PrefixListener)listener).exitMathOp(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PrefixVisitor ) return ((PrefixVisitor<? extends T>)visitor).visitMathOp(this);
			else return visitor.visitChildren(this);
		}
	}

	public final MathOpContext mathOp() throws RecognitionException {
		MathOpContext _localctx = new MathOpContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_mathOp);
		try {
			setState(139);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case PLUS:
				enterOuterAlt(_localctx, 1);
				{
				setState(131);
				match(PLUS);
				((MathOpContext)_localctx).op =  "+";
				}
				break;
			case MINUS:
				enterOuterAlt(_localctx, 2);
				{
				setState(133);
				match(MINUS);
				((MathOpContext)_localctx).op =  "-";
				}
				break;
			case MUL:
				enterOuterAlt(_localctx, 3);
				{
				setState(135);
				match(MUL);
				((MathOpContext)_localctx).op =  "*";
				}
				break;
			case DIV:
				enterOuterAlt(_localctx, 4);
				{
				setState(137);
				match(DIV);
				((MathOpContext)_localctx).op =  "/";
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\30\u0090\4\2\t\2"+
		"\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\4\f\t\f\4\r\t\r\4\16\t\16\3\2\3\2\3\2\3\2\3\3\3\3\3\3\3\3\3\3\3"+
		"\3\3\3\3\3\3\3\3\3\3\3\3\3\5\3-\n\3\3\4\3\4\3\4\3\4\3\4\3\5\3\5\3\5\3"+
		"\5\3\5\3\5\3\6\3\6\3\6\3\6\5\6>\n\6\3\7\3\7\3\7\3\7\3\b\3\b\3\b\3\b\3"+
		"\b\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3\t\5\tQ\n\t\3\n\3\n\3\n\3\n\3\n\3\n\3"+
		"\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\5\ne\n\n\3\13\3\13\3\13"+
		"\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\13\5\13s\n\13\3\f\3\f\3\f\3"+
		"\f\5\fy\n\f\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\5\r\u0084\n\r\3\16\3\16"+
		"\3\16\3\16\3\16\3\16\3\16\3\16\5\16\u008e\n\16\3\16\2\2\17\2\4\6\b\n\f"+
		"\16\20\22\24\26\30\32\2\2\2\u0097\2\34\3\2\2\2\4,\3\2\2\2\6.\3\2\2\2\b"+
		"\63\3\2\2\2\n=\3\2\2\2\f?\3\2\2\2\16C\3\2\2\2\20P\3\2\2\2\22d\3\2\2\2"+
		"\24r\3\2\2\2\26x\3\2\2\2\30\u0083\3\2\2\2\32\u008d\3\2\2\2\34\35\5\4\3"+
		"\2\35\36\7\2\2\3\36\37\b\2\1\2\37\3\3\2\2\2 !\5\b\5\2!\"\b\3\1\2\"-\3"+
		"\2\2\2#$\5\f\7\2$%\b\3\1\2%-\3\2\2\2&\'\5\16\b\2\'(\b\3\1\2(-\3\2\2\2"+
		")*\5\6\4\2*+\b\3\1\2+-\3\2\2\2, \3\2\2\2,#\3\2\2\2,&\3\2\2\2,)\3\2\2\2"+
		"-\5\3\2\2\2./\7\27\2\2/\60\5\22\n\2\60\61\5\4\3\2\61\62\b\4\1\2\62\7\3"+
		"\2\2\2\63\64\7\25\2\2\64\65\5\22\n\2\65\66\5\4\3\2\66\67\5\n\6\2\678\b"+
		"\5\1\28\t\3\2\2\29:\5\4\3\2:;\b\6\1\2;>\3\2\2\2<>\b\6\1\2=9\3\2\2\2=<"+
		"\3\2\2\2>\13\3\2\2\2?@\7\26\2\2@A\5\20\t\2AB\b\7\1\2B\r\3\2\2\2CD\7\t"+
		"\2\2DE\7\30\2\2EF\5\20\t\2FG\b\b\1\2G\17\3\2\2\2HI\7\30\2\2IQ\b\t\1\2"+
		"JK\5\30\r\2KL\b\t\1\2LQ\3\2\2\2MN\5\22\n\2NO\b\t\1\2OQ\3\2\2\2PH\3\2\2"+
		"\2PJ\3\2\2\2PM\3\2\2\2Q\21\3\2\2\2RS\5\24\13\2ST\5\30\r\2TU\5\30\r\2U"+
		"V\b\n\1\2Ve\3\2\2\2WX\7\22\2\2XY\5\22\n\2YZ\b\n\1\2Ze\3\2\2\2[\\\7\23"+
		"\2\2\\e\b\n\1\2]^\7\24\2\2^e\b\n\1\2_`\5\26\f\2`a\5\22\n\2ab\5\22\n\2"+
		"bc\b\n\1\2ce\3\2\2\2dR\3\2\2\2dW\3\2\2\2d[\3\2\2\2d]\3\2\2\2d_\3\2\2\2"+
		"e\23\3\2\2\2fg\7\n\2\2gs\b\13\1\2hi\7\13\2\2is\b\13\1\2jk\7\f\2\2ks\b"+
		"\13\1\2lm\7\r\2\2ms\b\13\1\2no\7\16\2\2os\b\13\1\2pq\7\17\2\2qs\b\13\1"+
		"\2rf\3\2\2\2rh\3\2\2\2rj\3\2\2\2rl\3\2\2\2rn\3\2\2\2rp\3\2\2\2s\25\3\2"+
		"\2\2tu\7\20\2\2uy\b\f\1\2vw\7\21\2\2wy\b\f\1\2xt\3\2\2\2xv\3\2\2\2y\27"+
		"\3\2\2\2z{\5\32\16\2{|\5\30\r\2|}\5\30\r\2}~\b\r\1\2~\u0084\3\2\2\2\177"+
		"\u0080\7\4\2\2\u0080\u0084\b\r\1\2\u0081\u0082\7\30\2\2\u0082\u0084\b"+
		"\r\1\2\u0083z\3\2\2\2\u0083\177\3\2\2\2\u0083\u0081\3\2\2\2\u0084\31\3"+
		"\2\2\2\u0085\u0086\7\5\2\2\u0086\u008e\b\16\1\2\u0087\u0088\7\6\2\2\u0088"+
		"\u008e\b\16\1\2\u0089\u008a\7\7\2\2\u008a\u008e\b\16\1\2\u008b\u008c\7"+
		"\b\2\2\u008c\u008e\b\16\1\2\u008d\u0085\3\2\2\2\u008d\u0087\3\2\2\2\u008d"+
		"\u0089\3\2\2\2\u008d\u008b\3\2\2\2\u008e\33\3\2\2\2\n,=Pdrx\u0083\u008d";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}