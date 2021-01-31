:loop
	mkd
	LCS2
	LCS2_clj
	LCS2_fhq
	fc 2.out 3.out
	if errorlevel==1 pause
	fc 1.out 2.out
	if errorlevel==1 pause
goto loop