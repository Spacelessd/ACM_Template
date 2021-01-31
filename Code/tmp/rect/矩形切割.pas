Program Cover;
Const Maxn=10000;  ｛立方体集合最多能容纳10000个立方体｝
Type Blocks=Record
              x1,y1,z1,x2,y2,z2:Longint; ｛描述方块的6个域｝
            End;
Var i,j,k,m,n,x,y,z,r,tot:longint;
    Cubic:array[1..Maxn] of Blocks;
    Now:Blocks;
Procedure Init;  ｛读入数据并预处理的过程｝
Begin
  assign(input,'cover.in');
  reset(input);
  assign(output,'cover.out');
  rewrite(output);
  readln(n);
  Fillchar(Cubic,sizeof(Cubic),0);
  tot:=0;
End;
Function Max(a,b:Longint):Longint; ｛比较两个数并返回较大者的函数｝
Begin
  if a>b then Max:=a
  else Max:=b;
End;
Function Min(a,b:Longint):Longint; ｛比较两个数并返回较小者的函数｝
Begin
  if a<b then Min:=a
  else Min:=b;
End;
Procedure Add(x1,y1,z1,x2,y2,z2:Longint);｛加入立方体的过程｝
Begin
  inc(tot);
  Cubic[tot].x1:=x1; Cubic[tot].y1:=y1; Cubic[tot].z1:=z1;
  Cubic[tot].x2:=x2; Cubic[tot].y2:=y2; Cubic[tot].z2:=z2;
End;
Procedure Cut(x1,y1,z1,x2,y2,z2,Direction:Longint);｛切割｝
Var k1,k2:longint;
Begin
  Case Direction of
    1:Begin ｛先在x方向切｝
        k1:=Max(x1,Now.x1);  ｛计算线段[x1,x2],[Now.x1,Now.x2]｝
        k2:=Min(x2,Now.x2);  ｛的交集[k1,k2]｝
        if x1<k1 then Add(x1,y1,z1,k1,y2,z2);
        if k2<x2 then Add(k2,y1,z1,x2,y2,z2);
        Cut(k1,y1,z1,k2,y2,z2,Direction+1); ｛调用y方向的切割｝
      End;
    2:Begin｛然后在y方向切｝
        k1:=Max(y1,Now.y1);
        k2:=Min(y2,Now.y2);
        if y1<k1 then Add(x1,y1,z1,x2,k1,z2);
        if k2<y2 then Add(x1,k2,z1,x2,y2,z2);
        Cut(x1,k1,z1,x2,k2,z2,Direction+1); ｛调用z方向的切割｝
      End;
    3:Begin｛接着在z方向切｝
        k1:=Max(z1,Now.z1);
        k2:=Min(z2,Now.z2);
        if z1<k1 then Add(x1,y1,z1,x2,y2,k1);
        if k2<z2 then Add(x1,y1,k2,x2,y2,z2);
      End;
  End;
End;
Function Cross(x1,x2,x3,x4:longint):boolean; ｛判断线段[x1,x2]，[x3,x4]是否相交｝
Begin
  if (x1>=x4)or(x3>=x2) then Cross:=false
  else Cross:=true;
End;
Procedure Caculate;  ｛计算所有立方体的体积和｝
Var i,Volume,k:longint;
Begin
  Volume:=0;
  for i:=1 to tot do
  begin
    k:=(Cubic[i].x2-Cubic[i].x1)*
	(Cubic[i].y2-Cubic[i].y1)*
	(Cubic[i].z2-Cubic[i].z1);
    Inc(Volume,k);
  end;
  Writeln(Volume);
End;

Procedure Main;  ｛主过程｝
Var  i,j,tot1:Longint;
Begin
  for i:=1 to n do
  begin
    readln(x,y,z,r);
    Now.x1:=x-r;   Now.y1:=y-r;   Now.z1:=z-r;
    Now.x2:=x+r;   Now.y2:=y+r;   Now.z2:=z+r;
    j:=0;
    tot1:=tot; ｛保存当前队列的尾指针，则tot1之后的立方体都是新切割出来的｝
    While j<tot1 do
    Begin
      inc(j);
      if (Cross(Cubic[j].x1,Cubic[j].x2,Now.x1,Now.x2))
      and(Cross(Cubic[j].y1,Cubic[j].y2,Now.y1,Now.y2))
      and(Cross(Cubic[j].z1,Cubic[j].z2,Now.z1,Now.z2)) then  ｛若两立方体发生重叠，则进行切割｝
      Begin
        Cut(Cubic[j].x1,Cubic[j].y1,Cubic[j].z1,
            Cubic[j].x2,Cubic[j].y2,Cubic[j].z2,1);
        Cubic[j]:=Cubic[tot1];
        Cubic[tot1]:=Cubic[tot];
        dec(tot);
        dec(tot1);
        dec(j);
      End;
    End;
    Add(Now.x1,Now.y1,Now.z1,Now.x2,Now.y2,Now.z2);｛加入矩形Now｝
  end;
  Caculate;
  Close(output);
End;

Begin
  Init;
  Main;
End.
