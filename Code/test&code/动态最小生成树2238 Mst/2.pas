program xqz;
const maxn=50005; maxm=200005;
var
  i,j,k,m,n,tt,f1,f2,e,ee,ans,task:longint;
  f,edge,ed,ma,o:array[0..maxn] of longint;
  point,next,g:array[-maxn..maxn] of longint;
  pos,s,t,w,ne,po,lca,b,d,y:array[0..maxm] of longint;
procedure sort(ll,rr:longint);
var i,j:longint;
begin
  i:=ll; j:=rr; tt:=w[random(rr-ll+1)+ll];
  while i<=j do
  begin
    while w[i]<tt do inc(i);
    while w[j]>tt do dec(j);
    if i<=j then
    begin
      k:=s[i]; s[i]:=s[j]; s[j]:=k;
      k:=t[i]; t[i]:=t[j]; t[j]:=k;
      k:=w[i]; w[i]:=w[j]; w[j]:=k;
      k:=b[i]; b[i]:=b[j]; b[j]:=k;
      inc(i); dec(j);
    end;
  end;
  if j>ll then sort(ll,j);
  if i<rr then sort(i,rr);
end;
 
function find(i:longint):longint;
begin
  if f[i]<>i then f[i]:=find(f[i]);
  find:=f[i];
end;
 
procedure dfs(i,dd:longint);
var b,p:longint;
begin
  b:=edge[i]; f[i]:=i; y[i]:=dd;
  while b<>0 do
  begin
    p:=point[b];
    if f[p]=0 then
    begin
      dfs(p,dd+1); f[p]:=i; ma[p]:=i; o[p]:=b;
    end;
    b:=next[b];
  end;
  b:=ed[i];
  while b<>0 do
  begin
    p:=po[b];
    if (i=s[p])and(f[t[p]]>0) then
      lca[p]:=find(t[p])
    else if (i=t[p])and(f[s[p]]>0) then
      lca[p]:=find(s[p]);
    b:=ne[b];
  end;
end;
 
begin
  assign(input,'1.in'); reset(input);
  assign(output,'2.out'); rewrite(output);
  read(n,m);
  for i:=1 to m do
  begin
    read(s[i],t[i],w[i]); b[i]:=i;
  end;
  sort(1,m);
  for i:=1 to n do f[i]:=i;
  for i:=1 to m do
  begin
    f1:=find(s[i]); f2:=find(t[i]); d[b[i]]:=i;
    if f1<>f2 then
    begin
      f[f1]:=f2; inc(e); inc(ans,w[i]); pos[i]:=e;
      next[e]:=edge[s[i]]; edge[s[i]]:=e; point[e]:=t[i];
      next[-e]:=edge[t[i]]; edge[t[i]]:=-e; point[-e]:=s[i];
    end
    else begin
      inc(ee); ne[ee]:=ed[s[i]]; ed[s[i]]:=ee; po[ee]:=i;
      inc(ee); ne[ee]:=ed[t[i]]; ed[t[i]]:=ee; po[ee]:=i;
    end;
  end;
 
  fillchar(f,sizeof(f),0);
  dfs(1,1);
  fillchar(g,sizeof(g),$ff);
  for i:=1 to n do f[i]:=i;
  for i:=1 to m do
  begin
    if pos[i]>0 then continue;
    j:=find(s[i]);
    while (y[j]>y[lca[i]]) do
    begin
      g[o[j]]:=w[i]; f[j]:=find(ma[j]);
      j:=f[ma[j]];
    end;
    j:=find(t[i]);
    while (y[j]>y[lca[i]]) do
    begin
      g[o[j]]:=w[i]; f[j]:=find(ma[j]);
      j:=f[ma[j]];
    end;
  end;
  read(task);
  for task:=1 to task do
  begin
    read(k); k:=d[k];
    if pos[k]=0 then writeln(ans)
    else
      if g[pos[k]]>0 then writeln(ans-w[k]+g[pos[k]])
      else if g[-pos[k]]>0 then writeln(ans-w[k]+g[-pos[k]])
      else writeln('Not connected');
  end;
  close(input); close(output);
end.


