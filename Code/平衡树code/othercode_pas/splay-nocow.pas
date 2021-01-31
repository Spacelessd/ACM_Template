const	maxn=500000;
var	stack,l,r,n,s,t,f:array[0..maxn]of longint;
	tt,top,root,i,q,c,x:longint;
 
//Splay(x,S);
procedure zig(var x:longint);
var	y:longint;
begin
y:=l[x]; l[x]:=r[y]; r[y]:=x;
f[y]:=f[x]; f[x]:=y;
if l[x]<>0 then f[l[x]]:=x;
s[y]:=s[x]; s[x]:=s[l[x]]+s[r[x]]+t[x];
x:=y;
end;
procedure zag(var x:longint);
var	y:longint;
begin
y:=r[x]; r[x]:=l[y]; l[y]:=x;
f[y]:=f[x]; f[x]:=y;
if r[x]<>0 then f[r[x]]:=x;
s[y]:=s[x]; s[x]:=s[l[x]]+s[r[x]]+t[x];
x:=y;
end;
procedure splay(x:longint; var S:longint);
begin
while f[x]<>f[S] do
	if l[f[x]]=x
		then if f[x]=S then zig(S)
			else if l[f[f[x]]]=f[x]
				then zig(l[f[f[x]]])
				else zig(r[f[f[x]]])
		else if f[x]=S then zag(S)
			else if l[f[f[x]]]=f[x]
				then zag(l[f[f[x]]])
				else zag(r[f[f[x]]]);
end;//此处的Splay操作退化了！
 
//New and Dispose a Node
procedure newnode(var x:longint);
begin
if top=0
	then begin
	inc(tt);
	x:=tt;
	end
	else begin
	x:=stack[top];
	dec(top);
	end;
end;
procedure disnode(x:longint);
begin
inc(top);
stack[top]:=x;
end;
 
//FindIt FindMax FindMin
function find(v:longint):boolean;
var	i:longint;
begin
i:=root;
while i<>0 do
	begin
	if n[i]=v
		then begin
		splay(i,root);
		exit(true);
		end;
	if v<n[i] then i:=l[i]
		else i:=r[i];
	end;
find:=false;
end;
function max(var x:longint):longint;
var	i:longint;
begin
i:=x;
while r[i]<>0 do
	i:=r[i];
max:=n[i];
splay(i,x);
end;
function min(var x:longint):longint;
var	i:longint;
begin
i:=x;
while l[i]<>0 do
	i:=l[i];
min:=n[i];
splay(i,x);
end;
 
//Insert Delete Union
procedure insert(v:longint);
var	i,j,x:longint;
begin
if find(v)
	then begin
	inc(t[root]);
	inc(s[root]);
	end
	else begin
	newnode(x);
	f[x]:=0; l[x]:=0; r[x]:=0;
	n[x]:=v; s[x]:=1; t[x]:=1;
	if root=0
		then root:=x
		else begin
		i:=root; j:=root;
		while i<>0 do
			begin
			inc(s[i]); j:=i;
			if v<n[i] then i:=l[i]
				else i:=r[i];
			end;
		if v<n[j] then l[j]:=x
			else r[j]:=x;
		f[x]:=j;
		splay(x,root);
		end;
	end;
end;
function union(var x,y:longint):longint;
begin
if x=0
	then begin
	f[y]:=0;
	exit(y);
	end;
max(x);
f[x]:=0; r[x]:=y; f[y]:=x;
s[x]:=s[l[x]]+s[r[x]]+t[x];
union:=x;
end;
procedure delete(v:longint);
var	temp:longint;
begin
if find(v)
	then if t[root]>1
		then begin
		dec(t[root]);
		dec(s[root]);
		end
		else begin
		temp:=union(l[root],r[root]);
		disnode(root);
		root:=temp;
		end;
end;
 
//Rank Select
function rank(v:longint):longint;
var	i,j:longint;
begin
i:=root; j:=0;
while i<>0 do
	if v<=n[i]
		then i:=l[i]
		else begin
		j:=j+s[l[i]]+t[i];
		i:=r[i];
		end;
rank:=j+1;
end;
function select(k:longint):longint;
var	i:longint;
begin
if k>s[root]
	then exit(-1);
i:=root;
while true do
	begin
	if (s[l[i]]<k)and(k<=s[l[i]]+t[i])
		then exit(n[i]);
	if k<=s[l[i]]
		then i:=l[i]
		else begin
		k:=k-s[l[i]]-t[i];
		i:=r[i];
		end;
	end;
end;
 
//Pred Succ
function pred(v:longint):longint;
var	flag:boolean;
begin
flag:=not find(v);
if flag then insert(v);
if l[root]=0
	then pred:=v
	else pred:=max(l[root]);
if flag then delete(v);
end;
function succ(v:longint):longint;
var	flag:boolean;
begin
flag:=not find(v);
if flag then insert(v);
if r[root]=0
	then succ:=v
	else succ:=min(r[root]);
if flag then delete(v);
end;
 
//Main
begin
assign(input,'bst.in'); reset(input);
assign(output,'bst1.out'); rewrite(output);
readln(q);
s[0]:=0; t[0]:=0;
tt:=0; root:=0;
for i:=1 to q do
	begin
	readln(c,x);
	case c of
		1:insert(x);
		2:delete(x);
		3:writeln(find(x));
		4:writeln(rank(x));
		5:writeln(select(x));
		6:writeln(pred(x));
		7:writeln(succ(x));
		end;
	end;
close(input); close(output);
end.