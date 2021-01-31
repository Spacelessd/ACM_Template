//非递归，广搜增广。
{
ID                      :       hqztrue1
PROG                    :       ditch
LANG                    :       PASCAL
}
 
Program ditch;
 
Const
  fin                   =       'ditch.in';
  fout                  =       'ditch.out';
 
Var
  map,f                 :       Array [0..201,0..201] of Longint;
  Last,n,m              :       Longint;
 
Procedure Init;
  var
    a                   :       Longint;
    x,y,z               :       Longint;
  begin
    readln(n,m);
    Fillchar(map,sizeof(map),0);
    for a:=1 to n do
      begin
        readln(x,y,z);
        inc(map[x,y],z);
      end;
  end;
 
Procedure Main;
  var
    h,w                 :       Array [0..4000] of Integer;
    use                 :       Array [0..4000] of Boolean;
    top,join,t,r,a,x    :       Integer;
    ff                  :       Boolean;
    min                 :       Longint;
 
  begin
    Last:=0;
    Fillchar(f,sizeof(f),0);
    Fillchar(w,sizeof(w),0);
    Fillchar(h,sizeof(h),0);
 
    while True do
      begin
        top:=0;join:=1;
        h[join]:=1;ff:=False;
        Fillchar(use,sizeof(use),False);use[1]:=True;
        Repeat
          inc(top);
          for a:=1 to m do
            if (map[h[top],a]-f[h[top],a]>0) and not(use[a])
              then
                begin
                  inc(join);
                  h[join]:=a;w[join]:=top;use[a]:=True;
                  if h[join]=m then
                    begin
                      min:=MaxLongint;
                      x:=w[join];t:=h[x];r:=h[join];
                      while r<>1 do
                        begin
                          if map[t,r]-f[t,r]<min then min:=map[t,r]-f[t,r];
                          r:=t;t:=h[w[x]];x:=w[x];
                        end;
                      x:=w[join];t:=h[x];r:=h[join];
                      while r<>1 do
                        begin
                          inc(f[t,r],min);dec(f[r,t],min);
                          r:=t;t:=h[w[x]];x:=w[x];
                        end;
                      inc(Last,min);
                      ff:=True;
                      break;
                    end;
                end;
        Until (top=join) or ff;
        if top=join then break;
      end;
  end;
 
Procedure Print;
  begin
    writeln(Last);
  end;
 
Begin
  Assign(INPUT,fin);Reset(INPUT);
  Init;
  Close(INPUT);
  Main;
  Assign(OUTPUT,fout);Rewrite(OUTPUT);
  Print;
  Close(OUTPUT);
End.