{
ID:yudingl2
PROG:ditch
LANG:PASCAL
}
type
	btp=record
		x,y,f,op,tot,next:longint;
	 end;

var
	n,m,tot:longint;
	edge:array[0..1000010] of btp; {边数}
	son,now,sumd,dis,back,pre:array[0..20010] of longint; {依次代表，初始弧，当前弧，标号总数，标号，返回值，前驱边}

procedure addit(x,y,d:longint); {和Dinic一样的增加双向边}
begin
	inc(tot);
	edge[tot].x:=x; edge[tot].y:=y; edge[tot].f:=d; edge[tot].op:=tot+1;
	edge[tot].next:=son[x]; son[x]:=tot;
	inc(tot);
	edge[tot].x:=y; edge[tot].y:=x; edge[tot].f:=0; edge[tot].op:=tot-1;
	edge[tot].next:=son[y]; son[y]:=tot;
end;

procedure init; {和Dinic一样的读入}
var i,x,y,d:longint;
begin
	tot:=0;
	fillchar(dis,sizeof(dis),0);
	fillchar(sumd,sizeof(sumd),0);
	fillchar(son,sizeof(son),0);
	fillchar(edge,sizeof(edge),0);

	readln(m,n);
	for i:=1 to m do
	  begin
		readln(x,y,d);
		addit(x,y,d);
	  end;
	now:=son; {当前弧初始化成初始弧}
end;

procedure main;
var
	i,flow,ans,t,j,tmp,min:longint;
	flag:boolean;
begin
	sumd[0]:=n;ans:=0;
	i:=1;flow:=maxlongint; {初始化}
	while dis[1]<n do {用循环代替递归}
	  begin
		back[i]:=flow; {I的返回值为当前最小流量}
		flag:=false; t:=now[i]; {设置可用弧为false，t为当前第一条边}
		while t<>0 do
		  begin
			j:=edge[t].y;
			if (edge[t].f>0)and(dis[j]+1=dis[i]) then {有流，满足标号关系}
		  	  begin
				flag:=true; {可用弧}
				now[i]:=t; {更新当前弧}
				if edge[t].f<flow then flow:=edge[t].f; {更新最小流量}
				pre[j]:=t; {更新j点的前驱边}
				i:=j; {模拟递归，i换成j}
				if i=n then {到达汇点}
				  begin
					inc(ans,flow); {累加最大流}
					while i<>1 do
					  begin
						dec(edge[pre[i]].f,flow); {减少正向弧流量}
						inc(edge[edge[pre[i]].op].f,flow); {增加反向弧流量}
						i:=edge[pre[i]].x; {i为前驱边的x}
					  end;
					flow:=maxlongint; {初始化}
				  end;
				break; {找到可用弧，直接跳出}
			  end;
			t:=edge[t].next;
		  end;
		if flag then continue; {如果找到可用弧，则continue}
		min:=n-1; {初始化最小标号}
		t:=son[i];
		while t<>0 do
		  begin
			if (edge[t].f>0)and(dis[edge[t].y]<min) then
			  begin
				tmp:=t;
				min:=dis[edge[t].y];
			  end; {更新当前弧，更新最小标号}
			t:=edge[t].next;
		  end;
		now[i]:=tmp; {设置当前弧为刚才更新的tmp}
		dec(sumd[dis[i]]); {将i所在标号的群数量减去1}
		if sumd[dis[i]]=0 then break; {如果为0，则出现断层，退出}
		dis[i]:=min+1; {更新标号}
		inc(sumd[dis[i]]); {将i所在新标号的群数量加上1}
		if i<>1 then {处理前一条边}
		  begin 
			i:=edge[pre[i]].x; 
			flow:=back[i]; 
		  end;
	  end;
	writeln(ans);
end;

begin
	assign(input,'ditch.in'); reset(input);
	assign(output,'ditch.out'); rewrite(output);
	init;
	main;
	close(input); close(output);
end.