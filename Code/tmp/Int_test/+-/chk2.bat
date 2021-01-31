set name=a
:loop
	mkd1.exe
	1.exe
	3.exe
	fc 1.out 3.out
	if errorlevel==1 pause
goto loop


