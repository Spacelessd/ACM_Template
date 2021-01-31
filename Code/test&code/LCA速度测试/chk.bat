set name=a
:loop
	mkd
	%name%
	%name%1
	%name%2
	fc %name%.out %name%1.out
	if errorlevel==1 pause
	fc %name%.out %name%2.out
	if errorlevel==1 pause
goto loop