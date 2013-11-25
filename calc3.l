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
"repeat"       { return REPEAT; }

[ \t\n]+        {printf("Whitespace\n");}       /* ignore whitespace */

[a-zA-Z_][a-zA-Z_0-9]*       {
        char *copy;
        printf("Variable\n");
        copy = strdup(yytext);
        yylval.sIndex = copy;
        printf("text of yytext - %s \n",yytext);
        printf("size of yytext - %lu \n",sizeof(*yytext));
        return VARIABLE;
      }
0           {
        printf("Integer\n");
        yylval.iValue = atoi(yytext);
        return INTEGER;
      }

[1-9][0-9]* {
        printf("Integer\n");
        yylval.iValue = atoi(yytext);
        return INTEGER;
      }

[0-9]*[.][0-9]* {
        printf("Float\n");
        yylval.fValue = atof(yytext);
        return FLOAT;
}

[-()<>=+*;/{}.] {
        printf("Text\n");
        return *yytext;
       }

.               yyerror("Unknown character");
%%
int yywrap(void) {
  return 1;
}
