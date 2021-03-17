grammar Generator;

gram: start grRule+ EOF;

start: '!' PARSE_NAME ';';

grRule: parseRule ';' | lexerRule ';';

parseRule: PARSE_NAME attrs? ('returns' attrs)? ':' nextRules;
attrs: '[' param (',' param)* ']';
param: paramType paramName;
paramType: CLASS_NAME;
paramName: VAR_NAME;
nextRules: nextRule ('|' nextRule)*;
nextRule: (QUOTE1 | PARSE_NAME)+ code?;
code: CODE;

lexerRule: LEXER_NAME ':' term_value;
term_value: QUOTE1;

fragment LETTER: [a-zA-Z0-9];
LEXER_NAME: [A-Z] [A-Z_]*;
PARSE_NAME: [a-z] LETTER*;
CLASS_NAME: [A-Z] LETTER*;
VAR_NAME: [a-zA-Z_] [a-zA-Z0-9_]*;

QUOTE1: '\'' (~('\'') | '\\\'')* '\'';
QUOTE2: '"' (~('"') | '\\"')* '"';
CODE: '{' (~[{}]+ CODE?)* '}' ;

WHITESPACE  : [ \t\r\n]+ -> skip;