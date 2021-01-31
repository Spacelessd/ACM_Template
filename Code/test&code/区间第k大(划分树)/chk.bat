
:loop
	mkd
	1
	2
	fc 1.out 2.out
	if errorlevel==1 pause
goto loop