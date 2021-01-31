{$inline on}
program poj3164; const maxn=500;
var
  a,b,l,r,root,v,fa:array[0..maxn*maxn] of longint;
  o:array[0..maxn] of boolean;
  g:array[0..maxn,0..maxn] of boolean;
  x,y,c,z:array[0..maxn*maxn] of real;
  i,j,k,n,m,t,e,tmp:longint;
  ans,pre:real;
 
procedure put(i:longint);inline;
begin
  c[l[i]]:=c[l[i]]-z[i];c[r[i]]:=c[r[i]]-z[i];
  z[l[i]]:=z[l[i]]+z[i];z[r[i]]:=z[r[i]]+z[i];
  z[i]:=0;
end;
 
function find(i:longint):longint;inline;
begin if fa[i]<>i then fa[i]:=find(fa[i]);find:=fa[i] end;
 
procedure merge(var x,y:longint);inline;
begin
  if c[x]>c[y] then begin tmp:=x;x:=y;y:=tmp end;
  put(x);
  if y<>0 then begin
    merge(r[x],y);
    tmp:=r[x];r[x]:=l[x];l[x]:=tmp;
  end;
end;
 
procedure dfs(i:longint);inline;var j:longint;
begin
  if o[i] then exit else inc(t);
  o[i]:=true;
  for j:=1 to n do if g[i,j] then dfs(j);
end;
 
function circle(i:longint):boolean;inline;var j,k:longint;
begin
  fillchar(o,sizeof(o),false);
  t:=0;j:=i;o[1]:=true;
  repeat
    o[j]:=true;
    inc(t);v[t]:=j;
    j:=find(a[root[j]]);
  until o[j];
  circle:=j=i;
end;
 
begin
  while not seekeof do begin
    fillchar(g,sizeof(g),false);
    fillchar(o,sizeof(o),false);
    fillchar(root,sizeof(root),0);
    fillchar(l,sizeof(l),0);
    fillchar(r,sizeof(r),0);
    fillchar(z,sizeof(z),0);
    readln(n,m);c[0]:=1e30;t:=0;
    for i:=1 to n do readln(x[i],y[i]);
    for i:=1 to m do begin
      readln(a[i],b[i]);
      g[a[i],b[i]]:=true;
      c[i]:=sqrt(sqr(x[a[i]]-x[b[i]])+sqr(y[a[i]]-y[b[i]]));
    end;
    dfs(1);ans:=0;
    if t<>n then writeln('poor snoopy') else begin
      for i:=1 to m do if a[i]<>b[i] then begin
        j:=i;merge(root[b[i]],j);
      end;
      for i:=1 to n do fa[i]:=i;
      for i:=2 to n do if fa[i]=i then
        while circle(i) do
          for j:=1 to t do begin
            e:=root[v[j]];z[e]:=z[e]+c[e];
            ans:=ans+c[e];fa[v[j]]:=i;put(e);
            merge(r[e],l[e]);root[v[j]]:=r[e];
            if j<>1 then merge(root[i],root[v[j]]);
          end;
      for i:=2 to n do if find(i)=i then ans:=ans+c[root[i]];
      writeln(ans:0:2);
    end;
  end;
end.


