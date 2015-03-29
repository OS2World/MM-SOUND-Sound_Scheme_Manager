# makefile
# Created by IBM WorkFrame/2 MakeMake at 6:05:55 on 21 July 1999
#
# The actions included in this make file are:
#  Compile::C++ Compiler
#  Link::Linker
#  Bind::Resource Bind
#  Compile::Resource Compiler

.SUFFIXES: .c .obj .rc .res 

.all: \
    .\ssm.exe

.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /Tdp /Q /Ti /C %s

{e:\data\c\ssm}.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /Tdp /Q /Ti /C %s

.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r %s %|dpfF.RES

{e:\data\c\ssm}.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r %s %|dpfF.RES

.\ssm.exe: \
    .\support.obj \
    .\test.obj \
    .\find.obj \
    .\main.obj \
    .\pmtools.obj \
    .\prodinfo.obj \
    .\question.obj \
    .\settings.obj \
    .\ssm.obj \
    .\ssm.res \
    {$(LIB)}os2386.lib \
    {$(LIB)}mmpm2.lib \
    {$(LIB)}cppom30.lib \
    {$(LIB)}ssm.def
    @echo " Link::Linker "
    @echo " Bind::Resource Bind "
    icc.exe @<<
     /B" /de /exepack:2 /pmtype:pm /packd /nologo"
     /Fessm.exe 
     os2386.lib 
     mmpm2.lib 
     cppom30.lib 
     ssm.def
     .\support.obj
     .\test.obj
     .\find.obj
     .\main.obj
     .\pmtools.obj
     .\prodinfo.obj
     .\question.obj
     .\settings.obj
     .\ssm.obj
<<
    rc.exe .\ssm.res ssm.exe

.\support.obj: \
    e:\data\c\ssm\support.c \
    {e:\data\c\ssm;$(INCLUDE);}ssm.h \
    {e:\data\c\ssm;$(INCLUDE);}support.h \
    {e:\data\c\ssm;$(INCLUDE);}main.h \
    {e:\data\c\ssm;$(INCLUDE);}acceltable.h \
    {e:\data\c\ssm;$(INCLUDE);}stringtable.h \
    {e:\data\c\ssm;$(INCLUDE);}test.h \
    {e:\data\c\ssm;$(INCLUDE);}menu.h \
    {e:\data\c\ssm;$(INCLUDE);}question.h \
    {e:\data\c\ssm;$(INCLUDE);}find.h \
    {e:\data\c\ssm;$(INCLUDE);}icon.h \
    {e:\data\c\ssm;$(INCLUDE);}prodinfo.h \
    {e:\data\c\ssm;$(INCLUDE);}settings.h \
    {e:\data\c\ssm;$(INCLUDE);}pmtools.h

.\ssm.obj: \
    e:\data\c\ssm\ssm.c \
    {e:\data\c\ssm;$(INCLUDE);}ssm.h \
    {e:\data\c\ssm;$(INCLUDE);}support.h \
    {e:\data\c\ssm;$(INCLUDE);}main.h \
    {e:\data\c\ssm;$(INCLUDE);}acceltable.h \
    {e:\data\c\ssm;$(INCLUDE);}stringtable.h \
    {e:\data\c\ssm;$(INCLUDE);}test.h \
    {e:\data\c\ssm;$(INCLUDE);}menu.h \
    {e:\data\c\ssm;$(INCLUDE);}question.h \
    {e:\data\c\ssm;$(INCLUDE);}find.h \
    {e:\data\c\ssm;$(INCLUDE);}icon.h \
    {e:\data\c\ssm;$(INCLUDE);}prodinfo.h \
    {e:\data\c\ssm;$(INCLUDE);}settings.h \
    {e:\data\c\ssm;$(INCLUDE);}pmtools.h

.\settings.obj: \
    e:\data\c\ssm\settings.c \
    {e:\data\c\ssm;$(INCLUDE);}ssm.h \
    {e:\data\c\ssm;$(INCLUDE);}support.h \
    {e:\data\c\ssm;$(INCLUDE);}main.h \
    {e:\data\c\ssm;$(INCLUDE);}acceltable.h \
    {e:\data\c\ssm;$(INCLUDE);}stringtable.h \
    {e:\data\c\ssm;$(INCLUDE);}settings.h

.\question.obj: \
    e:\data\c\ssm\question.c \
    {e:\data\c\ssm;$(INCLUDE);}ssm.h \
    {e:\data\c\ssm;$(INCLUDE);}support.h \
    {e:\data\c\ssm;$(INCLUDE);}main.h \
    {e:\data\c\ssm;$(INCLUDE);}acceltable.h \
    {e:\data\c\ssm;$(INCLUDE);}stringtable.h \
    {e:\data\c\ssm;$(INCLUDE);}question.h

