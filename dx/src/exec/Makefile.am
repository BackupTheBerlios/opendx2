SUBDIRS = libdx dxmods hwrender dpexec dxexec

DELFILES = \
        mduser.o \
        lbmemory.o \
        lbmem.o    \
        exattribute.o \
        exbackground.o \
        excache.o \
        excachegraph.o \
        exccm.o \
        excommand.o \
        excontext.o \
        exdistconnect.o \
        exdistpacket.o \
        exdistqueue.o \
        exdxmain.o \
        exdxpfsmgr.o \
        exevalgraph.o \
        exgraph.o \
        exgraph2.o \
        exgraphqueue.o \
        exhelp.o \
        exinstrument.o \
        exlex.o \
        exlog.o \
        exmain.o \
        exnodereadb.o \
        exnodewriteb.o \
        expacket.o \
        exparsemdf.o \
        expath.o \
        expendingcmds.o \
        exqueue.o \
        exremote.o \
        exrih.o \
        exrq.o \
        exsocket.o \
        exstatus.o \
        exswap.o \
        extask.o \
        exvariable.o \
        exvcr.o \
        exyuiif.o


install-exec-local:
	if test -d tmp ; then						   \
		rm -rf tmp ;						   \
	fi ;								   \
	mkdir tmp ;							   \
	cd tmp ; 							   \
	for i in dpexec dxmods hwrender hwrender/opengl libdx ; do	   \
		echo merging  $$i ;					   \
		case $$i in						   \
			dpexec) 	 lib=libDPEXEC.a ; pre=ex ;; 	   \
			dxmods) 	 lib=libDXMODS.a ; pre=md ;; 	   \
			hwrender) 	 lib=libHW.a ;     pre=hw ;;	   \
			hwrender/opengl) lib=libOPENGL.a ; pre=og ;; 	   \
			libdx)		 lib=libLIBDX.a ;  pre=lb ;;	   \
		esac ;							   \
		echo lib: $$lib pre: $$pre ; 				   \
		files=`ar t ../$$i/$$lib` ; 				   \
		ar x ../$$i/$$lib; 					   \
		for j in $$files ; do					   \
			l=`echo $$j | tr A-Z a-z` ;			   \
			echo $$j renamed $$pre$$l ;	 		   \
			mv $$j $$pre$$l ;				   \
		done ; 							   \
		echo adding files from $$i/$$lib to DX library... ;	   \
		ar qv libDX.a *.o ;					   \
		rm *.o	;						   \
	done ; 								   \
	if test ! -z "@FMT_LIBS@" ; then				   \
		for i in @FMT_LIBS@ "" ; do				   \
			lib="";						   \
			for j in /lib /usr/lib /usr/local/lib @LIBS@ ; do  \
				k=`echo $$j | sed -e "s/-L//"` ;	   \
				if test -f $$k/$$i ; then		   \
					lib=$$k/$$i ;			   \
					break ;				   \
				fi ;					   \
			done ;						   \
			if test "$$lib" = ""  ; then			   \
				echo Library $$i not found ; 		   \
			else						   \
				echo $$lib ;				   \
				case $$i in				   \
					libz.a) 	 pre=z  ;; 	   \
					libcdf.a) 	 pre=cd ;; 	   \
					libjpeg.a) 	 pre=jp ;;	   \
				libdf.a) 	 pre=df ;;		   \
					libnetcdf.a) 	 pre=nc ;;	   \
				esac ;					   \
				files=`ar t $$lib` ; 			   \
				ar x $$lib ; 				   \
				for j in $$files ; do			   \
					l=`echo $$j | tr A-Z a-z` ;	   \
					echo $$j renamed $$pre$$l ; 	   \
					mv $$j $$pre$$l ;		   \
				done ; 					   \
				echo adding files from $$i to library... ; \
				ar qv libDX.a *.o ;			   \
				rm *.o ; 				   \
			fi ; 						   \
		done ;							   \
	fi ; 								   \
	mv libDX.a .. ; 						   \
	cd .. ;								   \
	$(INSTALL) libDX.a $(prefix)/dx/lib_$(ARCH) ;			   \
	echo making libDXcallm.a ;					   \
	mv libDX.a tmp/libDXcallm.a ; 					   \
	cd tmp; 							\
	ar dv libDXcallm.a $(DELFILES) ;				\
	for i in libdx dxmods ; do	   					\
		echo merging  $$i ;					   \
		case $$i in						   \
			libdx) 	 lib=libcallm.a ; pre=cm ;; 	  	 \
			dxmods)  lib=libusercm.a ; pre=cm ;; 	  	 \
		esac ;							   \
		echo lib: $$lib pre: $$pre ; 				   \
		files=`ar t ../$$i/$$lib` ; 				   \
		ar x ../$$i/$$lib; 					   \
		for j in $$files ; do					   \
			l=`echo $$j | tr A-Z a-z` ;			   \
			echo $$j renamed $$pre$$l ;	 		   \
			mv $$j $$pre$$l ;				   \
		done ; 							   \
		echo adding files from $$i/$$lib to DXcallm library... ;	   \
		ar qv libDXcallm.a *.o ;					   \
		rm *.o	;						   \
	done ; 								   \
	mv libDXcallm.a .. ;						\
	cd .. ;								\
	$(INSTALL) libDXcallm.a $(prefix)/dx/lib_$(ARCH) ;		   \
	rm libDXcallm.a ;

