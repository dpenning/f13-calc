GCC = gcc
GPP = g++
OBJECTS = lex.yy.o y.tab.o symbol_table.o
LEX_OTHER_FILES = lex.yy.c y.tab.c y.tab.h
CALC_OBJECTS = calc3a.o calc3b.o calc3g.o calc3p.o
CALC_RUN = f13-calc-a f13-calc-b f13-calc-g f13-calc-p

JUST_PSTACK = calc3p.o -o f13-calc-p

JUST_BR = calc3br.o -o f13-calc-r

br : $(OBJECTS) calc3br.o
	$(GPP) $(OBJECTS) $(JUST_BR)
	cp f13-calc-r TESTS/mycalc3

p : $(OBJECTS) calc3p.o
	$(GPP) $(OBJECTS) $(JUST_PSTACK)

all : $(OBJECTS) calc3.h calc3a.o calc3b.o calc3g.o calc3p.o
	$(GPP) $(OBJECTS) calc3a.o -o f13-calc-a
	$(GPP) $(OBJECTS) calc3b.o -o f13-calc-b
	$(GPP) $(OBJECTS) calc3g.o -o f13-calc-g
	$(GPP) $(OBJECTS) calc3p.o -o f13-calc-p
	$(GPP) $(OBJECTS) calc3br.o -o f13-calc-r

calc3a.o : calc3.h calc3a.c
	gcc -c calc3a.c
calc3b.o : calc3.h calc3b.c
	gcc -c calc3b.c
calc3g.o : calc3.h calc3g.c
	gcc -c calc3g.c
calc3p.o : calc3.h calc3p.c
	gcc -c calc3p.c
calc3br.o : calc3.h calc3br.c
	gcc -c calc3br.c

y.tab.c : calc3.y calc3.h
	bison -y -d calc3.y
lex.yy.c : calc3.l calc3.h
	flex calc3.l
lex.yy.o : lex.yy.c y.tab.c calc3.h
	$(GCC) -c y.tab.c lex.yy.c
symbol_table.o : symbol_table.cc symbol_table.h calc3.h
	$(GPP) -c symbol_table.cc

check-syntax:
	gcc -o nul -S ${CHK_SOURCES}

clean:
	-rm -f $(OBJECTS) $(LEX_OTHER_FILES) $(CALC_OBJECTS)
clean-all:
	-rm -f $(OBJECTS) $(LEX_OTHER_FILES) $(CALC_OBJECTS) $(CALC_RUN)