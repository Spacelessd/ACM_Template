program otoci;
//
const
	maxn=30000;
	oo=19920905;
	maxpro=100000000;
//
type
	node=record
		l,r,num,fa,tot:longint;
		flip:boolean;
	end;
//
var
	n,m,count:longint;
	w:array[0..maxn] of longint;
	poi:array[0..maxn] of longint;
	comfa:array[0..maxn] of longint;
	pre:array[0..maxn] of longint;
	t:array[0..maxn] of node;
//
procedure init;
var i:longint;
begin
	readln(n);
	w[0]:=0; t[0].tot:=0; poi[0]:=0;
	for i:=1 to n do read(w[i]); readln;
end;
//
procedure maketree(x:longint);
begin
	inc(count);
	with t[count] do
	begin
		l:=0; r:=0; tot:=w[x]; pre[x]:=0;
		num:=x; fa:=0; poi[x]:=count; flip:=false;
	end;
end;
//
procedure flip(x:longint);
var tmp:longint;
begin
	with t[x] do
	begin
		tmp:=l; l:=r; r:=tmp; flip:=false;
		if l>0 then t[l].flip:=not t[l].flip;
		if r>0 then t[r].flip:=not t[r].flip;
	end;
end;
//
procedure update(x:longint);
begin
	with t[x] do
	begin
		tot:=t[l].tot+t[r].tot+w[x];
	end;
end;
//
procedure turn_l(x:longint);
var y:longint;
begin
	y:=t[x].fa;
	t[y].r:=t[x].l;
	if t[x].l<>0 then t[t[x].l].fa:=y;
	t[x].fa:=t[y].fa;
	if t[y].fa<>0 then
	begin
		if y=t[t[y].fa].l then t[t[y].fa].l:=x
							else t[t[y].fa].r:=x;
	end;
	t[x].l:=y; t[y].fa:=x;
	update(y); update(x);
end;
procedure turn_r(x:longint);
var y:longint;
begin
	y:=t[x].fa;
	t[y].l:=t[x].r;
	if t[x].r<>0 then t[t[x].r].fa:=y;
	t[x].fa:=t[y].fa;
	if t[y].fa<>0 then
	begin
		if y=t[t[y].fa].l then t[t[y].fa].l:=x
							else t[t[y].fa].r:=x;
	end;
	t[x].r:=y; t[y].fa:=x;
	update(y); update(x);
end;
//
procedure splay(x:longint);
var y:longint;
begin
	while t[x].fa<>0 do
	begin
		if t[t[x].fa].fa=0 then
		begin
			if t[t[x].fa].flip then flip(t[x].fa);
			if t[x].flip then flip(x);
			if x=t[t[x].fa].l then turn_r(x)
								else turn_l(x);
			exit;
		end;
		if t[t[t[x].fa].fa].flip then flip(t[t[x].fa].fa);
		if t[t[x].fa].flip then flip(t[x].fa);
		if t[x].flip then flip(x);
		if t[x].fa=t[t[t[x].fa].fa].l then
		begin
			if x=t[t[x].fa].l then
			begin
				turn_r(t[x].fa);
				turn_r(x);
			end else
			begin
				turn_l(x);
				turn_r(x);
			end;
		end else
		begin
			if x=t[t[x].fa].r then
			begin
				turn_l(t[x].fa);
				turn_l(x);
			end else
			begin
				turn_r(x);
				turn_l(x);
			end;
		end;
	end;
end;
//
function findroot(x:longint):longint;
begin
	if t[x].flip then flip(x);
	if t[x].l=0 then exit(x) else exit(findroot(t[x].l));
end;
//
procedure access(x:longint);
var y:longint;
begin
	y:=0;
	repeat
		splay(poi[x]);
		if t[x].flip then flip(x);
		if t[poi[x]].r>0 then begin t[t[poi[x]].r].fa:=0; pre[findroot(t[poi[x]].r)]:=x; end;
		t[poi[x]].r:=poi[y]; if poi[y]>0 then t[poi[y]].fa:=poi[x]; update(poi[x]);
		pre[y]:=0;
		y:=x;
		x:=pre[findroot(x)];
	until x=0;
end;
//
function find(x:longint):longint;
var j,root,tmp:longint;
begin
	j:=x;
	while comfa[j]<>j do j:=comfa[j];
	root:=j;
	j:=x;
	while comfa[j]<>j do
	begin
		tmp:=comfa[j];
		comfa[j]:=root;
		j:=tmp;
	end;
	find:=root;
end;
//
function lca(x,y:longint):longint;
var tmp,root,fi:longint;
begin
	access(x); root:=find(x);
	splay(poi[y]);
	fi:=findroot(y);
	while fi<>root do
	begin
		y:=pre[fi];
		splay(y); fi:=findroot(y);
	end;
	exit(y);
end;
//
procedure work;
var i,j,x,y,z,tmp1,tmp2,tmp3:longint;
	ch:char;
begin
	//randomize;
	count:=0; for i:=1 to n do maketree(i);
	for i:=1 to n do comfa[i]:=i;
	readln(m);
	for i:=1 to m do
	begin
		read(ch);
		case ch of
			'b':begin
					for j:=1 to 5 do read(ch);
					readln(x,y);
					if find(x)=find(y) then writeln('no')
					else
					begin
						comfa[find(x)]:=find(y);
						access(x); splay(x);
						t[x].flip:=not t[x].flip;
						pre[x]:=y;
						writeln('yes');
					end;
				end;
			'p':begin
					for j:=1 to 7 do read(ch);
					readln(x,y);
					splay(poi[x]);
					t[poi[x]].tot:=t[poi[x]].tot+y-w[x];
					w[x]:=y;
				end;
			'e':begin
					for j:=1 to 8 do read(ch);
					readln(x,y);
					if find(x)<>find(y) then
					begin
						writeln('impossible');
						continue;
					end;
					access(x); splay(x);
					tmp1:=t[poi[x]].tot;
					access(y); splay(y);
					tmp2:=t[poi[y]].tot;
					z:=lca(x,y); access(z); splay(z);
					tmp3:=t[poi[z]].tot;
					writeln(tmp1+tmp2-2*tmp3+w[z]);
				end;
		end;
	end;
end;
//
begin
	assign(input,'otoci.in');reset(input);
	assign(output,'otoci.out');rewrite(output);
	init;
	work;
	close(input);close(output);
end.


