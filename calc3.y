%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "calc3.h"

/* prototypes */
nodeType *opr(int oper, int nops, ...);
 nodeType *id(char* s);
nodeType *con(int value);
nodeType *conf(float value);
void freeNode(nodeType *p);
int ex(nodeType *p);
int yylex(void);

void yyerror(char *s);
int sym[26];                    /* symbol table */
%}

%union {
  int iValue;                 /* integer value */
  float fValue;
  char *sIndex;                /* symbol table index */
  nodeType *nPtr;             /* node pointer */
};

%token <iValue> INTEGER
%token <fValue> FLOAT
%token <sIndex> VARIABLE
%token WHILE IF PRINT DO UNTIL INTD FLOATD REPEAT
%nonassoc IFX
%nonassoc ELSE

%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <nPtr> stmt expr stmt_list decl

%%

program:
    function                { exit(0); }
    ;

function:
      function stmt         { ex($2); freeNode($2); }
    | /* NULL */
    ;

stmt:
      ';'                            { $$ = opr(';', 2, NULL, NULL); }
    | expr ';'                       { $$ = $1; }
    | PRINT expr ';'                 { $$ = opr(PRINT, 1, $2); }
    | decl VARIABLE ';'              { $$ = id($2); }

    // [TODO] - Change this back to just the function below
    //decl VARIABLE '=' expr ';'     { $$ = opr('=', 2, id($2), $4); }

    | decl VARIABLE '=' expr ';'     { printf("Variable Name = %s\n",$2);$$ = opr('=', 2, id($2), $4); }
    
    // [TODO] - Change this back to just the function below
    //VARIABLE '=' expr ';'          { $$ = opr('=', 2, id($1), $3); }
    | VARIABLE '=' expr ';'          { printf("Variable Name = %s\n",$1);$$ = opr('=', 2, id($1), $3); }
    
    | WHILE '(' expr ')' stmt        { $$ = opr(WHILE, 2, $3, $5); }
    | DO '{' stmt '}' WHILE '(' expr ')' ';' { }
    | REPEAT '{' stmt '}' UNTIL '(' expr ')' ';' { }
    | IF '(' expr ')' stmt %prec IFX { $$ = opr(IF, 2, $3, $5); }
    | IF '(' expr ')' stmt ELSE stmt { $$ = opr(IF, 3, $3, $5, $7); }
    | '{' stmt_list '}'              { $$ = $2; }
    ;

stmt_list:
      stmt                  { $$ = $1; }
    | stmt_list stmt        { $$ = opr(';', 2, $1, $2); }
    ;

expr:
      INTEGER               { $$ = con($1); }
    | FLOAT                 { $$ = conf($1); }
    | VARIABLE              { $$ = id($1); }
    | '-' expr %prec UMINUS { $$ = opr(UMINUS, 1, $2); }
    | expr '+' expr         { $$ = opr('+', 2, $1, $3); }
    | expr '-' expr         { $$ = opr('-', 2, $1, $3); }
    | expr '*' expr         { $$ = opr('*', 2, $1, $3); }
    | expr '/' expr         { $$ = opr('/', 2, $1, $3); }
    | expr '<' expr         { $$ = opr('<', 2, $1, $3); }
    | expr '>' expr         { $$ = opr('>', 2, $1, $3); }
    | expr GE expr          { $$ = opr(GE, 2, $1, $3); }
    | expr LE expr          { $$ = opr(LE, 2, $1, $3); }
    | expr NE expr          { $$ = opr(NE, 2, $1, $3); }
    | expr EQ expr          { $$ = opr(EQ, 2, $1, $3); }
    | '(' expr ')'          { $$ = $2; }
    ;

decl:
      INTD                  {}
    | FLOATD                {}

%%

#define SIZEOF_NODETYPE ((char *)&p->con - (char *)p)

nodeType *con(int value) {
  nodeType *p;
  size_t nodeSize;

  /* allocate node */
  nodeSize = SIZEOF_NODETYPE + sizeof(conNodeType);
  if ((p = malloc(nodeSize)) == NULL)
    yyerror("out of memory");

  /* copy information */
  p->type = typeCon;
  p->con.value = value;

  return p;
}

nodeType *conf(float value) {
  nodeType *p;
  size_t nodeSize;

  /* allocate node */
  nodeSize = SIZEOF_NODETYPE + sizeof(floatNodeType);
  if ((p = malloc(nodeSize)) == NULL)
    yyerror("out of memory");

  /* copy information */
  p->type = typeFloat;
  p->fl.value = value;

  return p;
}

nodeType *id(char* s) {
  nodeType *p;
  size_t nodeSize;

  /* allocate node */
  nodeSize = SIZEOF_NODETYPE + sizeof(idNodeType);
  if ((p = malloc(nodeSize)) == NULL)
    yyerror("out of memory");

  /* copy information */
  p->type = typeId;
  p->id.s = s;

  return p;
}

nodeType *opr(int oper, int nops, ...) {
  va_list ap;
  nodeType *p;
  size_t nodeSize;
  int i;

  /* allocate node */
  nodeSize = SIZEOF_NODETYPE + sizeof(oprNodeType) +
    (nops - 1) * sizeof(nodeType*);
  if ((p = malloc(nodeSize)) == NULL)
    yyerror("out of memory");

  /* copy information */
  p->type = typeOpr;
  p->opr.oper = oper;
  p->opr.nops = nops;
  va_start(ap, nops);
  for (i = 0; i < nops; i++)
    p->opr.op[i] = va_arg(ap, nodeType*);
  va_end(ap);
  return p;
}

void freeNode(nodeType *p) {
  int i;

  if (!p) return;
  if (p->type == typeOpr) {
    for (i = 0; i < p->opr.nops; i++)
      freeNode(p->opr.op[i]);
  }
  free (p);
}

void yyerror(char *s) {
  fprintf(stdout, "%s\n", s);
}

int main(void) {
  yyparse();
  return 0;
}
