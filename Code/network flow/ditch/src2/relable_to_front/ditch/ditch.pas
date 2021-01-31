program relable_to_front;

const
  maxm=1000010;
  maxn=3010;
type
  edgetype=record
    b,e:longint;
  end;
var
  head,ans,lk,s,t,n,m:longint;
  edge:array[1..maxm]of edgetype;
  f,c,cf:array[1..maxn,1..maxn]of longint;
  pre,next,l,st,e,h:array[-1..maxn]of longint;
  procedure sort;
  var
    i,j:longint;
    temp:edgetype;
  begin
    for i:=1 to m-1 do
      for j:=i+1 to m do
        if edge[i].b>edge[j].b then
        begin
          temp:=edge[i];
          edge[i]:=edge[j];
          edge[j]:=temp;
        end;
  end;

  procedure init;{输入数据}
  var
    temp,i,j,a,b:longint;
  begin
    assign(input,'ditch.in');reset(input);
    fillchar(c,sizeof(c),0);
    fillchar(st,sizeof(st),0);
    readln(m,n);j:=0;s:=1;t:=n;
    for i:=1 to m do
    begin
      read(a,b);readln(c[a,b]);
      inc(j);
      edge[j].b:=a;edge[j].e:=b;
    end;
    for i:=1 to m do
    begin
      edge[i+m]:=edge[i];
      temp:=edge[i+m].b;
      edge[i+m].b:=edge[i+m].e;
      edge[i+m].e:=temp;
    end;
    m:=m*2;{构造逆边}
     close(input);
    sort;
    for i:=1 to m do
      if st[edge[i].b]=0 then st[edge[i].b]:=i;
    cf:=c;
  end;

  function min(a,b:longint):longint;
  begin
    if a>b then exit(b) else exit(a);
  end;

  procedure push(u,v:longint);{压入}
  var
    df:longint;
  begin
    df:=min(cf[u,v],e[u]);
    f[u,v]:=f[u,v]+df;
    f[v,u]:=-f[u,v];
    cf[u,v]:=cf[u,v]-df;
    cf[v,u]:=cf[v,u]+df;
    e[u]:=e[u]-df;
    e[v]:=e[v]+df;
  end;

  procedure relable(u:longint);{重标记}
  var
    i,j:longint;
  begin
    i:=st[u];j:=maxlongint;
    while edge[i].b=u do
    begin
      if cf[edge[i].b,edge[i].e]>0 then j:=min(j,h[edge[i].e]);
      inc(i);
    end;
    h[u]:=j+1;
  end;

  procedure initialize; {初始化}
  var
    i,u:longint;
  begin
    fillchar(h,sizeof(h),0);
    fillchar(e,sizeof(e),0);
    fillchar(f,sizeof(f),0);
    h[s]:=n;
    i:=st[s];
    while edge[i].b=s do
    begin
      u:=edge[i].e;
      f[s,u]:=c[s,u];
      cf[s,u]:=0;cf[u,s]:=c[s,u];
      f[u,s]:=-f[s,u];
      e[u]:=c[s,u];
      e[s]:=e[s]-c[s,u];
      inc(i);
    end;
  end;

  procedure discharge(u:longint);{排除点}
  var
    v,k:longint;
  begin
    k:=st[u];
    while e[u]>0 do
    begin
      v:=edge[k].e;
      if edge[k].b<>u then
      begin
        relable(u);
        k:=st[u];
      end
      else
        if (cf[u,v]>0) and (h[u]=h[v]+1) then push(u,v)
      else inc(k);
    end;
  end;

  procedure initialize_l; {构造L表}
  var
    i:longint;
  begin
    lk:=0;
    for i:=1 to n do
      if (i<>s)and(i<>t) then
      begin
        inc(lk);
        l[lk]:=i;
        if lk=1 then head:=i;
      end;
    for i:=1 to lk-1 do next[l[i]]:=l[i+1];
    next[l[lk]]:=-1;
    for i:=2 to lk do pre[l[i]]:=l[i-1];
    pre[l[1]]:=-1;
    next[-1]:=l[1];
    pre[-1]:=l[lk];
  end;

  procedure move(u:longint);{将U元素移至表头}
  begin
    if head<>u then
    begin
      next[pre[u]]:=next[u];
      pre[next[u]]:=pre[u];
      next[u]:=head;
      pre[head]:=u;
      head:=u;
      pre[u]:=-1;
    end;
  end;

  procedure maxflow;{主程序}
  var
    u,oh:longint;
  begin
    initialize;
    initialize_l;
    u:=head;
    while u<>-1 do
    begin
      oh:=h[u];
      discharge(u);
      if h[u]>oh then move(u);
      u:=next[u];
    end;
  end;

  procedure calc;{计算最大流}
  var
    i:longint;
  begin
    for i:=1 to n do
      ans:=ans+f[i,t];
  end;

  procedure print;{输出}
  begin
    assign(output,'ditch.out');rewrite(output);
    writeln(ans);
    close(output);
  end;

begin
  init;
  maxflow;
  calc;
  print;
end.

//begin
//end.


