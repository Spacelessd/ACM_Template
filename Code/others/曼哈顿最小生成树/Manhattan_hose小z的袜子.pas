const maxn=120000;oo=1 shl 30;
var
 z,edge,point,next,x,y,q,a,b,c,f,g:array[0..maxn] of longint;
  s,t,w:array[0..maxn*2] of longint;
  d,ans:array[0..maxn] of dword;
  e,i,j,k,m,n,ll,rr,lim:longint;
  k1,k2,f1,f2,now:dword;
procedure swap(var a,b:longint);
var k:longint;
begin
  k:=a; a:=b; b:=k;
end;

procedure sort1(l,r:longint);
var i,j:longint;
begin
  i:=l; j:=r; k:=q[random(r-l+1)+l]; k1:=x[k];k2:=y[k];
  while i<=j do
  begin
    while (x[q[i]]<k1)or(x[q[i]]=k1)and(y[q[i]]<k2)do inc(i);
    while(x[q[j]]>k1)or(x[q[j]]=k1)and(y[q[j]]>k2) do dec(j);
    if i<=j then
    begin
      swap(q[i],q[j]);
      inc(i); dec(j);
    end;
  end;
  if j>l then sort1(l,j);
  if i<r then sort1(i,r);
end;

procedure sort2(l,r:longint);
var i,j:longint;
begin
  i:=l; j:=r; k1:=w[random(r-l+1)+l];
  while i<=j do
  begin
    while w[i]<k1 do inc(i);
    while w[j]>k1 do dec(j);
    if i<=j then
    begin
      swap(s[i],s[j]); swap(t[i],t[j]);swap(w[i],w[j]);
      inc(i); dec(j);
    end;
  end;
  if j>l then sort2(l,j);
  if i<r then sort2(i,r);
end;

procedure add(i,k:longint);
begin
  while i<=lim do
  begin
    if b[k]<b[c[i]] then c[i]:=k;
    i:=i+i and (-i);
  end;
end;

function find(i:longint):longint;
var ans:longint;
begin
  ans:=m+1;
  while i>0 do
  begin
    if b[c[i]]<b[ans] then ans:=c[i];
    i:=i-i and (-i);
  end;
  find:=ans;
end;

procedure work;
begin
  for i:=1 to lim do c[i]:=m+1;
  for i:=1 to m do
  begin
    q[i]:=i; a[i]:=lim-a[i]+1;
  end;
  sort1(1,m);
  for j:=m downto 1 do
  begin
    i:=q[j]; k:=find(a[i]);
    if (k<>m+1) then
    begin
      inc(rr); s[rr]:=i; t[rr]:=k;w[rr]:=b[k]-b[i];
    end;
    add(a[i],i);
  end;
end;

function get(i:longint):longint;
begin
  if f[i]<>i then f[i]:=get(f[i]);
  get:=f[i];
end;

procedure dfs(i:longint);
var b:longint;
begin
  b:=edge[i]; z[i]:=1;
  if i<>m then
  begin
    if x[i]<ll then
      for j:=x[i] to ll-1 do
      begin
        now:=now+2*g[d[j]];
        inc(g[d[j]]);
      end
    else for j:=ll to x[i]-1 do
      begin
        now:=now-2*g[d[j]]+2; dec(g[d[j]]);
      end;
      if y[i]>rr then
      for j:=rr+1 to y[i] do
      begin
        now:=now+2*g[d[j]];
        inc(g[d[j]]);
      end
    else for j:=y[i]+1 to rr do
      begin
        now:=now-2*g[d[j]]+2; dec(g[d[j]]);
      end;
    ll:=x[i]; rr:=y[i]; ans[i]:=now;
  end;
  while b<>0 do
  begin
    if z[point[b]]=0 then dfs(point[b]);
    b:=next[b];
  end;
end;

begin
  //assign(input,'hose.in'); reset(input);
  //assign(output,'hose.out'); rewrite(output);
  read(n,m); inc(m); x[m]:=0; y[m]:=0;randomize; b[m+1]:=oo;
  lim:=2*n+1;
  for i:=1 to n do read(d[i]);
  for i:=1 to m do
  begin
    read(x[i],y[i]);
    a[i]:=y[i]-x[i]+1; b[i]:=y[i]+x[i];
  end;
  work;
  for i:=1 to m do
  begin
    k:=x[i]; x[i]:=y[i]; y[i]:=k;a[i]:=y[i]-x[i]+n;
  end;
  work;
  for i:=1 to m do
  begin
    x[i]:=n-x[i]+1; a[i]:=y[i]-x[i]+n+2;b[i]:=y[i]+x[i];
  end;
  work;
  for i:=1 to m do
  begin
    k:=x[i]; x[i]:=y[i]; y[i]:=k;
    a[i]:=y[i]-x[i]+n; b[i]:=y[i]+x[i];
  end;
  work;
  for i:=1 to m do y[i]:=n-y[i]+1;
  for i:=1 to m do f[i]:=i;
  sort2(1,rr);
  for i:=1 to rr do
  begin
    f1:=get(s[i]); f2:=get(t[i]);
    if f1<>f2 then
    begin
      inc(e); point[e]:=t[i]; next[e]:=edge[s[i]];edge[s[i]]:=e;
      inc(e); point[e]:=s[i];next[e]:=edge[t[i]]; edge[t[i]]:=e;
      f[f1]:=f2;
    end;
  end;
  ll:=0; rr:=0; now:=0; g[0]:=1; dfs(m);
  for i:=1 to m-1 do
  begin
    f1:=ans[i];f2:=(int64(y[i])-x[i]+1)*(y[i]-x[i]); k1:=f1; k2:=f2;
    if y[i]=x[i] then writeln('0/1')
    else begin
      while k2<>0 do
      begin
        now:=k1; k1:=k2; k2:=now mod k2;
      end;
      writeln(f1 div k1,'/',f2 div k1);
    end;
  end;
  //close(input); close(output);
end.


