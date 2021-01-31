var
  n,x,i,t1:longint;
  begin
  assign(output,'1.in');rewrite(output);
  randomize;t1:=randseed;
  n:=10000000;
  writeln(n);
  for i:=1 to n do write(random(1000000000),' ');
  close(output);
  assign(output,'read_pascal.out');rewrite(output);
  randomize;
  writeln('time=',randseed-t1);
  close(output);
  end.


