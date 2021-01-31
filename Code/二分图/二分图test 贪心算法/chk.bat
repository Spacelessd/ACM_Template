:loop
	mkd
	Hopcraft-Karp
	"二分图最大匹配(贪心算法)"
	"二分图最大匹配(贪心算法)N^2"
	fc 1.out 2.out
	if errorlevel==1 pause
	fc 1.out 3.out
	if errorlevel==1 pause
goto loop