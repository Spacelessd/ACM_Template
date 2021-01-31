set name=a
:loop
	mkd.exe
	1.exe
	2.exe
	3.exe
	fc 1.out 2.out
	if errorlevel==1 pause
	fc 1.out 3.out
	if errorlevel==1 pause
goto loop


