set name=1
:loop
	mkd
	用二项表实现的半动态变换.exe
	用整数组合分解实现的半动态变换.exe
	fc 1.out 2.out
	if errorlevel==1 pause
goto loop