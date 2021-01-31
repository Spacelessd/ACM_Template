var
  t,n,m,i,x,y,z:longint;
begin
  assign(output,'1.in'); rewrite(output);
  randomize;
  t:=20; writeln(t);
  for t:=1 to t do
    begin
          writeln;
	  n:=10000; writeln(n);
	  for i:=2 to n do writeln(random(i-1)+1,' ',i,' ',random(1000)-500);
	  m:=10000;
	  for i:=1 to m do
	     begin
		   z:=random(2); x:=random(n-1)+1; y:=random(n)+1;
                   while (x=y) do begin x:=random(n-1)+1; y:=random(n)+1; end;
		   if (z=1) then writeln('QUERY ',x,' ',y)
		   else writeln('CHANGE ',x,' ',y);
		 end;
	  writeln('DONE');
	end;
  close(output);
end.
