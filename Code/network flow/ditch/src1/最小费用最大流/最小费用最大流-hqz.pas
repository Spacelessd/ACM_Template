const inf=100000000;

type re=record
      x,y,f,w,next:longint;
     end;

var
 v:array[0..400000] of re;
 d,q,f,son:array[0..400000] of longint;
 inq:array[0..400000] of boolean;
 s,t,n,m,tot,minflow,mincost,i,j,a,b,c,maxflow:longint;

procedure add(x,y,w,c:longint);
begin
 v[tot].f:=c;
 v[tot].next:=son[x]; son[x]:=tot;
 v[tot].x:=x;
 v[tot].y:=y;
 v[tot].w:=w;
 inc(tot);
end;

procedure addedge(x,y,w,c:longint);
begin
 add(x,y,w,c);
 add(y,x,-w,0);
end;

function spfa:boolean;
var x,p,head,tail,i,j:longint;
begin
 head:=0; tail:=1;
 fillchar(inq,sizeof(inq),false);
 for i:=0 to n+2 do d[i]:=inf;
 d[s]:=0; inq[s]:=true;
 f[s]:=-1; q[tail]:=s;
 while tail<>head do
  begin
   inc(head);
   x:=q[head];
   inq[x]:=false;
   p:=son[x];
   while p<>-1 do
    begin
     if (v[p].f>0) and (d[x]+v[p].w<d[v[p].y]) then
      begin
       d[v[p].y]:=d[x]+v[p].w;
       f[v[p].y]:=p;
       if not inq[v[p].y] then
        begin
         inc(tail); q[tail]:=v[p].y;
         inq[v[p].y]:=true;
        end;
      end;
    p:=v[p].next;
   end;
 end;
 if d[t]<inf then exit(true) else exit(false);
end;

procedure solve;
var p,i:longint;
begin
 minflow:=inf;
 p:=f[t];
 while p<>-1 do
  begin
   if minflow>v[p].f then minflow:=v[p].f;
   p:=f[v[p].x];
  end;
 p:=f[t];
 maxflow:=maxflow+minflow;
 while p<>-1 do
  begin
   v[p].f:=v[p].f-minflow;
   v[p xor 1].f:=v[p xor 1].f+minflow;
   mincost:=mincost+v[p].w*minflow;
   p:=f[v[p].x];
  end;
end;

begin
 readln(n,m);
 fillchar(son,sizeof(son),255);
 for i:=1 to m do
  begin
   readln(a,b,c);
   addedge(a,b,c,1);
   addedge(b,a,c,1);
  end;
 s:=0;
 t:=n+1;
 addedge(s,1,0,2);
 addedge(n,t,0,2);
 while spfa do
  solve;
 writeln(mincost,' ',maxflow);
end.
