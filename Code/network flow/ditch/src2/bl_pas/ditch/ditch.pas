program ditch;
var
  n,m,i,j,a,b,mi:longint;
  ff:array[1..2000,1..2000]of longint;
  flow:array[1..2000]of longint;
  pre:array[1..2000]of longint;
  use:array[1..2000]of boolean;
  c,x,max,sum:longint;
begin
  assign(input,'ditch.in');
  assign(output,'ditch.out');
  reset(input);
  rewrite(output);
  readln(n,m);
  for i:=1 to n do
  begin
    readln(a,b,c);
    inc(ff[a,b],c);
  end;
  sum:=0;
  while true do
  begin
    fillchar(flow,sizeof(flow),0);
    flow[1]:=maxlongint;
    fillchar(use,sizeof(use),false);
    while true do
    begin
      max:=0;
      mi:=0;
      for i:=1 to m do
        if not use[i] then
          if flow[i]>max then
          begin
            max:=flow[i];
            mi:=i;
          end;
      if mi=0 then
        break;
      if mi=m then
        break;
      use[mi]:=true;
      for i:=1 to m do
        if ff[mi,i]>0 then
        begin
          if flow[mi]<ff[mi,i] then
            x:=flow[mi]
          else
            x:=ff[mi,i];
          if x>flow[i] then
          begin
            pre[i]:=mi;
            flow[i]:=x;
          end;
        end;
    end;
    if mi=0 then
      break;
    i:=m;
    x:=flow[m];
    inc(sum,x);
    while i<>1 do
    begin
      j:=i;
      i:=pre[i];
      ff[i,j]:=ff[i,j]-x;
      ff[j,i]:=ff[j,i]+x;
    end;
  end;
  writeln(sum);
  close(output);
end.
