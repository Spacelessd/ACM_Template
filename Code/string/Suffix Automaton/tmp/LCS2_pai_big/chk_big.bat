:loop
	mkd
	LCS2
	LCS2_fhq
	fc 1.out 3.out
	if errorlevel==1 pause
goto loop