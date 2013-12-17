GCC = gcc
GPP = g++
OBJECTS = lex.yy.o y.tab.o symbol_table.o
LEX_OTHER_FILES = lex.yy.c y.tab.c y.tab.h
CALC_OBJECTS = calc3br.o
CALC_RUN = f13-calc-r

JUST_BR = calc3br.o -o f13-calc-r

f : $(OBJECTS) calc3f.o
	$(GPP) $(OBJECTS) calc3f.o -o f13-calc-f

br : $(OBJECTS) calc3br.o
	$(GPP) $(OBJECTS) $(JUST_BR)
	cp f13-calc-r TESTS/mycalc3

all : $(OBJECTS) calc3br.o calc3g.o
	$(GPP) $(OBJECTS) calc3br.o -o f13-calc-r
	$(GPP) $(OBJECTS) calc3g.o -o f13-calc-g

test_yacc : y.tab.c lex.yy.o


calc3br.o : calc3.h calc3br.c
	gcc -c calc3br.c

calc3g.o : calc3.h calc3g.c
	gcc -c calc3g.c

calc3f.o : calc3.h calc3f.c
	gcc -c calc3f.c

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
	-rm -f $(OBJECTS) $(LEX_OTHER_FILES) *.o $(CALC_RUN)