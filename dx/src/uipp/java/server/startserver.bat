@echo off 
if %1x==-verbosex (set VERBOSE="ver") else set VERBOSE=

set CURDIR=%CD% 
cd ..
set JXSRVPATH=%CD%
cd ..
set JDXROOT=%CD%
cd ..
set FDXROOT=%CD%
cd %CURDIR%

if %DXROOT%x==x    set DXROOT=%FDXROOT%
if %JXSVSPATH%x==x set JXSVSPATH=%JXSRVPATH%
if %JXMEMORY%x==x  set JXMEMORY=64
if %JXMDF%x==x     set JXMDF=all.mdf

set CLASSPATH=%JXSVSPATH%\class\server.jar
set DXMACROS=%JXSVSPATH%\dxmacros;%JXSVSPATH%\usermacros
set DXINCLUDE=%DXMACROS%
set DXDATA=%JXSVSPATH%\userdata
set DXARGS=-execonly -highlight off -optimize memory

if %DXJAVASRV%x==x set PATH=%DXROOT%\bin_intelnt;%PATH%;%DXROOT%\bin;%DXROOT%\lib_intelnt;%JXSVSPATH%\lib_intelnt

rem Now set this variable so PATH won't keep growing.
set DXJAVASRV=RunOnceAlready

echo %JXSVSPATH%\nets>dxserver.paths

if %VERBOSE%x==x goto LAUNCH

:VO
echo DXROOT = %DXROOT%
echo CLASSPATH = %CLASSPATH%
echo DXMACROS = %DXMACROS%
echo DXINCLUDE = %DXINCLUDE%
echo DXDATA = %DXDATA%
echo DXARGS = %DXARGS%
echo\ 
echo\
echo PATH = %PATH%
echo\
echo java -classpath %CLASSPATH% -DDXServer.outUrl=output -DDXServer.outDir=%JDXROOT%\output DXServer
goto END

:LAUNCH
java -classpath %CLASSPATH% -DDXServer.outUrl=output -DDXServer.outDir="../../output" DXServer

:END
