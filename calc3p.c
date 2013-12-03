#include <stdio.h>
#include "calc3.h"
#include "symbol_table.h"
#include "y.tab.h"

static int lbl;

int ex(nodeType *p) {
  struct symbol_entry *sym;
  if (!p) return 0;
  switch(p->type) {
  case typeCon:       
    printf("%04d I_CONSTANT value:%d", lbl++, p->con.value); 
    break;
  case typeFloat:
    printf("%04d R_CONSTANT value:%f", lbl++, p->fl.value); 
    break;
  case typeId:
    sym = getSymbolEntry(p->id.s);    
    printf("%04d I_VARIABLE lev:%d disp:%d"
           , lbl++
           , sym->blk_level
           , sym->offset); 
    break;
  case typeOpr:
    switch(p->opr.oper) {
    case WHILE:
      printf("");
      ex(p->opr.op[0]);
      printf("");
      ex(p->opr.op[1]);
      printf("");
      printf("");
      break;
    case DO:
      printf("");
      ex(p->opr.op[0]);
      ex(p->opr.op[1]);
      printf("");
      printf("");
      printf("");
      break;
    case REPEAT:
      printf("");
      ex(p->opr.op[0]);
      ex(p->opr.op[1]);
      printf("");
      break;
    case IF:
      ex(p->opr.op[0]);
      if (p->opr.nops > 2) {
        /* if else */
        printf("");
        ex(p->opr.op[1]);
        printf("");
        printf("");
        ex(p->opr.op[2]);
        printf("");
      } else {
        /* if */
        printf("");
        ex(p->opr.op[1]);
        printf("");
      }
      break;
    case PRINT:     
      ex(p->opr.op[0]);
      printf("%04d I_WRITE words:1", lbl++);
      break;
    case '=':
      /*This should be changed later to handle
       more than one assignment at a time.*/
      ex(p->opr.op[1]);
      printf("%04d I_ASSIGN words:%d", lbl++, 1);
      break;
    case UMINUS:    
      ex(p->opr.op[0]);
      printf("%04d I_MINUS", lbl++);
      break;
    default:
      ex(p->opr.op[0]);
      ex(p->opr.op[1]);
      switch(p->opr.oper) {
      case '+':   printf("%04d I_ADD", lbl++); break;
      case '-':   printf("%04d I_SUBTRACT", lbl++); break; 
      case '*':   printf("%04d I_MULTIPLY", lbl++); break;
      case '/':   printf("%04d I_DIVIDE", lbl++); break;
      case '<':   printf("%04d I_LESS", lbl++); break;
      case '>':   printf("%04d I_GREATER", lbl++); break;
      case EQ:    printf("%04d I_EQUAL", lbl++); break;
      case NE:
        printf("%04d I_EQUAL", lbl++);
        printf("%04d I_CONSTANT value:0", lbl++);
        printf("%04d I_EQUAL", lbl++);
        break;
      case GE:
        printf("%04d ", lbl++);
        break;
      case LE:
        printf("%04d ", lbl++);
        break;
      }
    }
  }
  printf("\n");
  return 0;
}
