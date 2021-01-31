var
 maxn,a,b,c,n:longint;

begin
 assign(output,'statistics.in'); rewrite(output);
 randomize;
 n:=5000; maxn:=1000000007;
 writeln(random(maxn),' ',random(maxn),' ',random(maxn),' ',n);
 close(output);
end.