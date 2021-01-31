md calc
for /R %%x in (*.exe) do (
cd calc
%%x>%%x.txt
cd ..
)
pause
