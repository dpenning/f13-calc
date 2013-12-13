#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"
#include "symbol_table.h"

int ex(nodeType *p,int build) {
  if (!p) return 0;
  switch(p->type) {
  case typeCon:       return p->con.value;
  case typeFloat:     return p->fl.value;
  case typeId:
    if (getSymbolEntry(p->id.s)->type == TYPE_INT) 
      return getSymbolEntry(p->id.s)->iVal;
    printf("Float | ");
    return getSymbolEntry(p->id.s)->fVal;
  case typeOpr:
    switch(p->opr.oper) {
    case WHILE:     while(ex(p->opr.op[0],build)) ex(p->opr.op[1],build); return 0;
    case DO:        do {ex(p->opr.op[0],build);} while (ex(p->opr.op[1],build)); return 0;
    case REPEAT:    do {ex(p->opr.op[0],build);} while (!ex(p->opr.op[1],build)); return 0;
    case IF:        if (ex(p->opr.op[0],build))
              ex(p->opr.op[1],build);
            else if (p->opr.nops > 2)
              ex(p->opr.op[2],build);
            return 0;
    case PRINT:     
      printf("<Symbol Table>\n");
      printSymbolTable();
      printf("</Symbol Table>\n");
      printf("%d\n", ex(p->opr.op[0],build)); return 0;

    case ';':       ex(p->opr.op[0],build); return ex(p->opr.op[1],build);
    case '=':       return getSymbolEntry(p->opr.op[0]->id.s)->iVal = (int)ex(p->opr.op[1],build);
    case UMINUS:    return -ex(p->opr.op[0],build);
    case '+':       return ex(p->opr.op[0],build) + ex(p->opr.op[1],build);
    case '-':       return ex(p->opr.op[0],build) - ex(p->opr.op[1],build);
    case '*':       return ex(p->opr.op[0],build) * ex(p->opr.op[1],build);
    case '/':       return ex(p->opr.op[0],build) / ex(p->opr.op[1],build);
    case '<':       return ex(p->opr.op[0],build) < ex(p->opr.op[1],build);
    case '>':       return ex(p->opr.op[0],build) > ex(p->opr.op[1],build);
    case GE:        return ex(p->opr.op[0],build) >= ex(p->opr.op[1],build);
    case LE:        return ex(p->opr.op[0],build) <= ex(p->opr.op[1],build);
    case NE:        return ex(p->opr.op[0],build) != ex(p->opr.op[1],build);
    case EQ:        return ex(p->opr.op[0],build) == ex(p->opr.op[1],build);
    }
  }
  return 0;
}
