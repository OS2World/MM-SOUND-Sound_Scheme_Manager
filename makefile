# nmake makefile
#
# Tools used:
#  Compile::Watcom Resource Compiler
#  Compile::GNU C
#  Make: nmake or GNU make

CFLAGS=-Wall -Zomf -c -O2
DEBUGFLAGS=-g

HEADERS = acceltable.h find.h icon.h main.h menu.h pmtools.h prodinfo.h question.h settings.h ssm.h stringtable.h suport.h test.h
OBJS = main.obj find.obj pmtools.obj prodinfo.obj question.obj settings.obj ssm.obj support.obj test.obj
ALL_IPF = help.ipf

all : ssm.exe

ssm.exe: $(OBJS) ssm.res
	gcc -Zomf -Zmap $(OBJS) ssm.def ssm.res -o $@
	wrc ssm.res

main.obj: main.c $(HEADER)
	gcc $(CFLAGS) $(DEBUGFLAGS) main.c -o main.obj

find.obj: find.c $(HEADERS)
	gcc $(CFLAGS) $(DEBUGFLAGS) find.c -o find.obj

pmtools.obj: pmtools.c $(HEADERS) 
	gcc $(CFLAGS) $(DEBUGFLAGS) pmtools.c -o pmtools.obj

prodinfo.obj: prodinfo.c $(HEADERS)
	gcc $(CFLAGS) $(DEBUGFLAGS) prodinfo.c -o prodinfo.obj

question.obj: question.c $(HEADERS)
	gcc $(CFLAGS) $(DEBUGFLAGS) question.c -o question.obj

settings.obj: settings.c  $(HEADERS)
	gcc $(CFLAGS) $(DEBUGFLAGS) settings.c -o settings.obj

ssm.obj: ssm.c  $(HEADERS)
	gcc $(CFLAGS) $(DEBUGFLAGS) ssm.c -o ssm.obj

support.obj: support.c $(HEADERS)
	gcc $(CFLAGS) $(DEBUGFLAGS) support.c -o support.obj

test.obj: test.c $(HEADERS)
	gcc $(CFLAGS) $(DEBUGFLAGS) test.c -o test.obj

ssm.res: ssm.rc ssm.ico $(HEADERS)
	wrc -r main.rc

help.hlp: $(ALL_IPF)
	wipfc help.ipf -o help.hlp

.PHONY : clean

clean :
	rm -rf *exe *res *obj *lib *.hlp
