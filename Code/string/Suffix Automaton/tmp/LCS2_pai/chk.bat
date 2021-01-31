:loop
	mkd
	LCS2
	LCS2_clj
	fc 1.out 2.out
	if errorlevel==1 pause
goto loop