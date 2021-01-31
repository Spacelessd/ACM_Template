del *.in
del *.out
set /p name=?
for /L %%x in (1,1,10) do (
mkd
%name%
ren %name%.in %name%%%x.in
ren %name%.out %name%%%x.out
)