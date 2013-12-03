BINS = api apd apm
PSTHEADS = apm.h apname.h
PSTOBJS = apmain.o apm.y.o apm.l.o
LIBS =
GCC = gcc

all : $(BINS)

api : api.c $(PSTHEADS)
	$(GCC) $< -o $@
apd : apd.c $(PSTHEADS)
	$(GCC) $< -o $@
apm : $(PSTOBJS)
	$(GCC) $(PSTOBJS) -o $@ $(LIBS)
apmain.o : apmain.c
	$(GCC) -c $<
apm.y.o : apm.y.c apm.y.h
	$(GCC) -c $<
apm.l.o : apm.l.c
	$(GCC) -c $<

clean :
	-rm $(PSTOBJS)
clean-all :
	-rm $(PSTOBJS) $(BINS)
