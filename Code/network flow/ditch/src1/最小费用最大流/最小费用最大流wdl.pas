type
 edge=record
  from,link,next,cost,cap:longint;
 end;

var
 n,m,k,e,w,ans,len,flow,i,j,p:longint;
 f:array[1..100000] of longint;
 d,b,son,pre:array[1..20000] of longint;
 v:array[1..50000] of edge;

function min(x,y:longint):longint;
begin
 if x<y then exit(x) else exit(y);
end;

function num(x,y,z:longint):longint;
begin
 exit((x-1)*m+y+n*m*z);
end;

procedure add(x,y,z,c:longint);
begin
 inc(e);
 v[e].from:=x;v[e].link:=y;v[e].next:=son[x];
 son[x]:=e;v[e].cap:=z;v[e].cost:=c;
end;

procedure build(x,y,z,c:longint);
begin
 add(x,y,z,c);
 add(y,x,0,-c);
end;

function spfa(s:longint):longint;
var st,en,p,q,i:longint;
begin
 fillchar(d,sizeof(d),$7F);
 fillchar(f,sizeof(f),0);
 fillchar(b,sizeof(b),0);
 d[s]:=0;f[1]:=s;b[s]:=1;
 st:=0;en:=1;
 while st<en do
  begin
   inc(st);p:=f[st];b[p]:=0;
   i:=son[p];
   while i<>0 do
    begin
     q:=v[i].link;
     if (v[i].cap>0)and(d[p]+v[i].cost<d[q]) then
      begin
       d[q]:=d[p]+v[i].cost;
       pre[q]:=i;
       if b[q]=0 then
        begin inc(en);b[q]:=1;f[en]:=q; end;
      end;
     i:=v[i].next;
    end;
  end;
 exit(d[num(n,m,1)]);
end;

begin
 readln(n,k);
 if k=0 then
  begin
   writeln(0);
   halt;
  end;
 m:=n;
 e:=0;ans:=0;
 for i:=1 to n do
  for j:=1 to m do
   begin
    read(w);
    if (i=1)and(j=1) then
     begin
      build(num(1,1,0),num(1,1,1),k,0);
      build(num(1,1,1),num(1,2,0),maxlongint,0);
      build(num(1,1,1),num(2,1,0),maxlongint,0);
      ans:=ans-w;continue;
     end;
    if (i=n)and(j=m) then
     begin
      build(num(n,m,0),num(n,m,1),k,0);
      ans:=ans-w;break;
     end;
    build(num(i,j,0),num(i,j,1),1,-w);
    build(num(i,j,0),num(i,j,1),maxlongint,0);
    if (i<>n) then build(num(i,j,1),num(i+1,j,0),maxlongint,0);
    if (j<>m) then build(num(i,j,1),num(i,j+1,0),maxlongint,0);
   end;
 while true do
  begin
   len:=spfa(1);
   if len>1000000000 then break;
   flow:=maxlongint;
   p:=num(n,m,1);
   while p<>1 do
    begin
     flow:=min(flow,v[pre[p]].cap);
     p:=v[pre[p]].from;
    end;
   p:=num(n,m,1);
   while p<>1 do
    begin
     dec(v[pre[p]].cap,flow);
     if pre[p] mod 2=1 then inc(v[pre[p]+1].cap,flow)
                       else inc(v[pre[p]-1].cap,flow);
     p:=v[pre[p]].from;
    end;
   inc(ans,flow*len);
  end;
 writeln(-ans);
end.