#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"

int ex(nodeType *p, int build) {
  int lbl1, lbl2;

  if (!p) return 0;
  switch(p->type) {
  case typeCon:       
    printf("\tpush\t%d\n", p->con.value); 
    break;
  case typeFloat:
    printf("\tpush\t%f\n", p->fl.value);
    break;
  case typeId:        
    printf("\tpush\t%s\n", p->id.s); 
    break;
  case typeOpr:
    switch(p->opr.oper) {
    case WHILE:
      printf("L%03d:\n", lbl1 = lbl++);
      ex(p->opr.op[0], build);
      printf("\tjz\tL%03d\n", lbl2 = lbl++);
      ex(p->opr.op[1], build);
      printf("\tjmp\tL%03d\n", lbl1);
      printf("L%03d:\n", lbl2);
      break;
    case DO:
      printf("L%03d:\n", lbl1 = lbl++);
      ex(p->opr.op[0], build);
      ex(p->opr.op[1], build);
      printf("\tjz\tL%03d\n", lbl2 = lbl++);
      printf("\tjmp\tL%03d\n", lbl1);
      printf("L%03d:\n", lbl2);
      break;
    case REPEAT:
      printf("L%03d:\n", lbl1 = lbl++);
      ex(p->opr.op[0], build);
      ex(p->opr.op[1], build);
      printf("\tjz\tL%03d\n", lbl1);
      break;
    case IF:
      ex(p->opr.op[0], build);
      if (p->opr.nops > 2) {
        /* if else */
        printf("\tjz\tL%03d\n", lbl1 = lbl++);
        ex(p->opr.op[1], build);
        printf("\tjmp\tL%03d\n", lbl2 = lbl++);
        printf("L%03d:\n", lbl1);
        ex(p->opr.op[2], build);
        printf("L%03d:\n", lbl2);
      } else {
        /* if */
        printf("\tjz\tL%03d\n", lbl1 = lbl++);
        ex(p->opr.op[1], build);
        printf("L%03d:\n", lbl1);
      }
      break;
    case PRINT:     
      ex(p->opr.op[0], build);
      printf("\tprint\n");
      break;
    case '=':       
      ex(p->opr.op[1], build);
      printf("\tpop\t%s\n", p->opr.op[0]->id.s);
      break;
    case UMINUS:    
      ex(p->opr.op[0], build);
      printf("\tneg\n");
      break;
    default:
      ex(p->opr.op[0], build);
      ex(p->opr.op[1], build);
      switch(p->opr.oper) {
      case '+':   printf("\tadd\n"); break;
      case '-':   printf("\tsub\n"); break; 
      case '*':   printf("\tmul\n"); break;
      case '/':   printf("\tdiv\n"); break;
      case '<':   printf("\tcompLT\n"); break;
      case '>':   printf("\tcompGT\n"); break;
      case GE:    printf("\tcompGE\n"); break;
      case LE:    printf("\tcompLE\n"); break;
      case NE:    printf("\tcompNE\n"); break;
      case EQ:    printf("\tcompEQ\n"); break;
      }
    }
  }
  return 0;
}
