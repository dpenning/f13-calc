GCC = gcc
GPP = g++
OBJECTS = lex.yy.o y.tab.o symbol_table.o calc3g.o

f13-calc : $(OBJECTS)
	$(GPP) $(OBJECTS) -o f13-calc
y.tab.c : calc3.y
	bison -y -d calc3.y
lex.yy.c : calc3.l
	flex calc3.l
lex.yy.o : lex.yy.c y.tab.c
	$(GCC) -c y.tab.c lex.yy.c 
symbol_table.o : symbol_table.cc symbol_table.h
	$(GPP) -c symbol_table.cc

clean:
	-rm -f $(OBJECTS) lex.yy.c y.tab.c y.tab.h
