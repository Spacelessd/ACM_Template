g++ statistics.cpp -o x -g
for /L %%i in (1,1,10) do (
	ren statistics%%i.in statistics.in
	x
	ren statistics.in statistics%%i.in
	ren statistics.out statistics%%i.out
)	
pause