.\prodinfo.obj: \
    e:\data\c\ssm\prodinfo.c \
    {e:\data\c\ssm;$(INCLUDE);}ssm.h \
    {e:\data\c\ssm;$(INCLUDE);}support.h \
    {e:\data\c\ssm;$(INCLUDE);}main.h \
    {e:\data\c\ssm;$(INCLUDE);}acceltable.h \
    {e:\data\c\ssm;$(INCLUDE);}stringtable.h \
    {e:\data\c\ssm;$(INCLUDE);}test.h \
    {e:\data\c\ssm;$(INCLUDE);}menu.h \
    {e:\data\c\ssm;$(INCLUDE);}question.h \
    {e:\data\c\ssm;$(INCLUDE);}find.h \
    {e:\data\c\ssm;$(INCLUDE);}icon.h \
    {e:\data\c\ssm;$(INCLUDE);}prodinfo.h \
    {e:\data\c\ssm;$(INCLUDE);}settings.h \
    {e:\data\c\ssm;$(INCLUDE);}pmtools.h

.\pmtools.obj: \
    e:\data\c\ssm\pmtools.c

.\main.obj: \
    e:\data\c\ssm\main.c \
    {e:\data\c\ssm;$(INCLUDE);}ssm.h \
    {e:\data\c\ssm;$(INCLUDE);}support.h \
    {e:\data\c\ssm;$(INCLUDE);}main.h \
    {e:\data\c\ssm;$(INCLUDE);}acceltable.h \
    {e:\data\c\ssm;$(INCLUDE);}stringtable.h \
    {e:\data\c\ssm;$(INCLUDE);}test.h \
    {e:\data\c\ssm;$(INCLUDE);}menu.h \
    {e:\data\c\ssm;$(INCLUDE);}question.h \
    {e:\data\c\ssm;$(INCLUDE);}find.h \
    {e:\data\c\ssm;$(INCLUDE);}icon.h \
    {e:\data\c\ssm;$(INCLUDE);}prodinfo.h \
    {e:\data\c\ssm;$(INCLUDE);}settings.h \
    {e:\data\c\ssm;$(INCLUDE);}pmtools.h

.\find.obj: \
    e:\data\c\ssm\find.c \
    {e:\data\c\ssm;$(INCLUDE);}ssm.h \
    {e:\data\c\ssm;$(INCLUDE);}support.h \
    {e:\data\c\ssm;$(INCLUDE);}main.h \
    {e:\data\c\ssm;$(INCLUDE);}acceltable.h \
    {e:\data\c\ssm;$(INCLUDE);}stringtable.h \
    {e:\data\c\ssm;$(INCLUDE);}test.h \
    {e:\data\c\ssm;$(INCLUDE);}menu.h \
    {e:\data\c\ssm;$(INCLUDE);}question.h \
    {e:\data\c\ssm;$(INCLUDE);}find.h \
    {e:\data\c\ssm;$(INCLUDE);}icon.h \
    {e:\data\c\ssm;$(INCLUDE);}prodinfo.h \
    {e:\data\c\ssm;$(INCLUDE);}settings.h \
    {e:\data\c\ssm;$(INCLUDE);}pmtools.h

.\test.obj: \
    e:\data\c\ssm\test.c \
    {e:\data\c\ssm;$(INCLUDE);}ssm.h \
    {e:\data\c\ssm;$(INCLUDE);}support.h \
    {e:\data\c\ssm;$(INCLUDE);}main.h \
    {e:\data\c\ssm;$(INCLUDE);}acceltable.h \
    {e:\data\c\ssm;$(INCLUDE);}stringtable.h \
    {e:\data\c\ssm;$(INCLUDE);}test.h

.\ssm.res: \
    e:\data\c\ssm\ssm.rc \
    {e:\data\c\ssm;$(INCLUDE)}settings.dlg \
    {e:\data\c\ssm;$(INCLUDE)}settings.h \
    {e:\data\c\ssm;$(INCLUDE)}prodinfo.dlg \
    {e:\data\c\ssm;$(INCLUDE)}prodinfo.h \
    {e:\data\c\ssm;$(INCLUDE)}test.dlg \
    {e:\data\c\ssm;$(INCLUDE)}test.h \
    {e:\data\c\ssm;$(INCLUDE)}find.dlg \
    {e:\data\c\ssm;$(INCLUDE)}find.h \
    {e:\data\c\ssm;$(INCLUDE)}question.dlg \
    {e:\data\c\ssm;$(INCLUDE)}question.h \
    {e:\data\c\ssm;$(INCLUDE)}main.dlg \
    {e:\data\c\ssm;$(INCLUDE)}main.h \
    {e:\data\c\ssm;$(INCLUDE)}ssm.ico \
    {e:\data\c\ssm;$(INCLUDE)}acceltable.h \
    {e:\data\c\ssm;$(INCLUDE)}stringtable.h \
    {e:\data\c\ssm;$(INCLUDE)}icon.h \
    {e:\data\c\ssm;$(INCLUDE)}menu.h
