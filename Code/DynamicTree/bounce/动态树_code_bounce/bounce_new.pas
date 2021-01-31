{$inline on}
{$M 1000000000}
type
  splaya=record
    l,r,key,size,p,min,delta,rev:longint;
    end;
var
  a:array[0..1000000]of splaya;
  father:array[0..1000000]of longint;
  n,m,x,y,z,ll,i,j,k,op:longint;

  procedure update(x:longint);inline;   //每次旋转完更新节点的两个域
    begin
    a[x].size:=a[a[x].l].size+a[a[x].r].size+1;
    end;


procedure zig(x:longint);inline;   //右旋
var
	y,z:longint;
begin
	y:=a[x].p;
	z:=a[y].p;
	if a[z].l=y then a[z].l:=x
		else a[z].r:=x;
	a[x].p:=z;
	a[y].p:=x;
	a[y].l:=a[x].r;
	a[x].r:=y;
	a[a[y].l].p:=y;
	update(y);
end;

procedure zag(x:longint);inline;   //左旋
var
	y,z:longint;
begin
	y:=a[x].p;
	z:=a[y].p;
	if a[z].l=y then a[z].l:=x
		else a[z].r:=x;
	a[x].p:=z;
	a[y].p:=x;
	a[y].r:=a[x].l;
	a[x].l:=y;
	a[a[y].r].p:=y;
	update(y);
end;



procedure Splay(x:longint);inline;
	var
		y,z	:longint;
	begin
        if x=0 then exit;
		while a[x].p<>0 do
		begin
			y:=a[x].p;
			z:=a[y].p;
			if z=0 then
			begin
				if x=a[y].l then Zig(x) else Zag(x);
			end
			else
			begin
				if y=a[z].l then
				begin
					if x=a[y].l then
					begin
						Zig(y);
						Zig(x);
					end
					else
					begin
						Zag(x);
						Zig(x);
					end;
				end
				else
				begin
					if x=a[y].r then
					begin
						Zag(y);
						Zag(x);
					end
					else
					begin
						Zig(x);
						Zag(x);
					end;
				end;
			end;
		end;
		update(x);
	end;



  function rank(x:longint):longint;inline;
    begin
    splay(x);
    rank:=a[a[x].l].size+1;
    end;




  function split(x:longint):longint;inline;
  var
    i:longint;
    begin
    splay(x);
    if a[x].r>0 then begin
      i:=a[x].r;
      a[x].r:=0;
      a[i].p:=0;
      dec(a[x].size,a[i].size);
      split:=i;
      end
      else exit(0);
    end;



  procedure link(x,y:longint);inline;
    begin
    splay(x);
    splay(y);
    a[y].r:=x;
    inc(a[y].size,a[x].size);
    a[x].p:=y;
    end;


  function get_head(x:longint):longint;inline;
    begin
    while a[x].p>0 do x:=a[x].p;
    while a[x].l>0 do x:=a[x].l;
    splay(x);
    exit(x);
    end;


  procedure expose(x:longint);inline;
    begin
    while true do
      begin
      x:=get_head(x);
      if father[x]=0 then exit;
      split(father[x]);
      link(x,father[x]);
      end;
    end;


  function depth(x:longint):longint;inline;
    begin
    expose(x);
    exit(rank(x)-1);
    end;


  function cut(x:longint):longint;inline;
    begin
    expose(x);
    split(father[x]);
    end;


  function changefa(x,y:longint):longint;inline;
    begin
    cut(x);
    split(y);
    father[x]:=y;
    link(x,y);
    end;

  begin
  assign(input,'bounce.in');reset(input);
  assign(output,'bounce.out');rewrite(output);
  readln(n);
  for i:=1 to n do
    begin
    read(k);
    if i+k>n+1 then father[i]:=n+1
      else father[i]:=i+k;
    end;
  for i:=1 to n+1 do a[i].size:=1;

  read(m);
  for i:=1 to m do
    begin
    read(op,j);
    inc(j);
    if op=1 then begin
      writeln(depth(j));
      end;
    if op=2 then begin
      read(k);
      k:=k+j;
      if k>n+1 then k:=n+1;
      changefa(j,k);
      end;
    end;
  close(output);
  end.






