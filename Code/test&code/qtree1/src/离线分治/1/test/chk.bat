set name=1
:loop
	mkd
	%name%
	%name%1
	fc %name%.out %name%1.out
	if errorlevel==1 pause
goto loop