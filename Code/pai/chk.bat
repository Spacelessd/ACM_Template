set name=a
:loop
	mkd.exe
	%name%.exe
	%name%1.exe
	fc %name%.out %name%1.out
	if errorlevel==1 pause
goto loop


