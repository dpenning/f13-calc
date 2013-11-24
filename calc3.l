%{
#include <stdlib.h>
#include "calc3.h"
#include "y.tab.h"
void yyerror(char *);
%}

%%

">="           { return GE; }
"<="           { return LE; }
"=="           { return EQ; }
"!="           { return NE; }
"while"        { return WHILE; }
"if"           { return IF; }
"else"         { return ELSE; }
"print"        { return PRINT; }
"int"          { return INTD; }
"float"        { return FLOATD; }
"do"           { return DO; }
"until"        { return UNTIL; }

[-()<>=+*/;{}.] {
        return *yytext;
       }

[a-zA-z_][a-zA-z_0=9]*       { 
        yylval.sIndex = yytext;
        return VARIABLE;
      }

[0-9]*[.][0-9]* {
yylval.fValue = atof(yytext);
return FLOAT;
}

0           {
        yylval.iValue = atoi(yytext);
        return INTEGER;
      }

[1-9][0-9]* {
        yylval.iValue = atoi(yytext);
        return INTEGER;
      }


[ \t\n]+        ;       /* ignore whitespace */

.               yyerror("Unknown character");
%%
int yywrap(void) {
  return 1;
}
