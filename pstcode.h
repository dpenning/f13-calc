/*
 * PROJECT         : CS 441,JWJ CS UK
 * FILE NAME       : pstcode.h
 * PROGRAMMER      : prepred for CS 441 (NFM)
 *
 * DATE WRITTEN    : 29 Apr 2000
 *
 * SYNOPSIS        : Interface for class PstackCode.  An implementation is
 *                   provided in pstcode.cc (q.v.).
 *
 * DESCRIPTION     : Class implementing a block of pstack code.  The code
 *                   is represented using a vector of integers.
 *
 * MODIFICATION HISTORY:
 *          29 Apr 2000      Put implementation into code.cc (was inline).
 *          28 Apr 2000      Add string support, and patchup for prolog.
 *          25 Apr 2000      Initial version.
 */

#ifndef _PSTCODE_H_INCLUDED
#define _PSTCODE_H_INCLUDED

#include "pstack/apm.h"

// Temporaries used by Code::add_*()
#define ADDR_TEMP  (STORAGE - 1)
#define ADDR_TEMP2 (STORAGE - 2)
#define ADDR_TEMP3 (STORAGE - 3)

struct code {
  WORD data;
  struct code* next;
};

struct code* first;
struct code* last;

// Add an instruction or (non-relocatable) operand
void add_int(int op);

// Add a real operand
void add_float(float op);

// Generate code to duplicate the top element of the stack.
void add_dup();

// Generate code to duplicate the top two elements of the stack.
void add_2dup();

// Generate code to copy the 3rd element on the stack to the topa
void add_3pick();

// Generate code to begin a program
void begin_prog();

// Generate code to end a program
//  void end_prog();  removed jwj
void end_prog(int); // added jwj

// Generate code to start a process block
void begin_proc();

// Generate code to end a process block
void end_proc(int patch_loc, int varsize);
 
// Write the code to a file.
int write(char* file, int binary);

// Return the current position.
int pos();

// Return a reference to the instruction at the specified position.
WORD* at(int p);

// Return a reference to a float stored at the specified position.
WORD* f_at(int p);



#endif
