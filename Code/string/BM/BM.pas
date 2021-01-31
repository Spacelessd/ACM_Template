//BM×î´ó´®Æ¥Åä
var
	a,b: String;
	next: Array[Byte] of Word;
function dist(s: String;Len: Word;ch: Char): Word;
var
	i: Integer;
begin
	i:=Len-1;
	if ch=s[i] then exit(Len);
	Dec(i);

	while i>=0 do
	if ch=s[i] then exit(Len-i-1) else Dec(i);

	exit(Len);
end;
function BMPos(a,b: String): Word;
var
	i,j: Integer;
	Lena,Lenb: Word;
begin
	BMPos:=0;
	Lena:=Length(a);
	Lenb:=Length(b);
	if Lena>Lenb then exit;

	i:=Lena-1;j:=i;

	while (i>=0) and (j<Lenb) do
	if a[i]=b[j] then
	begin
		Dec(i);Dec(j);
	end else
	begin
		Inc(j,dist(a,Lena,b[j]));
		i:=Lena-1;
	end;

	if i<0 then exit(j+1);
end;
begin
	while not eof do
	begin
		readln(a);
		readln(b);
		writeln(BMPos(a,b));
	end;
end.


