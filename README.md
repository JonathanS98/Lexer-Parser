Grammar

 ```
/*
<MATCH> -> <EXPR>
<EXPR> -> <LETTER> | <GROUP>
<LETTER> -> <MANY> | <DOT> | <OR> | <CHAR>
<GROUP> -> (<LETTER>) | (<LETTER>'+'<LETTER>)
<MANY> -> <CHAR><MANY>
<DOT> -> <DOT>{<CHAR>} | <DOT><MANY>
<OR> -> <CHAR> "+" <CHAR>
 */
 ```
