#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"

static int lbl;

int ex(nodeType *p) {
  int lbl1, lbl2;

  if (!p) return 0;
  switch(p->type) {
  case typeCon:       
    printf(""); 
    break;
  case typeFloat:
    printf("");
    break;
  case typeId:        
    printf(""); 
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
      printf("");
      break;
    case '=':       
      ex(p->opr.op[1]);
      printf("");
      break;
    case UMINUS:    
      ex(p->opr.op[0]);
      printf("");
      break;
    default:
      ex(p->opr.op[0]);
      ex(p->opr.op[1]);
      switch(p->opr.oper) {
      case '+':   printf(""); break;
      case '-':   printf(""); break; 
      case '*':   printf(""); break;
      case '/':   printf(""); break;
      case '<':   printf(""); break;
      case '>':   printf(""); break;
      case GE:    printf(""); break;
      case LE:    printf(""); break;
      case NE:    printf(""); break;
      case EQ:    printf(""); break;
      }
    }
  }
  return 0;
}
