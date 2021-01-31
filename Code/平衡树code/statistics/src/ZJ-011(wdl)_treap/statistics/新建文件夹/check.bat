:a
	mkd
	statistics
	statistics_bl
	fc statistics.out statistics_bl.out
	if errorlevel == 1 pause
goto a