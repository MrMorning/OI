@echo off
set prog1=81E
set prog2=81E
set gen=81E_datamaker
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
