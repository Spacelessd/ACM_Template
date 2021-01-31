del *.in
del *.out
set name=a
for /L %%x in (1,1,10) do (
	mkd.exe
	%name%.exe
	ren %name%.in %name%%%x.in
	ren %name%.out %name%%%x.out
)


