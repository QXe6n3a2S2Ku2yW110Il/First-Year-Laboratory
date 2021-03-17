// Generated from /home/donaldo/Documents/MT/3/src/main/java/Prefix.g4 by ANTLR 4.9.1
package antlr;
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class PrefixLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.9.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		WHITESPACE=1, NUMBER=2, PLUS=3, MINUS=4, MUL=5, DIV=6, DEF=7, EQUALS=8, 
		NOT_EQUAL=9, LESS=10, LESS_EQUAL=11, GREATER=12, GREATER_EQUAL=13, AND=14, 
		OR=15, NOT=16, TRUE=17, FALSE=18, IF=19, PRINT=20, WHILE=21, VARIABLE=22;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"WHITESPACE", "DIGIT", "NUMBER", "PLUS", "MINUS", "MUL", "DIV", "DEF", 
			"EQUALS", "NOT_EQUAL", "LESS", "LESS_EQUAL", "GREATER", "GREATER_EQUAL", 
			"AND", "OR", "NOT", "TRUE", "FALSE", "IF", "PRINT", "WHILE", "LETTER", 
			"VARIABLE"
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


	public PrefixLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "Prefix.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\30\u009a\b\1\4\2"+
		"\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4"+
		"\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22"+
		"\t\22\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31"+
		"\t\31\3\2\6\2\65\n\2\r\2\16\2\66\3\2\3\2\3\3\3\3\3\4\5\4>\n\4\3\4\3\4"+
		"\7\4B\n\4\f\4\16\4E\13\4\3\4\5\4H\n\4\3\4\3\4\6\4L\n\4\r\4\16\4M\5\4P"+
		"\n\4\3\5\3\5\3\6\3\6\3\7\3\7\3\b\3\b\3\t\3\t\3\n\3\n\3\n\3\13\3\13\3\13"+
		"\3\f\3\f\3\r\3\r\3\r\3\16\3\16\3\17\3\17\3\17\3\20\3\20\3\20\3\20\3\21"+
		"\3\21\3\21\3\22\3\22\3\22\3\22\3\23\3\23\3\23\3\23\3\23\3\24\3\24\3\24"+
		"\3\24\3\24\3\24\3\25\3\25\3\25\3\26\3\26\3\26\3\26\3\26\3\26\3\27\3\27"+
		"\3\27\3\27\3\27\3\27\3\30\3\30\3\31\3\31\3\31\7\31\u0096\n\31\f\31\16"+
		"\31\u0099\13\31\2\2\32\3\3\5\2\7\4\t\5\13\6\r\7\17\b\21\t\23\n\25\13\27"+
		"\f\31\r\33\16\35\17\37\20!\21#\22%\23\'\24)\25+\26-\27/\2\61\30\3\2\6"+
		"\5\2\13\f\17\17\"\"\3\2\62;\3\2\63;\5\2C\\aac|\2\u009f\2\3\3\2\2\2\2\7"+
		"\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2"+
		"\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\2"+
		"\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3\2\2\2\2\'\3\2\2\2"+
		"\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2\61\3\2\2\2\3\64\3\2\2\2\5:\3\2\2\2"+
		"\7G\3\2\2\2\tQ\3\2\2\2\13S\3\2\2\2\rU\3\2\2\2\17W\3\2\2\2\21Y\3\2\2\2"+
		"\23[\3\2\2\2\25^\3\2\2\2\27a\3\2\2\2\31c\3\2\2\2\33f\3\2\2\2\35h\3\2\2"+
		"\2\37k\3\2\2\2!o\3\2\2\2#r\3\2\2\2%v\3\2\2\2\'{\3\2\2\2)\u0081\3\2\2\2"+
		"+\u0084\3\2\2\2-\u008a\3\2\2\2/\u0090\3\2\2\2\61\u0092\3\2\2\2\63\65\t"+
		"\2\2\2\64\63\3\2\2\2\65\66\3\2\2\2\66\64\3\2\2\2\66\67\3\2\2\2\678\3\2"+
		"\2\289\b\2\2\29\4\3\2\2\2:;\t\3\2\2;\6\3\2\2\2<>\7/\2\2=<\3\2\2\2=>\3"+
		"\2\2\2>?\3\2\2\2?C\t\4\2\2@B\5\5\3\2A@\3\2\2\2BE\3\2\2\2CA\3\2\2\2CD\3"+
		"\2\2\2DH\3\2\2\2EC\3\2\2\2FH\7\62\2\2G=\3\2\2\2GF\3\2\2\2HO\3\2\2\2IK"+
		"\7\60\2\2JL\5\5\3\2KJ\3\2\2\2LM\3\2\2\2MK\3\2\2\2MN\3\2\2\2NP\3\2\2\2"+
		"OI\3\2\2\2OP\3\2\2\2P\b\3\2\2\2QR\7-\2\2R\n\3\2\2\2ST\7/\2\2T\f\3\2\2"+
		"\2UV\7,\2\2V\16\3\2\2\2WX\7\61\2\2X\20\3\2\2\2YZ\7?\2\2Z\22\3\2\2\2[\\"+
		"\7?\2\2\\]\7?\2\2]\24\3\2\2\2^_\7#\2\2_`\7?\2\2`\26\3\2\2\2ab\7>\2\2b"+
		"\30\3\2\2\2cd\7>\2\2de\7?\2\2e\32\3\2\2\2fg\7@\2\2g\34\3\2\2\2hi\7@\2"+
		"\2ij\7?\2\2j\36\3\2\2\2kl\7c\2\2lm\7p\2\2mn\7f\2\2n \3\2\2\2op\7q\2\2"+
		"pq\7t\2\2q\"\3\2\2\2rs\7p\2\2st\7q\2\2tu\7v\2\2u$\3\2\2\2vw\7v\2\2wx\7"+
		"t\2\2xy\7w\2\2yz\7g\2\2z&\3\2\2\2{|\7h\2\2|}\7c\2\2}~\7n\2\2~\177\7u\2"+
		"\2\177\u0080\7g\2\2\u0080(\3\2\2\2\u0081\u0082\7k\2\2\u0082\u0083\7h\2"+
		"\2\u0083*\3\2\2\2\u0084\u0085\7r\2\2\u0085\u0086\7t\2\2\u0086\u0087\7"+
		"k\2\2\u0087\u0088\7p\2\2\u0088\u0089\7v\2\2\u0089,\3\2\2\2\u008a\u008b"+
		"\7y\2\2\u008b\u008c\7j\2\2\u008c\u008d\7k\2\2\u008d\u008e\7n\2\2\u008e"+
		"\u008f\7g\2\2\u008f.\3\2\2\2\u0090\u0091\t\5\2\2\u0091\60\3\2\2\2\u0092"+
		"\u0097\5/\30\2\u0093\u0096\5/\30\2\u0094\u0096\5\5\3\2\u0095\u0093\3\2"+
		"\2\2\u0095\u0094\3\2\2\2\u0096\u0099\3\2\2\2\u0097\u0095\3\2\2\2\u0097"+
		"\u0098\3\2\2\2\u0098\62\3\2\2\2\u0099\u0097\3\2\2\2\13\2\66=CGMO\u0095"+
		"\u0097\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}