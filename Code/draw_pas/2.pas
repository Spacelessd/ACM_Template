Program Myprog;
uses Graph;
var
	gd,gm,ecode: Integer;
begin
	gd := Detect;
	InitGraph(gd, gm,' ');
	ecode:=GraphResult;
	if ecode<>grOK then
		begin
			Writeln('Graphics error:', GraphErrorMsg(ecode));
			exit;
		end;
	//setcolor(3);
	outtextxy(10,450,'Press Enter..');
	//setcolor(6);
	SetLineStyle(0,0,1); circle(320,240,100);  readln;
	line(0,0,639,479); readln;
	SetFillStyle(1,1);
	sector(300,200,0,90,90,80);
	readln;
	closegraph;
end.


