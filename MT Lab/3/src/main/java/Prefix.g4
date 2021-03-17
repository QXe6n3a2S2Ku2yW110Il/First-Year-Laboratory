grammar Prefix;

@parser::header {
    import java.util.Set;
    import java.util.HashSet;
}

program returns[String val] locals [String global]: ex=expr[1] EOF {
    // System.out.println("in program $ex.vars is " + ($ex.vars == null ? "null" : $ex.vars));
    $global = $ex.vars.isEmpty() ? "" : "int " + String.join(" = 0, ", $ex.vars) + " = 0;\n\n";
    $val = String.format("#include <iostream>\n\n%sint main() {\n%s\n\treturn 0;\n}", $global, $ex.val);
};

expr[int tab] returns[String val, Set<String> vars] @init {$vars = new HashSet<>();}:
ex=ifBody[tab] {
    $val = $ex.val;
    $vars = $ex.vars;
} | pr=print[tab] {
    $val = $pr.val + "\n";
    $vars.addAll($pr.vars);
} | ass=assign[tab] {
    $val = $ass.val + "\n";
    $vars = $ass.vars;
    // System.out.println("vars now " + $vars);
} | wh = whileBody[tab] {
    $val = $wh.val + "\n";
    $vars = $wh.vars;
};

whileBody[int tab] returns[String val, Set<String> vars] @init {$vars = new HashSet<>();}:
WHILE l=logic ex=expr[tab + 1] {
    $val = String.format("%swhile (%s) {\n%s%s}", "\t".repeat($tab), $l.val, $ex.val, "\t".repeat($tab));
    $vars = $l.vars;
    $vars.addAll($ex.vars);
};

ifBody[int tab] returns[String val, Set<String> vars]: IF l=logic ex=expr[tab + 1] el=elseBody[tab] {
    $val = String.format("%sif (%s) {\n%s%s}%s\n", "\t".repeat($tab), $l.val, $ex.val, "\t".repeat($tab), $el.val);
    $vars = $l.vars;
    $vars.addAll($ex.vars);
    $vars.addAll($el.vars);
};

elseBody[int tab] returns[String val, Set<String> vars]:
ex=expr[tab + 1] {
    $val = String.format(" else {\n%s%s}", $ex.val, "\t".repeat($tab));
    $vars = $ex.vars;
} | {
    $val = "";
    $vars = new HashSet<>();
};

print[int tab] returns[String val, Set<String> vars]: PRINT v=rvalue {
    $val = String.format("%sstd::cout << %s << '\\n';", "\t".repeat($tab), $v.val);
    $vars = $v.vars;
    // System.out.println("print: " + $val + ", vars = " + $vars);
};

assign[int tab] returns[String val, Set<String> vars] @init {$vars = new HashSet<>();}: DEF var=VARIABLE v=rvalue {
    $val = String.format("%s%s = %s;", "\t".repeat($tab), $var.text, $v.val);
    $vars.add($var.text);
    $vars.addAll($v.vars);
    // System.out.println("assign: " + $val + ", vars = " + $vars);
};

rvalue returns[String val, Set<String> vars] @init {$vars = new HashSet<>();} @after {/* System.out.println("rvalue = " + $val + ", vars = " + $vars);*/}:
var=VARIABLE {
    $val = $var.text;
    $vars.add($val);
    // System.out.println("rvalue var!");
} | num=calc {
    $val = $num.val;
    $vars = $num.vars;
    // System.out.println("rvalue calc!");
} | l=logic {
    $val = $l.val;
    $vars = $l.vars;
    // System.out.println("rvalue logic!");
};

logic returns[String val, Set<String> vars] @init {$vars = new HashSet<>();}:
op=cmpOp v1=calc v2=calc {
    $val = String.format("%s %s %s", $v1.val, $op.op, $v2.val);
    $vars.addAll($v1.vars);
    $vars.addAll($v2.vars);
}| NOT l=logic {
    $val = String.format("!(%s)", $l.val);
    $vars = $l.vars;
} | TRUE {$val = "true";}
| FALSE {$val = "false";}
| op_=logicOp x1=logic x2=logic {
    $val = String.format("(%s %s %s)", $x1.val, $op_.op, $x2.val);
    $vars.addAll($x1.vars);
    $vars.addAll($x2.vars);
};

cmpOp returns[String op]: EQUALS {$op = "==";}
                          | NOT_EQUAL {$op = "!=";}
                          | LESS {$op = "<";}
                          | LESS_EQUAL {$op = "<=";}
                          | GREATER {$op = ">";}
                          | GREATER_EQUAL {$op = ">=";};

logicOp returns[String op]: AND {$op = "&&";}
                            | OR {$op = "||";};

calc returns[String val, Set<String> vars] @init {$vars = new HashSet<>();}:
op=mathOp v1=calc v2=calc {
    $val = String.format("(%s %s %s)", $v1.val, $op.op, $v2.val);
    $vars.addAll($v1.vars);
    $vars.addAll($v2.vars);
}| num=NUMBER {$val = $num.text;}
| var=VARIABLE {
    $val = $var.text;
    $vars.add($val);
};

mathOp returns[String op]: PLUS {$op = "+";}
                           | MINUS {$op = "-";}
                           | MUL {$op = "*";}
                           | DIV {$op = "/";};

WHITESPACE: [ \t\r\n]+ -> skip;
fragment DIGIT: [0-9];
NUMBER: (('-'? [1-9] DIGIT*) | '0') ('.' DIGIT+)?;

PLUS: '+';
MINUS: '-';
MUL: '*';
DIV: '/';

DEF: '=';

EQUALS: '==';
NOT_EQUAL: '!=';
LESS: '<';
LESS_EQUAL: '<=';
GREATER: '>';
GREATER_EQUAL: '>=';

AND: 'and';
OR: 'or';
NOT: 'not';
TRUE: 'true';
FALSE: 'false';

IF: 'if';
PRINT: 'print';
WHILE: 'while';

fragment LETTER: [a-zA-Z_];
VARIABLE: LETTER (LETTER | DIGIT)*;
