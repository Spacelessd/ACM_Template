set name=ditch
for /L %%x in (1,1,10) do (
mkd
%name%.exe
ren %name%.in %name%%%x.in
ren %name%.out %name%%%x.out
)