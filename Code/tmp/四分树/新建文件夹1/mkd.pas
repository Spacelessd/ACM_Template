var
 i,j,x,y,n,m,k:longint;

begin
 randomize;
 assign(output,'1.in'); rewrite(output);
 for j:=1 to 10 do
  begin
   n:=1000; m:=1000; k:=1000;
   writeln(n,' ',m,' ',k);

   for i:=1 to k do
    begin
     x:=random(n); y:=random(n);
     writeln(random(n-x),' ',random(m-y),' ',random(100),' ',x,' ',y);
    end;
  end;
end.
