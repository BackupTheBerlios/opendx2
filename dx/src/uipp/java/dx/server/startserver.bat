@echo off

if %JXDRIVE%x==x   set JXDRIVE=d:
if %DXROOT%x==x    set DXROOT=d:\dx
if %JDKPATH%x==x   set JDKPATH=d:\jdk1_1
if %JXSVSPATH%x==x set JXSVSPATH=\java\server
if %JXMEMORY%x==x  set JXMEMORY=64
if %JXMDF%x==x     set JXMDF=all.mdf

set CLASSPATH=
set DXMACROS=%JXSVSPATH%/dxmacros;../usermacros
set DXINCLUDE=%DXMACROS%
set DXDATA=../userdata
set DXARGS=-execonly -highlight off -optimize memory

set PATH=..\bin_intelnt;%PATH%;%DXROOT%\bin;..\lib_intelnt

rem  the following line is essential since cd does not do a drive change
%JXDRIVE%

cd %JXSVSPATH%\class
echo ../pcnets>dxserver.paths

%JDKPATH%\bin\java -DDXServer.outUrl=output -DDXServer.outDir=../../output DXServer
