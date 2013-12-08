
/*
Converted to C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pstcode.h"

void link(WORD w) {
  last->next = malloc(sizeof(struct code));
  last = last->next;
  last->data = w;
  last->next = NULL;
}

void add_int(int op) {
  WORD w;
  w.Integer = op;
  link(w);
}

void add_float(float op) {
  WORD w;
  w.Real = op;
  link(w);
}

void add_dup() {
  /* -- w */
  add_int(I_CONSTANT);
  add_int(ADDR_TEMP);
  /* -- addr_temp w*/
  add_int(I_SWAP);
  /* -- w addr_temp*/
  add_int(I_ASSIGN);
  add_int(1);
  add_int(I_CONSTANT);
  add_int(ADDR_TEMP);
  add_int(I_VALUE);
  /* -- w*/
  add_int(I_CONSTANT);
  add_int(ADDR_TEMP);
  add_int(I_VALUE);
  /* -- w w*/
}

void add_2dup() {
  /* -- w x  (want -- w x w x)*/
  add_int(I_CONSTANT);
  add_int(ADDR_TEMP);
  /* -- addr_temp w x*/
  add_int(I_SWAP);
  /* -- w addr_temp x*/
  add_int(I_ASSIGN);
  add_int(1);
  /* -- x*/
  add_int(I_CONSTANT);
  add_int(ADDR_TEMP2);
  /* -- addr_temp2 x*/
  add_int(I_SWAP);
  /* -- x addr_temp2*/
  add_int(I_ASSIGN);
  add_int(1);
  /* --*/
  add_int(I_CONSTANT);
  add_int(ADDR_TEMP2);
  /* -- addr_temp2*/
  add_int(I_VALUE);
  /* -- x*/
  add_int(I_CONSTANT);
  add_int(ADDR_TEMP);
  /* -- addr_temp x*/
  add_int(I_VALUE);
  /* -- w x*/
  add_int(I_CONSTANT);
  add_int(ADDR_TEMP2);
  /* -- addr_temp2 w x*/
  add_int(I_VALUE);
  /* -- x w x*/
  add_int(I_CONSTANT);
  add_int(ADDR_TEMP);
  /* -- addr_temp x w x*/
  add_int(I_VALUE);
  /* -- w x w x*/
}


void add_3pick() {
  /* -- w x y  (want -- y w x y)*/
  add_int(I_CONSTANT);
  add_int(ADDR_TEMP);
  /* -- addr_temp w x y*/
  add_int(I_SWAP);
  /* -- w addr_temp x y*/
  add_int(I_ASSIGN);
  add_int(1);
  /* -- x y*/
  add_int(I_CONSTANT);
  add_int(ADDR_TEMP2);
  /* -- addr_temp2 x y*/
  add_int(I_SWAP);
  /* -- x addr_temp2 y*/
  add_int(I_ASSIGN);
  add_int(1);
  /* -- y*/
  add_int(I_CONSTANT);
  add_int(ADDR_TEMP3);
  /* -- addr_temp3 y*/
  add_int(I_SWAP);
  /* -- y addr_temp3*/
  add_int(I_ASSIGN);
  add_int(1);
  /* --*/
  add_int(I_CONSTANT);
  add_int(ADDR_TEMP3);
  add_int(I_VALUE);
  /* -- y*/
  add_int(I_CONSTANT);
  add_int(ADDR_TEMP2);
  add_int(I_VALUE);
  /* -- x y*/
  add_int(I_CONSTANT);
  add_int(ADDR_TEMP);
  add_int(I_VALUE);
  /* -- w x y*/
  add_int(I_CONSTANT);
  add_int(ADDR_TEMP3);
  add_int(I_VALUE);
  /* -- y w x y*/
}

void begin_prog() {
  /* execution starts at address 1*/
  first = malloc(sizeof(struct code));
  first->next = NULL;
  last = first;
  first->data.Integer = 0;
  /*add_int(0);*/
  add_int(I_PROG);
  add_int(0); /* address 2 will be patched by end_prog()*/
  add_int(pos() + 1);
}


void end_prog(int varsize) /* modified jwj: add parameter */
{
  at(2)->Integer = varsize;  /* patch I_PROG's first parameter - added jwj*/
  add_int(I_ENDPROG);
}

void begin_proc() {  
  add_int(I_PROC);
  add_int(0);
  add_int(pos()+1);
}

void end_proc(int patch_loc, int varsize) {
  printf("patch_loc: %d varsize: %d\n", patch_loc, varsize);
  at(patch_loc)->Integer = varsize;
  add_int(I_ENDPROC);
}

int write(char* file, int binary) {
  struct code* it;

  FILE *str;
  str = fopen(file, "w");
  if(!str)
    return 1;

  for(it = first; it != NULL; it = it->next) {
    if(binary) {
      fwrite(&(it->data), sizeof(WORD), 1, str);
    } else {
      /* NOTE: ASCII format does not support floats!!*/
      fprintf(str, "%d\n", it->data.Integer);
    }
  }

  if(ferror(str)) {
    fclose(str);
    return 1;
  }
  fclose(str);
  return 0;
}

int pos() {
  int size = 0;
  struct code* position = first;
  while (position->next != NULL) {
    ++size;
    position = position->next;
  }
  return size;
}

WORD* at(int p) {
  struct code* position = first;
  while (p) {
    --p;
    position = position->next;
  }
  return &(position->data);
}

WORD* f_at(int p) {
  struct code* position = first;
  while (p) {
    --p;
    position = position->next;
  }
  return &(position->data);
}
