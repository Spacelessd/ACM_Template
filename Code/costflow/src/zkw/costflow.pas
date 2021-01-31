const maxn=20010; maxm=1000010;
type gtp=record y,d,c,op,next:longint; end;
//========================================================
var n,m,tot,st,ed,ans:longint;
    g:array[0..maxm] of gtp;
    first,now,dis:array[0..maxn] of longint;
    v:array[0..maxn] of boolean;
//========================================================
function min(a,b:longint):longint;
begin
 if a>b then exit(b) else exit(a);
end;
//========================================================
procedure add(x,y,d,c,t:longint); {存边表}
begin
 inc(tot);
 g[tot].y:=y; g[tot].d:=d; g[tot].c:=c;
 g[tot].op:=tot+t; g[tot].next:=first[x]; first[x]:=tot;
end;
//========================================================
procedure init;
var i,x,y,d,c:longint;
begin
 fillchar(first,sizeof(first),0);
 readln(n,m); tot:=0; st:=1; ed:=n; ans:=0;
 for i:=1 to m do
 begin
  readln(x,y,d,c); {x点y点，容量，费用}
  add(x,y,d,c,1); add(y,x,0,-c,-1); {正反向都存}
 end;
end;
//========================================================
function aug(x,flow:longint):longint; {寻找增广路}
var y,t,tmp:longint;
begin
 if x=ed then {找到增广路，增加流量}
 begin
  inc(ans,flow*dis[st]);
  exit(flow);
 end;
 t:=now[x]; v[x]:=true;
 while t<>0 do
 begin
  y:=g[t].y;
  if (g[t].d>0)and(not v[y])and(dis[x]=dis[y]+g[t].c) then {满足容量、未被访问（这里是一个优化）、距离标号关系}
  begin
   tmp:=aug(y,min(g[t].d,flow)); {继续增广}
   if tmp>0 then {若增广成功}
   begin
    dec(g[t].d,tmp); inc(g[g[t].op].d,tmp); {更新容量值}
    now[x]:=t; {更新当前弧}
    exit(tmp);
   end;
  end;
  t:=g[t].next;
 end;
 now[x]:=0; {小优化}
 exit(0);
end;
//========================================================
function modlabel:boolean; {修改距离标号}
var tmp,y,i,t:longint;
begin
 tmp:=maxlongint;
 for i:=1 to n do
 if v[i] then {若某边为true，则距离标号已经不合格}
 begin
  t:=first[i];
  while t<>0 do
  begin
   y:=g[t].y;
   if (g[t].d>0)and(not v[y])and(dis[y]+g[t].c-dis[i]<tmp) then tmp:=dis[y]+g[t].c-dis[i]; {取最小值}
   t:=g[t].next;
  end;
 end;
 if tmp=maxlongint then exit(true); {无法修复距离标号}
 for i:=1 to n do {若能修复，则修复距离标号}
 if v[i] then
 begin
  inc(dis[i],tmp);
  v[i]:=false;
 end;
 exit(false);
end;
//========================================================
procedure main;
var i:longint;
begin
 fillchar(dis,sizeof(dis),0);
 repeat
  for i:=1 to n do now[i]:=first[i];
  while aug(st,maxlongint)>0 do fillchar(v,sizeof(v),false); {若能增广则无限增广}
 until modlabel; {直到无法修复距离标号}
 writeln(ans);
end;
//========================================================
begin
 assign(input,'costflow.in'); reset(input);
 assign(output,'costflow.out'); rewrite(output);
 init;
 main;
 close(input); close(output);
end.
