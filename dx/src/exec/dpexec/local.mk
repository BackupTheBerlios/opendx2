
SUFFIXES = .m .y .c .s .h .o .a 

.y.h:
	$(YACC) $(YFLAGS) -d $*.y
	mv y.tab.h $*.h
	mv y.tab.c $*.c

.y.c:
	$(YACC) $(YFLAGS) -d $*.y
	mv y.tab.h $*.h
	mv y.tab.c $*.c

compile.h: 
	echo '#define' EX_COM_DATE '"'`date`'"' >> compile.h
	echo '#define' EX_COM_HOST '"'`uname -a`'"' >> compile.h
	
