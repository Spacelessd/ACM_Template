var
n,m,i,l,s,t,c,cost,u:longint;
v:array[0..20010]of boolean;
dis:array[0..20010]of longint;
e_n,e_t,e_c,e_u,e_p,e_x:array[0..1000010]of longint;

function min(a,b:longint):longint;
begin
    if a>b then exit(b);
    exit(a);
end;

procedure addedge(s,t,c,u,k:longint);
begin
    inc(l);
    e_n[l]:=e_n[s];
    e_n[s]:=l;//下一条边
    e_t[l]:=t;//边的另一端
    e_c[l]:=c;//边的费用
    e_u[l]:=u;//边的容量
    e_p[l]:=l+k;//对应的边
end;

procedure build(s,t,c,u:longint);
begin
    addedge(s,t,c,u,1);
    addedge(t,s,-c,0,-1);
end;

function aug(no,m:longint):longint;
var
i,d:longint;
begin
    if no=n then begin
        inc(cost,m*dis[1]);
        exit(m);
    end;
    v[no]:=true;
    i:=e_x[no];
    while i<>0 do begin
        if (e_u[i]>0)and(not v[e_t[i]])and(dis[e_t[i]]+e_c[i]=dis[no]) then begin
            d:=aug(e_t[i],min(m,e_u[i]));
            if d>0 then begin
                dec(e_u[i],d);
                inc(e_u[e_p[i]],d);
                e_x[no]:=i;
                exit(d);
            end;
        end;
        i:=e_n[i];
    end;
    e_x[no]:=i;
    exit(0);
end;

function modlabel:boolean;
var
d,i,j:longint;
begin
    d:=maxlongint;
    for i:=1 to n do if v[i] then begin
        j:=e_n[i];
        while j<>0 do begin
            if (e_u[j]>0)and(not v[e_t[j]])and(e_c[j]-dis[i]+dis[e_t[j]]<d) then
                d:=e_c[j]-dis[i]+dis[e_t[j]];
            j:=e_n[j];
        end;
    end;
    if d=maxlongint then exit(true);
    for i:=1 to n do if v[i] then begin
        v[i]:=false;
        inc(dis[i],d);
    end;
    exit(false);
end;

begin
    assign(input,'costflow.in');reset(input);
    assign(output,'costflow.out');rewrite(output);
    readln(n,m);
    l:=n;
    for m:=m downto 1 do begin
        readln(s,t,u,c);
        build(s,t,c,u);
    end;
    repeat
        for i:=1 to n do e_x[i]:=e_n[i];
        while aug(1,maxlongint)>0 do fillchar(v,sizeof(v),0);
    until modlabel;
    writeln(cost);
    close(output);
end.
