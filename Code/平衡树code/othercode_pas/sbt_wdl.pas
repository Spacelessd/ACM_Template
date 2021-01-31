{$inline on}
program CQF_SBT;
const maxn=2000000;
var key,s,left,right,a,b:array[0..maxn] of longint;
tt,q:longint;

procedure init;
begin
readln(q);
for q:=1 to q do
readln(a[q],b[q]);
end;

procedure work;
var t,k:longint;

procedure right_rotate(var t:longint);inline;{右旋操作}
begin
k:=left[t];
left[t]:=right[k];
right[k]:=t;
s[k]:=s[t];
s[t]:=s[left[t]]+s[right[t]]+1;
t:=k;
end;
procedure left_rotate(var t:longint);inline;{左旋操作}
begin
k:=right[t];
right[t]:=left[k];
left[k]:=t;
s[k]:=s[t];
s[t]:=s[left[t]]+s[right[t]]+1;
t:=k;
end;

procedure maintain(var t:longint;flag:boolean);inline;{最主要的维护操作}
begin
if flag=false then{左子树被插入导致的不平衡}
if s[left[left[t]]]>s[right[t]] then{左子树的左子树比右子树大}
right_rotate(t)
else
if s[right[left[t]]]>s[right[t]] then begin{左子树的右子树比右子树大}
left_rotate(left[t]);
right_rotate(t);
end
else
exit{当前是平衡的，退出}
else
if s[right[right[t]]]>s[left[t]] then{右子树的右子树比左子树大}
left_rotate(t)
else
if s[left[right[t]]]>s[left[t]] then begin{右子树的左子树比左子树大}
right_rotate(right[t]);
left_rotate(t);
end
else
exit;
maintain(left[t],false);{这两句语句大家可以自己考虑一下，其实画图一下并简单分析就可以得出结论了}
maintain(right[t],true);
maintain(t,true);{维护根的平衡}
maintain(t,false);
end;

procedure insert(var t,v:longint);inline;{插入操作}
begin
if t=0 then begin{如果当前点为空那么插入}
inc(tt);
t:=tt;
key[t]:=v;
s[t]:=1;
left[t]:=0;
right[t]:=0;
end
else begin{当前点不为空}
inc(s[t]);{增加体积}
if v<key[t] then
insert(left[t],v)
else
insert(right[t],v);
maintain(t,v>=key[t]);{维护注意，flag=TRUE则维护右子树，否则维护左子树被插入的情况}
end;
end;
function delete(var t:longint;v:longint):longint;inline;{删除操作}
begin
dec(s[t]);{将当前点的size减小，要删除元素}
if (v=key[t])or(v<key[t])and(left[t]=0)or(v>key[t])and(right[t]=0) then begin{如果当前点是要删除点}
delete:=key[t];{记录删除的点是什么}
if (left[t]=0)or(right[t]=0) then{如果左右子树有一颗是空的}
t:=left[t]+right[t]{将其中的那棵非空树表示为t}
else
key[t]:=delete(left[t],key[t]+1){删除左子树中最大的，然后用它做根};
end
else
if v<key[t] then{分别从左子树中删或右子树中删}
delete:=delete(left[t],v)
else
delete:=delete(right[t],v);
end;

function find(var t,v:longint):boolean;inline;{查找操作}
begin
if t=0 then
exit(false);
if v<key[t] then
find:=find(left[t],v)
else
find:=(key[t]=v)or find(right[t],v);
end;
function rank(var t,v:longint):longint;inline;{求元素的秩}
begin
if t=0 then
exit(1);
if v<=key[t] then
rank:=rank(left[t],v)
else
rank:=s[left[t]]+1+rank(right[t],v);
end;
function select(var t:longint;k:longint):longint;inline;{输出第k大}
begin
if k=s[left[t]]+1 then
exit(key[t]);
if k<=s[left[t]] then
select:=select(left[t],k)
else
select:=select(right[t],k-1-s[left[t]]);
end;
function pred(var t,v:longint):longint;inline;{找前驱}
begin
if t=0 then
exit(v);
if v<=key[t] then
pred:=pred(left[t],v)
else begin
pred:=pred(right[t],v);
if pred=v then
pred:=key[t];
end;
end;
function succ(var t,v:longint):longint;inline;{找后继}
begin
if t=0 then
exit(v);
if key[t]<=v then
succ:=succ(right[t],v)
else begin
succ:=succ(left[t],v);
if succ=v then
succ:=key[t];
end;
end;

begin{work}
tt:=0;
t:=0;
s[0]:=0;
for q:=1 to q do
case a[q] of
1:insert(t,b[q]);
2:delete(t,b[q]);
3:writeln(find(t,b[q]));
4:writeln(rank(t,b[q]));
5:writeln(select(t,b[q]));
6:writeln(pred(t,b[q]));
7:writeln(succ(t,b[q]));
end;
end;

begin
assign(input,'bst.in');
assign(output,'bst.out');
reset(input);
rewrite(output);
init;
work;
close(input);
close(output);
end.


