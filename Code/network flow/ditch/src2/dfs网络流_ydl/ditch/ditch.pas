{
ID:yudingl2
PROG:ditch
LANG:PASCAL
}

var
 n,m,i,j,x,y,z,ans,min:longint;
 a:array[1..2000,1..2000] of longint;
 pre:array[1..2000] of longint;
 f:array[1..2000] of boolean;
 flag:boolean;

procedure dfs(x:longint);
var i:longint;
begin
 if x=n then
  begin
   flag:=false;
   exit;
  end;
 f[x]:=false;
 for i:=1 to n do
  begin
   if f[i] and (a[x,i]<>0) and flag then
    begin
     pre[x]:=i;
     dfs(i);
     if not flag then exit;
    end;
   if not flag then exit;
  end;
end;

procedure network_flow;
var i,j,k,L:longint;
begin
 while true do
  begin
   flag:=true;
   fillchar(f,sizeof(f),true);
   fillchar(pre,sizeof(pre),0);
   dfs(1);
   if flag then break;
   min:=maxlongint;
   k:=1;L:=pre[k];
   while L<>0 do
    begin
     if a[k,L]<min then min:=a[k,L];
     k:=L;L:=pre[k];
    end;
   k:=1;L:=pre[k];
   while L<>0 do
    begin
     a[k,L]:=a[k,L]-min;
     a[L,k]:=a[L,k]+min;
     k:=L;L:=pre[k];
    end;
   ans:=ans+min;
  end;
end;

begin
 assign(input,'ditch.in');reset(input);
 assign(output,'ditch.out');rewrite(output);
 randomize;
 readln(m,n);
 for i:=1 to m do
  begin
   readln(x,y,z);
   inc(a[x,y],z);
//inc(a[y,x],z);
  end;
for i:=1 to n do a[i][i]:=0;
{for i:=1 to n do
  for j:=1 to n do
  if (a[i][j]>0)and(a[j][i]>0)then writeln('wa');}
 network_flow;
 writeln(ans);
 close(input);close(output);
end.
