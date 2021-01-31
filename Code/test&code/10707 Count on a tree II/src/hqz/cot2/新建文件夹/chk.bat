:loop
	mkd
	cot2
bl
	fc cot2.out cot3.out
	if errorlevel==1 pause
goto loop