 # Parsing grammar
 
* `start` is an only start parser rule
* synthesized attributes can be used if following parser rule has corresponding attribute
* one parser rule can hold 1..* synthesized and inherited attributes
* parser rule starts with lower case letter
* lexer rule starts with upper case letter
* non-terminals has not any attributes
* generator doesn't generate parser if grammar is not LL(1)
* num is counted from 0
  ```
  rule (inherited attributes) [synthesized attributes] : next (attributes expression to inherit) NEXT next2 (...) {
      ${synthesized attribute name} ...
      ${num}.{synthesized attribute name} ...
  }
  
  RULE : "rule"
  RULE2 : [\s]*[\S]+[\s]*
  ```

# Example

CF Grammar
```
D -> TL
T -> int | real
L -> L, id | id
```

Parser Grammar 1
```
start () [] : t () l ()
t () [] : INT | REAL
l () [] : l () COMMA ID | ID

INT : "int"
REAL : "real"
ID : [a-zA-Z]+
COMMA : ","
```

Parser Grammar 2 (with the left recursion)
```
start () [String s] : t () l () {
    $s = %0.s + " " + $1.s;
}

t () [String s] : INT {
    $s = "int";
} REAL {
    $s = "real";
}

l () [String s] : l () COMMA ID {
    $s = $0.s + ", " + $2.node;
} ID {
    $s = $0.node;
}

INT : "int"
REAL : "real"
ID : [a-zA-Z]+
COMMA : ","
```

Parser Grammar 3 (LL(1), initializing with 0)
```
start () [String s] : t () l () {
    $s = $0.s + " " + $1.s + ";";
}

t () [String s] : INT {
    $s = "int";
} REAL {
    $s = "real";
}

l () [String s] : ID l1 ($0.node + " = 0") {
    $s = $1.s;
}

l1 (String acc) [String s] : COMMA ID l1 (acc + ", " + $1.node + " = 0") {
    $s = $2.s;
} EPS {
    $s = acc;
}

INT : "int"
REAL : "real"
ID : [a-zA-Z]+
COMMA : ","
```