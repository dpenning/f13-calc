GCC = gcc
GPP = g++
OBJECTS = lex.yy.o y.tab.o symbol_table.o

f13-calc-a : $(OBJECTS) calc3.h calc3a.o calc3b.o calc3g.o
	$(GPP) $(OBJECTS) calc3a.o -o f13-calc-a
	$(GPP) $(OBJECTS) calc3b.o -o f13-calc-b
	$(GPP) $(OBJECTS) calc3g.o -o f13-calc-g
calc3a.o : calc3.h calc3a.c
	gcc -c calc3a.c
calc3b.o : calc3.h calc3b.c
	gcc -c calc3b.c
calc3g.o : calc3.h calc3g.c
	gcc -c calc3g.c
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
	-rm -f $(OBJECTS) lex.yy.c y.tab.c y.tab.h calc3g.o calc3a.o calc3b.o
