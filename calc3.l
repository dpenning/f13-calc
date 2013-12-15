%{
#include <stdlib.h>
#include "calc3.h"
#include "y.tab.h"
#include "symbol_table.h"
void yyerror(char *);
%}

%%

">="           { return GE;     }
"<="           { return LE;     }
"=="           { return EQ;     }
"!="           { return NE;     }
"while"        { return WHILE;  }
"if"           { return IF;     }
"else"         { return ELSE;   }
"print"        { return PRINT;  }
"int"          { return INTD;   }
"float"        { return FLOATD; }
"do"           { return DO;     }
"until"        { return UNTIL;  }
"repeat"       { return REPEAT; }

"begin"        { pushSymbolTable();return BEG;}
"end"          {return END;}

[ \t\n]+       {}       /* ignore whitespace */

[a-zA-Z_][a-zA-Z_0-9]*       {
        char *copy;
        copy = strdup(yytext);
        yylval.sIndex = copy;
        return VARIABLE;
      }
0           {
        yylval.iValue = atoi(yytext);
        return INTEGER;
      }

[1-9][0-9]* {
        yylval.iValue = atoi(yytext);
        return INTEGER;
      }

[0-9]*[.][0-9]* {
        yylval.fValue = atof(yytext);
        return FLOAT;
}

"//".* {

}

"/*".*"*/" {

}

[-()<>=+/.*{}] {
        return *yytext;
       }

";" {
        line++;
        return *yytext;
    }

.               yyerror("Unknown character");
%%
int yywrap(void) {
  return 1;
}
