#include <stdio.h>
#include "calc3.h"
#include "symbol_table.h"
#include "y.tab.h"

/** declaration function helpers
 * declare flag tells us when we can make a variable
 */
int declare_flag = 0;
int assign_flag = 0;
int decl_type = 0;

/** scoping function helpers
 * scope variables is variables in scope
 * no_inner_scopes is a flag that says whether to dive in build == 0
 */
int scope_variables = 0;
int no_inner_scopes = 0;

/** variable helpers, this just tells us if we want to return the value
 * return value is a variable that defines if we print out I_value or F_value
 */
int output_value = 0;

int ex(nodeType *p, int build) {
  struct symbol_entry *sym;
  int operator_type_1;
  int operator_type_2;
  int label_save;
  int label_save_2;
  int if_false_location;
  int if_true_location;
  int last_id_output_value;

  if (build == 0) {
    switch(p->type) {
      case typeCon:
        lbl += 2;
        return TYPE_INT;
      case typeFloat:
        lbl += 2;
        return TYPE_FLOAT;
      case typeId:
        if (declare_flag == 1) {
          scope_variables += 1;
        }
        if (assign_flag == 1) {
          lbl += 3; return TYPE_INT;
        }
        if (output_value == 1) {
          lbl += 4; return TYPE_INT;
        }
        return 0;
      case typeOpr:
        switch(p->opr.oper) {
          // all of the cases we need to meet
          case PROG_BEGIN:
            //NOTHING
            return 0;
          case FUNC:
            ex(p->opr.op[0],0);
            ex(p->opr.op[1],0);
            return 0;
          case INT_DECL:
            declare_flag = 1;
            ex(p->opr.op[0],0);
            declare_flag = 0;
            return 0;
          case FLOAT_DECL:
            declare_flag = 1;
            ex(p->opr.op[0],0);
            declare_flag = 0;
            return 0;
          case LIST:
            if (declare_flag == 1){
              ex(p->opr.op[0],0);
              ex(p->opr.op[1],0);
            }
            return 0;
          case LIST_END:
            if (declare_flag == 1){
              ex(p->opr.op[0],0);
            }
            return 0;
          case INT_ASSIGN:
            declare_flag = 1;
            assign_flag = 1;
            ex(p->opr.op[0],0);
            assign_flag = 0;
            declare_flag = 0;
            operator_type_1 = ex(p->opr.op[1],0);
            if (operator_type_1 == TYPE_INT) {
              lbl += 2;
            }else{yyerror("Bad Assignment on line %d",line);}
            return 0;
          case FLOAT_ASSIGN:
            declare_flag = 1;
            assign_flag = 1;
            ex(p->opr.op[0],0);
            assign_flag = 0;
            declare_flag = 0;
            operator_type_1 = ex(p->opr.op[1],0);
            if (operator_type_1 == TYPE_FLOAT) {
              lbl += 2;
            }else{yyerror("Bad Assignment on line %d",line);}
            return 0;
          case BEG:
            if (no_inner_scopes == 1) {return 0;}
            pushSymbolTable();
            lbl += 3;
            lbl += 2;
            lbl += 3;
            ex(p->opr.op[0],0);
            lbl++;
            popSymbolTable();
            return 0;
          case PRINT:
            output_value = 1;
            ex(p->opr.op[0],0);
            output_value = 0;
            lbl += 2;
            return 0;
          case WHILE:
            ex(p->opr.op[0],0);
            lbl+=2;
            ex(p->opr.op[1],0);
            lbl+=2;
            return 0;
          case DO:
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
            lbl = if_false_location;
            return 0;
          case UMINUS:
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1  = ex(p->opr.op[0],0);
            output_value = last_id_output_value;
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
          case '=':
            assign_flag = 1;
            operator_type_1 = ex(p->opr.op[0],0);
            assign_flag = 0;

            output_value = 1;
            operator_type_2 = ex(p->opr.op[1],0);
            output_value = 0;

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
          case '+':
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],0);
            operator_type_2 = ex(p->opr.op[1],0);
            output_value = last_id_output_value;
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
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],0);
            operator_type_2 = ex(p->opr.op[1],0);
            output_value = last_id_output_value;
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
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],0);
            operator_type_2 = ex(p->opr.op[1],0);
            output_value = last_id_output_value;
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
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],0);
            operator_type_2 = ex(p->opr.op[1],0);
            output_value = last_id_output_value;
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
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],0);
            operator_type_2 = ex(p->opr.op[1],0);
            output_value = last_id_output_value;
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
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],0);
            operator_type_2 = ex(p->opr.op[1],0);
            output_value = last_id_output_value;
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
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],0);
            operator_type_2 = ex(p->opr.op[1],0);
            output_value = last_id_output_value;
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
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],0);
            operator_type_2 = ex(p->opr.op[1],0);
            output_value = last_id_output_value;
            if (operator_type_1 == TYPE_INT) {
              if (operator_type_2 == TYPE_INT) {
                lbl+=4;
                return 0;
              }
              return 0;
            }
            if (operator_type_1 == TYPE_FLOAT) {
              if (operator_type_2 == TYPE_FLOAT) {
                lbl+=4;
                return 0;
              }
              return 0;
            }
            return 0;
          case GE:
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],0);
            operator_type_2 = ex(p->opr.op[1],0);
            output_value = last_id_output_value;
            if (operator_type_1 == TYPE_INT) {
              if (operator_type_2 == TYPE_INT) {
                lbl+=4;
                return 0;
              }
              return 0;
            }
            if (operator_type_1 == TYPE_FLOAT) {
              if (operator_type_2 == TYPE_FLOAT) {
                lbl+=4;
                return 0;
              }
              return 0;
            }
            return 0;
          case LE:
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],0);
            operator_type_2 = ex(p->opr.op[1],0);
            output_value = last_id_output_value;
            if (operator_type_1 == TYPE_INT) {
              if (operator_type_2 == TYPE_INT) {
                lbl+=4;
                return 0;
              }
              return 0;
            }
            if (operator_type_1 == TYPE_FLOAT) {
              if (operator_type_2 == TYPE_FLOAT) {
                lbl+=4;
                return 0;
              }
              return 0;
            }
            return 0;
        }
    }
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
        if (declare_flag == 1) {
          //add the symbol to the symbol table
          sym = malloc(sizeof(struct symbol_entry));
          sym->name = p->id.s;
          sym->type = decl_type;
          sym->size = 1;
          sym->blk_level = getCurrentLevel();
          addSymbol(sym, line);
        }
        if (assign_flag == 1) {
          sym = getSymbolEntry(p->id.s);
          if (sym->type == TYPE_INT) {
            printf("%04d I_Variable lev:%d disp:%d\n"
             , lbl
             , sym->blk_level
             , sym->offset); 
            lbl += 3;
            return TYPE_INT;
          }
          if (sym->type == TYPE_FLOAT) {
            printf("%04d R_Variable lev:%d disp:%d\n"
             , lbl
             , sym->blk_level
             , sym->offset); 
            lbl += 3;
            return TYPE_FLOAT;
          }
        }
        if (output_value == 1) {
          sym = getSymbolEntry(p->id.s);
          if (sym->type == TYPE_INT) {
            printf("%04d I_Variable lev:%d disp:%d\n"
             , lbl
             , sym->blk_level
             , sym->offset); 
            lbl += 3;
            printf("%04d I_Value\n",lbl++);
            return TYPE_INT;
          }
          if (sym->type == TYPE_FLOAT) {
            printf("%04d R_Variable lev:%d disp:%d\n"
             , lbl
             , sym->blk_level
             , sym->offset); 
            lbl += 3;
            printf("%04d R_Value\n",lbl++);
            return TYPE_FLOAT;
          }
        }
        return 0;
      case typeOpr:
        switch(p->opr.oper) {
          case PROG_BEGIN:
            pushSymbolTable();
            //calculate the number of scope variables
            scope_variables = 0;
            no_inner_scopes = 1;
            ex(p->opr.op[0],0);
            no_inner_scopes = 0;
            lbl = 1;
            printf("%04d Prog varlen:%d addr:%d\n",lbl,scope_variables,4);
            lbl += 3;
            //reset variables
            scope_variables = 0;
            no_inner_scopes = 0;
            ex(p->opr.op[0],1);
            //end the program
            printf("%04d EndProg\n",lbl);
            lbl += 1;

            return 0;
          case FUNC:
            ex(p->opr.op[0],1);
            ex(p->opr.op[1],1);
            return 0;
          case INT_DECL:
            //we dont actually need to print anything from this
            //we just need to turn on declarations
            declare_flag = 1;
            decl_type = TYPE_INT;
            ex(p->opr.op[0],1);
            declare_flag = 0;
            return 0;
          case FLOAT_DECL:
            //we dont actually need to print anything from this
            //we just need to turn on declarations
            declare_flag = 1;
            decl_type = TYPE_FLOAT;
            ex(p->opr.op[0],1);
            declare_flag = 0;
            return 0;
          case LIST:
            if (declare_flag == 1){
              ex(p->opr.op[1],1);
              ex(p->opr.op[0],1);
            }
            return 0;
          case LIST_END:
            if (declare_flag == 1){
              ex(p->opr.op[0],1);
            }
            return 0;
          case INT_ASSIGN:
            declare_flag = 1;
            assign_flag = 1;
            decl_type = TYPE_INT;
            ex(p->opr.op[0],1);
            assign_flag = 0;
            declare_flag = 0;
            operator_type_1 = ex(p->opr.op[1],1);
            if (operator_type_1 == TYPE_INT) {
              printf("%04d I_Assign words:%d\n", lbl, 1);
              lbl += 2;
            }else{yyerror("Bad Assignment on line %d",line);}
            return 0;
          case FLOAT_ASSIGN:
            declare_flag = 1;
            decl_type = TYPE_FLOAT;
            ex(p->opr.op[0],1);
            declare_flag = 0;
            operator_type_1 = ex(p->opr.op[1],1);
            if (operator_type_1 == TYPE_FLOAT) {
              printf("%04d I_Assign words:%d\n", lbl, 1);
              lbl += 2;
            }else{yyerror("Bad Assignment on line %d",line);}
            return 0;
          case BEG:
            pushSymbolTable();
            printf("%04d Call level:%d addr:%d\n",lbl,0,lbl + 5);
            lbl += 3;
            label_save = lbl; // jump label
            no_inner_scopes = 0; // jump into scopes
            ex(p->opr.op[0],0);
            no_inner_scopes = 0; // reset

            label_save_2 = lbl;
            scope_variables = 0; // grabe the variables from scope
            no_inner_scopes = 1; // jump into scopes
            ex(p->opr.op[0],0);
            no_inner_scopes = 0; // reset

            printf("%04d Jmp %d\n",label_save,label_save_2+6);
            lbl = label_save+2;
            printf("%04d Proc varlen:%d addr:%d\n",lbl,scope_variables,lbl+3);
            scope_variables = 0;
            label_save = 0;
            label_save_2 = 0;
            lbl += 3;
            ex(p->opr.op[0],1);
            printf("%04d EndProc\n",lbl++);
            popSymbolTable();
            return 0;
          case PRINT:
            output_value = 1;
            ex(p->opr.op[0],1);
            output_value = 0;
            printf("%04d I_Write words:1\n", lbl);
            lbl += 2;
            return 0;
          case WHILE:
            label_save = lbl;
            ex(p->opr.op[0],0);
            lbl+=2;
            ex(p->opr.op[1],0);
            lbl+=2;
            label_save_2 = lbl;
            lbl = label_save;
            ex(p->opr.op[0],1);
            printf("%04d Jmp_if_False %04d\n",lbl,label_save_2);
            lbl += 2;
            ex(p->opr.op[1],1);
            printf("%04d Jmp %04d\n",lbl,label_save);
            lbl += 2;
            return 0;
          case DO:
            label_save = lbl;
            ex(p->opr.op[0],1);
            ex(p->opr.op[1],1);
            printf("%04d Jmp_if_True %04d\n",lbl,label_save);
            lbl += 2;
            return 0;
          case REPEAT:
            label_save = lbl;
            ex(p->opr.op[0],1);
            ex(p->opr.op[1],1);
            printf("%04d Jmp_if_False %04d\n",lbl,label_save);
            lbl += 2;
            return 0;
          case IF:
            label_save = lbl;
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
            lbl = label_save;
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
          case UMINUS:
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1  = ex(p->opr.op[0],1);
            output_value = last_id_output_value;
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
          case '=':
            assign_flag = 1;
            operator_type_1 = ex(p->opr.op[0],1);
            assign_flag = 0;

            output_value = 1;
            operator_type_2 = ex(p->opr.op[1],1);
            output_value = 0;

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
          case '+':
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],1);
            operator_type_2 = ex(p->opr.op[1],1);
            output_value = last_id_output_value;
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
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],1);
            operator_type_2 = ex(p->opr.op[1],1);
            output_value = last_id_output_value;
            if (operator_type_1 == TYPE_INT) {
              if (operator_type_2 == TYPE_INT) {
                printf("%04d I_Subtract\n", lbl++);
                return TYPE_INT;
              }
              return 0;
            }
            if (operator_type_1 == TYPE_FLOAT) {
              if (operator_type_2 == TYPE_FLOAT) {
                printf("%04d R_Subtract\n", lbl++);
                return TYPE_FLOAT;
              }
              return 0;
            }
            return 0;
          case '*':
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],1);
            operator_type_2 = ex(p->opr.op[1],1);
            output_value = last_id_output_value;
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
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],1);
            operator_type_2 = ex(p->opr.op[1],1);
            output_value = last_id_output_value;
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
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],1);
            operator_type_2 = ex(p->opr.op[1],1);
            output_value = last_id_output_value;
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
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],1);
            operator_type_2 = ex(p->opr.op[1],1);
            output_value = last_id_output_value;
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
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],1);
            operator_type_2 = ex(p->opr.op[1],1);
            output_value = last_id_output_value;
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
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],1);
            operator_type_2 = ex(p->opr.op[1],1);
            output_value = last_id_output_value;
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
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],1);
            operator_type_2 = ex(p->opr.op[1],1);
            output_value = last_id_output_value;
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
            last_id_output_value = output_value;
            output_value = 1;
            operator_type_1 = ex(p->opr.op[0],1);
            operator_type_2 = ex(p->opr.op[1],1);
            output_value = last_id_output_value;
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


}