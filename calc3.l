%{
#include <stdlib.h>
#include "calc3.h"
#include "y.tab.h"
#include "symbol_table.h"
void yyerror(char *);
int currently_block_commenting = 0;
%}

%%
[ \t\n]+       {}
"/*"     {currently_block_commenting = 1;}
"*/"    {if (currently_block_commenting == 1) currently_block_commenting = 0;}
"//".*         {}

">="           { if (currently_block_commenting == 0) return GE;     }
"<="           { if (currently_block_commenting == 0) return LE;     }
"=="           { if (currently_block_commenting == 0) return EQ;     }
"!="           { if (currently_block_commenting == 0) return NE;     }
"while"        { if (currently_block_commenting == 0) return WHILE;  }
"if"           { if (currently_block_commenting == 0) return IF;     }
"else"         { if (currently_block_commenting == 0) return ELSE;   }
"print"        { if (currently_block_commenting == 0) return PRINT;  }
"int"          { if (currently_block_commenting == 0) return INTD;   }
"float"        { if (currently_block_commenting == 0) return FLOATD; }
"do"           { if (currently_block_commenting == 0) return DO;     }
"until"        { if (currently_block_commenting == 0) return UNTIL;  }
"repeat"       { if (currently_block_commenting == 0) return REPEAT; }

"begin"        { if (currently_block_commenting == 0) return BEG;}
"end"          { if (currently_block_commenting == 0) return END;}

[a-zA-Z_][a-zA-Z_0-9]*       { if (currently_block_commenting == 0) {
        char *copy;
        copy = strdup(yytext);
        yylval.sIndex = copy;
        return VARIABLE;}
      }
0           { if (currently_block_commenting == 0) {
        yylval.iValue = atoi(yytext);
        return INTEGER;
      }}

[1-9][0-9]* { if (currently_block_commenting == 0) {
        yylval.iValue = atoi(yytext);
        return INTEGER;
      }}

[0-9]*[.][0-9]* { if (currently_block_commenting == 0) {
        yylval.fValue = atof(yytext);
        return FLOAT;
}}

[-()<>=+/.*{},] { if (currently_block_commenting == 0) {
        return *yytext;
       }}

";" { if (currently_block_commenting == 0) {
        line++;
        return *yytext;
    }}

.               {if (currently_block_commenting == 0) {
                  printf("%s\n",yytext);
                  yyerror("Unknown character");}}
%%
int yywrap(void) {
  return 1;
}
