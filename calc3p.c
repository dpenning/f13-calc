#include <stdio.h>
#include "calc3.h"
#include "symbol_table.h"
#include "y.tab.h"

static int lbl;

int ex(nodeType *p,int build) {
  struct symbol_entry *sym;
  int start_location_loop;
  int end_location_loop;
  int if_true_location;
  int if_false_location;

  if (!p) return 0;

  if (build == 0) {
    switch(p->type) {
      case typeCon:
        lbl++;
        return TYPE_INT;
      case typeFloat:
        lbl++;
        return TYPE_FLOAT;
      case typeId:
        lbl++;
        return 0;
      case typeOpr:
        switch(p->opr.oper) {
          case WHILE:
            ex(p->opr.op[0],0);
            lbl++;
            ex(p->opr.op[1],0);
            lbl++;
            return 0;
          case DO:
            ex(p->opr.op[0],0);
            ex(p->opr.op[1],0);
            lbl++;
            return 0;
          case REPEAT:
            ex(p->opr.op[0],0);
            ex(p->opr.op[1],0);
            lbl++;
            return 0;
          case IF:
            ex(p->opr.op[0],0);
            lbl++;
            ex(p->opr.op[1],0);
            if (p->opr.nops > 2) {
              lbl++;
              ex(p->opr.op[2],0);
            }
            return 0;
          case PRINT:
            ex(p->opr.op[0],0);
            lbl++;
            return 0;
          case '=':
            ex(p->opr.op[1],0);
            lbl++;
            return 0;
          case UMINUS:
            ex(p->opr.op[0],0);
            lbl++;
            return 0;
          default:
            ex(p->opr.op[0],0);
            ex(p->opr.op[1],0);
            lbl++;
            return 0;
        }
    }
    return 0;
  }

  switch(p->type) {
    case typeCon:
      printf("%04d I_Constant value:%d\n", lbl++, p->con.value); 
      return TYPE_INT;
    case typeFloat:
      printf("%04d R_Constant value:%f\n", lbl++, p->fl.value); 
      return TYPE_FLOAT;
    case typeId:
      sym = getSymbolEntry(p->id.s);
      if (sym->type == TYPE_INT) {
        printf("%04d I_Variable lev:%d disp:%d\n"
             , lbl++
             , sym->blk_level
             , sym->offset); 
        return TYPE_INT;
      }
      else {
        printf("%04d R_Variable lev:%d disp:%d\n"
             , lbl++
             , sym->blk_level
             , sym->offset); 
        return TYPE_FLOAT;
      }
    case typeOpr:
      switch(p->opr.oper) {
      case WHILE:
        start_location_loop = lbl;
        ex(p->opr.op[0],0);
        lbl++;
        ex(p->opr.op[1],0);
        lbl++;
        end_location_loop = lbl;
        lbl = start_location_loop;
        ex(p->opr.op[0],1);
        printf("%04d Jmp_if_False %04d\n",lbl++,end_location_loop);
        ex(p->opr.op[1],1);
        printf("%04d Jmp %04d\n",lbl++,start_location_loop);
        return 0;
      case DO:
        start_location_loop = lbl;
        ex(p->opr.op[0],1);
        ex(p->opr.op[1],1);
        printf("%04d Jmp_if_True %04d\n",lbl++,start_location_loop);
        return 0;
      case REPEAT:
        start_location_loop = lbl;
        ex(p->opr.op[0],1);
        ex(p->opr.op[1],1);
        printf("%04d Jmp_if_False %04d\n",lbl++,start_location_loop);
        return 0;
      case IF:
        start_location_loop = lbl;
        ex(p->opr.op[0],0);
        lbl++;
        ex(p->opr.op[1],0);
        if (p->opr.nops > 2) {
          lbl++;
          if_false_location = lbl + 1;
          ex(p->opr.op[2],0);
          if_true_location = lbl + 1;
        }
        else {
          if_false_location = lbl + 1;
        }
        lbl = start_location_loop;
        ex(p->opr.op[0],1);
        printf("%04d Jmp_if_False %04d\n",lbl++,if_false_location);
        ex(p->opr.op[1],1);
        if (p->opr.nops > 2) {
          printf("%04d Jmp %04d\n",lbl++,if_true_location);
          ex(p->opr.op[2],1);
        }
        return 0;
      case PRINT:
        ex(p->opr.op[0],0);
        printf("%04d I_Write words:1\n", lbl++);
        return 0;
      case '=':
        ex(p->opr.op[1],1);
        printf("%04d I_Assign words:%d\n", lbl++, 1);
        return 0;
      case UMINUS:
        ex(p->opr.op[0],1);
        printf("%04d I_Minus", lbl++);
        break;
      default:
        ex(p->opr.op[0],1);
        ex(p->opr.op[1],1);
        switch(p->opr.oper) {
        case '+':   printf("%04d I_Add", lbl++); break;
        case '-':   printf("%04d I_Subtract", lbl++); break; 
        case '*':   printf("%04d I_Multiply", lbl++); break;
        case '/':   printf("%04d I_Divide", lbl++); break;
        case '<':   printf("%04d I_Less", lbl++); break;
        case '>':   printf("%04d I_Greater", lbl++); break;
        case EQ:    printf("%04d I_Equal", lbl++); break;
        case NE:
          printf("%04d I_Equal", lbl++);
          printf("%04d I_Constant value:0", lbl++);
          printf("%04d I_Equal", lbl++);
          break;
        case GE:
          printf("%04d I_Less", lbl++);
          printf("%04d I_Constant value:0", lbl++);
          printf("%04d I_Equal", lbl++);
          break;
        case LE:
          printf("%04d I_Greater", lbl++);
          printf("%04d I_Constant value:0", lbl++);
          printf("%04d I_Equal", lbl++);
          break;
        }
      }
  }
  printf("\n");
  return 0;
}
