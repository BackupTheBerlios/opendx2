all: sequence.h imagemac.net gifmac.h dxmac.h netlex.c netyacc.c

EditorWindow.o: sequence.h
ImageNodeUtils.o: imagemac.h dxmac.h vrmlmac.h gifmac.h


sequence.h: sequence.net 
	sh net2c sequence.net sequence.h

imagemac.h: imagemac.net
	sh net2c imagemac.net imagemac.h

gifmac.h:  
	sh net2c ../java/server/macros/gifmac.net gifmac.h

vrmlmac.h:
	sh net2c ../java/server/macros/vrmlmac.net vrmlmac.h

dxmac.h:
	sh net2c ../java/server/macros/dxmac.net dxmac.h

netlex.c: net.lex
	$(LEX) net.lex
	sed "/#line/d" lex.yy.c > netlex.c

netyacc.c: net.yacc netlex.c netyacc.awk
	$(YACC) net.yacc
	awk -f netyacc.awk y.tab.c > netyacc.c
	rm -f y.tab.c
