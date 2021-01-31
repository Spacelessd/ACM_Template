var
  o,v:array[0..1600] of boolean;
  f,s,d,dis:array[0..1600] of longint;
  next,p,c,w:array[-20000..20000] of longint;
  n,m,i,j,t,tt,ft,ff,st,sf,ans,imp,new,flow,x1,x2,x3,x4:longint;

procedure link(i,j,k,l:longint);
begin
  inc(t);next[t]:=d[i];d[i]:=t;p[t]:=j;c[t]:=k;w[t]:=l;
  next[-t]:=d[j];d[j]:=-t;p[-t]:=i;w[-t]:=-l;
end;

function dfs(i,flow:longint):longint;
var j,k,l,min:longint;
begin
  if i=tt then begin
    inc(ans,dis[i]*flow);exit(flow);
  end;
  k:=s[i];j:=p[k];dfs:=0;
  o[i]:=true;v[i]:=true;
  while k<>0 do begin
    l:=dis[i]+w[k]-dis[j];min:=flow;
    if c[k]<min then min:=c[k];
    if (min>0)and(l<f[j]) then f[j]:=l;
    if (min>0)and(l=0)and not o[j] then begin
      l:=dfs(j,min);
      inc(dfs,l);dec(flow,l);
      dec(c[k],l);inc(c[-k],l);
    end;
    if flow=0 then break;
    s[i]:=next[s[i]];
    k:=s[i];j:=p[k];
  end;
  o[i]:=false;
end;

begin
  assign(input,'costflow.in');reset(input);
  assign(output,'costflow.out');rewrite(output);
  readln(n,m);
  for i:=1 to m do begin
    read(x1,x2,x3,x4);
	link(x1,x2,x3,x4);
  end;
  repeat
    for i:=1 to tt do s[i]:=d[i];
    fillchar(v,sizeof(v),false);
    fillchar(f,sizeof(f),1);
    inc(flow,dfs(1,1<<20));
    imp:=maxint;
    for i:=1 to tt do
      if not v[i] and (f[i]<imp) then imp:=f[i];
    for i:=1 to tt do if not v[i] then inc(dis[i],imp);
  until imp=maxint;
  writeln(ans);
  close(output);close(input);
end.