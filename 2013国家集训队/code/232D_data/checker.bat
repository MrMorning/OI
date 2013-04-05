@echo off
set prog1=232D
set prog2=232D_brute
set gen=232D_datamaker
set cnt=0
:begin
set /a cnt=cnt+1
echo Test Case: %cnt%
echo %* %RANDOM% | %gen%.exe
%prog1%.exe > %prog1%.out
%prog2%.exe > %prog2%.out
fc %prog1%.out %prog2%.out
if errorlevel 1 goto failed
echo Same
goto begin
:failed
echo Wrong Answer!!
pause
