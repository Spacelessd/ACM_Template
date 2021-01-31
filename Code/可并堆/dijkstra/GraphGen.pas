unit GraphGen;

interface

uses
	Base;
const
	MaxN = 10000;
	MaxM = 100000;
	MaxWeight = 100000;
type
	TEdge = record
		Adj: TIndex;
		Weight: TKey;
		Prev: TIndex;
	end;
	TEdgeSet = array[1..MaxM] of TEdge;
	TLast = array[1..MaxN] of TIndex;
var
	N, M: TIndex;
	S, T: TIndex;
	Edge: TEdgeSet;
	Last: TLast;

procedure GenerateRandomSparse;
procedure PrintRandomSparse;

implementation

procedure InsertEdge(x, y: TIndex; w: TKey);
begin
	Inc(M);
	Edge[M].Adj := y;
	Edge[M].Weight := w;
	Edge[M].Prev := Last[x];
	Last[x] := M;
end;

procedure GenerateRandomSparse;
var
	i: TIndex;
begin
	N := MaxN;
	S := 1;
	T := MaxN;
	M := 0;
	FillChar(Last, SizeOf(Last), 0);
	for i := 2 to MaxN do
		InsertEdge(Random(i - 1) + 1, i, Random(MaxWeight) + 1);
	while M < MaxM do
		InsertEdge(Random(MaxN) + 1, Random(MaxN) + 1, Random(MaxWeight) + 1);
end;

procedure PrintEdge(x, y: TIndex; w: TKey);
begin
	Writeln(x, ' ', y, ' ', w);
end;

procedure PrintRandomSparse;
var
	i: TIndex;
begin
	N := MaxN;
	S := 1;
	T := MaxN;
	M := 0;
	Writeln(N, ' ', MaxM, ' ', S, ' ', T);
	for i := 2 to MaxN do
		PrintEdge(Random(i - 1) + 1, i, Random(MaxWeight) + 1);
	while M < MaxM do
		PrintEdge(Random(MaxN) + 1, Random(MaxN) + 1, Random(MaxWeight) + 1);
end;
begin
end.
