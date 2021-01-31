uses Graph,crt;
var
	gd,gm,ecode:integer;
	n,i:longint;
	x,y:array[1..100010]of longint;
	dhh:longint;
	s:string;
	ff:text;
begin
	randomize;
	gd := Detect;
	InitGraph(gd, gm,' ');
	ecode:=GraphResult;
	if ecode<>grOK then
		begin
		Writeln('Graphics error:', GraphErrorMsg(ecode));
		exit;
		end;
	while true do
		begin
		readln(dhh);
  		str(dhh,s);
		assign(ff,'c:\'+s+'.in');reset(ff);
		cleardevice;
		readln(ff,n);//n:=10;
		for i:=1 to n do
			begin
			readln(ff,x[i],y[i]);
			x[i]:=trunc(x[i]/1000000);
			y[i]:=trunc(y[i]/1000000);
			//if (x[i]>100)then x[i]:=100;if (y[i]>100)then y[i]:=100;
			//x[i]:=x[i];y[i]:=y[i]*100;
			circle(x[i],y[i],1);
			end;
		{for i:=1 to 1000 do
			begin
			circle(random(100),random(100),3);
			end;}
		close(ff);
		end;
	while not keypressed do;
	closegraph;
end.


