var
  n,x,i,t1:longint;
  begin
  assign(input,'1.in');reset(input);
  assign(output,'read_pascal.out');rewrite(output);
  randomize;t1:=randseed;
  read(n);
  for i:=1 to n do read(x);
  randomize;
  writeln('time=',randseed-t1);
  close(input);close(output);
  end.


