const maxn=105; eps=1e-15;
var
  i,j,k,m,n,c:longint;
  x,y,z:array[0..maxn] of extended;
  x1,y1,z1,x2,y2,z2,x3,y3,z3,x0,y0,z0,dj,ans:extended;
  o1,o2:boolean;
begin
  read(n);
  for i:=1 to n do
  begin
    read(x[i],y[i],z[i]);
    x[i]:=x[i]+random(1000)*eps; y[i]:=y[i]+random(1000)*eps;
    z[i]:=z[i]+random(1000)*eps;
  end;
  for i:=1 to n do
    for j:=i+1 to n do
      for k:=j+1 to n do
      begin
        x1:=x[i]; y1:=y[i]; z1:=z[i];
        x2:=x[j]-x1; y2:=y[j]-y1; z2:=z[j]-z1;
        x3:=x[k]-x1; y3:=y[k]-y1; z3:=z[k]-z1;
        x0:=y2*z3-y3*z2;
        y0:=x3*z2-x2*z3;
        z0:=x2*y3-x3*y2;
        o1:=false; o2:=false;
        for c:=1 to n do
        if (c<>i)and(c<>j)and(c<>k) then
        begin
          dj:=(x[c]-x1)*x0+(y[c]-y1)*y0+(z[c]-z1)*z0;
          if dj>0 then o1:=true;
          if dj<0 then o2:=true;
          if o1 and o2 then break;
        end;
        if o1 xor o2 then
          ans:=ans+sqrt(sqr(x0)+sqr(y0)+sqr(z0));
      end;
  writeln(ans/2:0:6);
end.


