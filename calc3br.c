#include <stdio.h>
#include "calc3.h"
#include "symbol_table.h"
#include "y.tab.h"

static int if_one_print_value = 0;

int ex(nodeType *p,int build) {
  struct symbol_entry *sym;
  int label_save;
  int start_location_loop;
  int end_location_loop;
  int if_true_location;
  int if_false_location;
  int operator_type_1;
  int operator_type_2;
  int last_if_one_print_value;


  if (!p) return 0;

  if (build == 0) {
    switch(p->type) {
      case typeCon:
        lbl += 2;
        return TYPE_INT;
      case typeFloat:
        lbl += 2;
        return TYPE_FLOAT;
      case typeId:
        sym = getSymbolEntry(p->id.s);
        if (sym->type == TYPE_INT) {
          lbl += 3;
          if (if_one_print_value == 1) {
            lbl++;
          }
          return TYPE_INT;
        }
        if (sym->type == TYPE_FLOAT) {
          lbl += 3;
          if (if_one_print_value == 1) {
            lbl++;
          }
          return TYPE_FLOAT;
        }
        return 0;
      case typeOpr:
        switch(p->opr.oper) {
          case BEG:
            pushSymbolTable();
            lbl += 3;
            lbl += 2;
            ex(p->opr.op[0],0);
            lbl++;
            popSymbolTable();
            return 0;
          case WHILE:
            ex(p->opr.op[0],0);
            lbl+=2;
            ex(p->opr.op[1],0);
            lbl+=2;
            return 0;
          case DO:
            start_location_loop = lbl;
            ex(p->opr.op[0],0);
            ex(p->opr.op[1],0);
            lbl += 2;
            return 0;
          case REPEAT:
            ex(p->opr.op[0],0);
            ex(p->opr.op[1],0);
            lbl += 2;
            return 0;
          case IF:
            ex(p->opr.op[0],0);
            lbl += 2;
            ex(p->opr.op[1],0);
            if (p->opr.nops > 2) {
              lbl += 2;
              ex(p->opr.op[2],0);
            }
            return 0;
          case PRINT:
            if_one_print_value = 1;
            operator_type_1 = ex(p->opr.op[0],0);
            if_one_print_value = 0;
            lbl += 2;
            return 0;
          case '=':
            operator_type_1 = ex(p->opr.op[0],0);
            if_one_print_value = 1;
            operator_type_2 = ex(p->opr.op[1],0);
            if_one_print_value = 0;
            if (operator_type_1 == TYPE_INT) {
              if (operator_type_2 == TYPE_INT) {
                lbl += 2;
                return TYPE_INT;
              }
            }
            if (operator_type_1 == TYPE_FLOAT) {
              if (operator_type_2 == TYPE_FLOAT) {
                lbl += 2;
                return TYPE_FLOAT;
              }
            }
            return 0;
          case UMINUS:
            last_if_one_print_value = if_one_print_value;
            if_one_print_value = 1;
            operator_type_1  = ex(p->opr.op[0],0);
            if_one_print_value = last_if_one_print_value;
            if (operator_type_1 == TYPE_INT) {
              lbl++;
              return TYPE_INT;
            }
            if (operator_type_1 == TYPE_FLOAT) {
              lbl++;
              return TYPE_FLOAT;
            }
            return 0;
          case ';':
            ex(p->opr.op[0],0);
            ex(p->opr.op[1],0);
            return 0;
          default:
            switch(p->opr.oper) {
              case '+':
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],0);
                operator_type_2 = ex(p->opr.op[1],0);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    lbl++;
                    return TYPE_INT;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    lbl++;
                    return TYPE_FLOAT;
                  }
                  return 0;
                }
                return 0;
              case '-':
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],0);
                operator_type_2 = ex(p->opr.op[1],0);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    lbl++;
                    return TYPE_INT;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    lbl++;
                    return TYPE_FLOAT;
                  }
                  return 0;
                }
                return 0;
              case '*':
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],0);
                operator_type_2 = ex(p->opr.op[1],0);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    lbl++;
                    return TYPE_INT;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    lbl++;
                    return TYPE_FLOAT;
                  }
                  return 0;
                }
                return 0;
              case '/':
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],0);
                operator_type_2 = ex(p->opr.op[1],0);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    lbl++;
                    return TYPE_INT;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    lbl++;
                    return TYPE_FLOAT;
                  }
                  return 0;
                }
                return 0;
              case '<':
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],0);
                operator_type_2 = ex(p->opr.op[1],0);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    lbl++;
                    return 0;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    lbl++;
                    return 0;
                  }
                  return 0;
                }
                return 0;
              case '>':
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],0);
                operator_type_2 = ex(p->opr.op[1],0);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    lbl++;
                    return 0;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    lbl++;
                    return 0;
                  }
                  return 0;
                }
                return 0;
              case EQ:
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],0);
                operator_type_2 = ex(p->opr.op[1],0);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    lbl++;
                    return 0;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    lbl++;
                    return 0;
                  }
                  return 0;
                }
                return 0;
              case NE:
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],1);
                operator_type_2 = ex(p->opr.op[1],1);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    lbl++;
                    lbl += 2;
                    lbl++;
                    return 0;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    lbl++;
                    lbl += 2;
                    lbl++;
                    return 0;
                  }
                  return 0;
                }
                return 0;
              case GE:
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],1);
                operator_type_2 = ex(p->opr.op[1],1);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    lbl++;
                    lbl += 2;
                    lbl++;
                    return 0;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    lbl++;
                    lbl += 2;
                    lbl++;
                    return 0;
                  }
                  return 0;
                }
                return 0;
              case LE:
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],1);
                operator_type_2 = ex(p->opr.op[1],1);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    lbl++;
                    lbl += 2;
                    lbl++;
                    return 0;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    lbl++;
                    lbl += 2;
                    lbl++;
                    return 0;
                  }
                  return 0;
                }
                return 0;
            }
        }
    }
    return 0;
  }
  if (build == 1) {
    switch(p->type) {
      case typeCon:
        printf("%04d I_Constant value:%d\n", lbl, p->con.value); 
        lbl += 2;
        return TYPE_INT;
      case typeFloat:
        printf("%04d R_Constant value:%f\n", lbl, p->fl.value); 
        lbl += 2;
        return TYPE_FLOAT;
      case typeId:
        sym = getSymbolEntry(p->id.s);
        if (sym->type == TYPE_INT) {
          printf("%04d I_Variable lev:%d disp:%d\n"
             , lbl
             , sym->blk_level
             , sym->offset); 
          lbl += 3;
          if (if_one_print_value == 1) {
            printf("%04d I_Value\n",lbl++);
          }
          return TYPE_INT;
        }
        if (sym->type == TYPE_FLOAT) {
          printf("%04d R_Variable lev:%d disp:%d\n"
             , lbl
             , sym->blk_level
             , sym->offset); 
          lbl += 3;
          if (if_one_print_value == 1) {
            printf("%04d R_Value\n",lbl++);
          }
          return TYPE_FLOAT;
        }
        return 0;
      case typeOpr:
        switch(p->opr.oper) {
          case BEG:
            pushSymbolTable();
            printf("%04d Call level:%d addr:%d\n",lbl,0,lbl + 5);
            lbl += 3;
            label_save = lbl; // jump label
            ex(p->opr.op[0],0);
            printf("%04d Jmp %d\n",label_save,lbl+4);
            lbl = label_save+2;
            printf("%04d Proc varlen:%d addr:%d\n",lbl,100,lbl+3);
            ex(p->opr.op[0],1);
            printf("%04d EndProc\n",lbl++);
            popSymbolTable(); // pop the last symbol table for scope
            return 0;
          case WHILE:
            start_location_loop = lbl;
            ex(p->opr.op[0],0);
            lbl+=2;
            ex(p->opr.op[1],0);
            lbl+=2;
            end_location_loop = lbl;
            lbl = start_location_loop;
            ex(p->opr.op[0],1);
            printf("%04d Jmp_if_False %04d\n",lbl,end_location_loop);
            lbl += 2;
            ex(p->opr.op[1],1);
            printf("%04d Jmp %04d\n",lbl,start_location_loop);
            lbl += 2;
            return 0;
          case DO:
            start_location_loop = lbl;
            ex(p->opr.op[0],1);
            ex(p->opr.op[1],1);
            printf("%04d Jmp_if_True %04d\n",lbl,start_location_loop);
            lbl += 2;
            return 0;
          case REPEAT:
            start_location_loop = lbl;
            ex(p->opr.op[0],1);
            ex(p->opr.op[1],1);
            printf("%04d Jmp_if_False %04d\n",lbl,start_location_loop);
            lbl += 2;
            return 0;
          case IF:
            start_location_loop = lbl;
            ex(p->opr.op[0],0);
            lbl+=2;
            ex(p->opr.op[1],0);
            if (p->opr.nops > 2) {
              lbl+=2;
              if_false_location = lbl + 1;
              ex(p->opr.op[2],0);
              if_true_location = lbl + 1;
            }
            else {
              if_false_location = lbl + 1;
            }
            lbl = start_location_loop;
            ex(p->opr.op[0],1);
            printf("%04d Jmp_if_False %04d\n",lbl,if_false_location);
            lbl += 2;
            ex(p->opr.op[1],1);
            if (p->opr.nops > 2) {
              printf("%04d Jmp %04d\n",lbl,if_true_location);
              lbl += 2;
              ex(p->opr.op[2],1);
            }
            return 0;
          case PRINT:
            if_one_print_value = 1;
            operator_type_1 = ex(p->opr.op[0],1);
            if_one_print_value = 0;
            printf("%04d I_Write words:1\n", lbl);
            lbl += 2;
            return 0;
          case '=':
            operator_type_1 = ex(p->opr.op[0],1);
            if_one_print_value = 1;
            operator_type_2 = ex(p->opr.op[1],1);
            if_one_print_value = 0;
            if (operator_type_1 == TYPE_INT) {
              if (operator_type_2 == TYPE_INT) {
                printf("%04d I_Assign words:%d\n", lbl, 1);
                lbl += 2;
                return TYPE_INT;
              }
            }
            if (operator_type_1 == TYPE_FLOAT) {
              if (operator_type_2 == TYPE_FLOAT) {
                printf("%04d R_Assign words:%d\n", lbl, 1);
                lbl += 2;
                return TYPE_FLOAT;
              }
            }
            return 0;
          case UMINUS:
            last_if_one_print_value = if_one_print_value;
            if_one_print_value = 1;
            operator_type_1  = ex(p->opr.op[0],1);
            if_one_print_value = last_if_one_print_value;
            if (operator_type_1 == TYPE_INT) {
              printf("%04d I_Minus\n", lbl++);
              return TYPE_INT;
            }
            if (operator_type_1 == TYPE_FLOAT) {
              printf("%04d R_Minus\n", lbl++);
              return TYPE_FLOAT;
            }
            return 0;
          case ';':
            ex(p->opr.op[0],1);
            ex(p->opr.op[1],1);
            return 0;
          default:
            switch(p->opr.oper) {
              case '+':
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],1);
                operator_type_2 = ex(p->opr.op[1],1);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    printf("%04d I_Add\n", lbl++);
                    return TYPE_INT;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    printf("%04d R_Add\n", lbl++);
                    return TYPE_FLOAT;
                  }
                  return 0;
                }
                return 0;
              case '-':
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],1);
                operator_type_2 = ex(p->opr.op[1],1);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    printf("%04d I_Sub\n", lbl++);
                    return TYPE_INT;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    printf("%04d R_Sub\n", lbl++);
                    return TYPE_FLOAT;
                  }
                  return 0;
                }
                return 0;
              case '*':
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],1);
                operator_type_2 = ex(p->opr.op[1],1);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    printf("%04d I_Multiply\n", lbl++);
                    return TYPE_INT;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    printf("%04d R_Multiply\n", lbl++);
                    return TYPE_FLOAT;
                  }
                  return 0;
                }
                return 0;
              case '/':
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],1);
                operator_type_2 = ex(p->opr.op[1],1);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    printf("%04d I_Divide\n", lbl++);
                    return TYPE_INT;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    printf("%04d R_Divide\n", lbl++);
                    return TYPE_FLOAT;
                  }
                  return 0;
                }
                return 0;
              case '<':
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],1);
                operator_type_2 = ex(p->opr.op[1],1);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    printf("%04d I_Less\n", lbl++);
                    return 0;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    printf("%04d R_Less\n", lbl++);
                    return 0;
                  }
                  return 0;
                }
                return 0;
              case '>':
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],1);
                operator_type_2 = ex(p->opr.op[1],1);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    printf("%04d I_Greater\n", lbl++);
                    return 0;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    printf("%04d R_Greater\n", lbl++);
                    return 0;
                  }
                  return 0;
                }
                return 0;
              case EQ:
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],1);
                operator_type_2 = ex(p->opr.op[1],1);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    printf("%04d I_Equal\n", lbl++);
                    return 0;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    printf("%04d R_Equal\n", lbl++);
                    return 0;
                  }
                  return 0;
                }
                return 0;
              case NE:
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],1);
                operator_type_2 = ex(p->opr.op[1],1);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    printf("%04d I_Equal\n", lbl++);
                    printf("%04d I_Constant value:0\n", lbl);
                    lbl += 2;
                    printf("%04d I_Equal\n", lbl++);
                    return 0;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    printf("%04d R_Equal\n", lbl++);
                    printf("%04d I_Constant value:0\n", lbl);
                    lbl += 2;
                    printf("%04d I_Equal\n", lbl++);
                    return 0;
                  }
                  return 0;
                }
                return 0;
              case GE:
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],1);
                operator_type_2 = ex(p->opr.op[1],1);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    printf("%04d I_Less\n", lbl++);
                    printf("%04d I_Constant value:0\n", lbl);
                    lbl += 2;
                    printf("%04d I_Equal\n", lbl++);
                    return 0;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    printf("%04d R_Less\n", lbl++);
                    printf("%04d I_Constant value:0\n", lbl);
                    lbl += 2;
                    printf("%04d I_Equal\n", lbl++);
                    return 0;
                  }
                  return 0;
                }
                return 0;
              case LE:
                last_if_one_print_value = if_one_print_value;
                if_one_print_value = 1;
                operator_type_1 = ex(p->opr.op[0],1);
                operator_type_2 = ex(p->opr.op[1],1);
                if_one_print_value = last_if_one_print_value;
                if (operator_type_1 == TYPE_INT) {
                  if (operator_type_2 == TYPE_INT) {
                    printf("%04d I_Greater\n", lbl++);
                    printf("%04d I_Constant value:0\n", lbl);
                    lbl += 2;
                    printf("%04d I_Equal\n", lbl++);
                    return 0;
                  }
                  return 0;
                }
                if (operator_type_1 == TYPE_FLOAT) {
                  if (operator_type_2 == TYPE_FLOAT) {
                    printf("%04d R_Greater\n", lbl++);
                    printf("%04d I_Constant value:0\n", lbl);
                    lbl += 2;
                    printf("%04d I_Equal\n", lbl++);
                    return 0;
                  }
                  return 0;
                }
                return 0;
            }
        }
    }
    return 0;
  }

  return 0;
}