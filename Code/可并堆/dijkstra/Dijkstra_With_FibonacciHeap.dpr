{$R+,Q+,D+}
program Dijsktra_With_FibonacciHeap;
uses
	Base, GraphGen, FibonacciHeap;
type
	TDist = array[1..MaxN] of TKey;
	TCheck = array[1..MaxN] of Boolean;
var
	Node: PFibonacciNode;
	Heap: TFibonacciHeap;
	Dist: TDist;
	Check: TCheck;
function Dijkstra: TKey;
var
	i: TIndex;
	Cur, Ptr: TIndex;
begin
	Heap.Create(N);
	for i := 1 to N do
	begin
		Check[i] := false;
		Heap.Insert(i, InfiniteValue);
		Dist[i] := InfiniteValue;
	end;
	Heap.DecreaseKey(S, 0);
	Dist[S] := 0;
	while not Check[T] do
	begin
		Node := Heap.Minimum;
		if Node = nil then Break;
		Cur := Node^.Index;

		Check[Cur] := true;
		Heap.DeleteMin;
		
		Ptr := Last[Cur];
		while Ptr > 0 do
		begin
			with Edge[Ptr] do
				if not Check[Adj] and (Dist[Adj] > Dist[Cur] + Weight) then
				begin
					Dist[Adj] := Dist[Cur] + Weight;
					Heap.DecreaseKey(Adj, Dist[Adj]);
				end;
			Ptr := Edge[Ptr].Prev;
		end;
	end;
	Result := Dist[T];
	Heap.Destory;
end;
procedure Main;
begin
	Randomize;
	GenerateRandomSparse;
	Writeln(Dijkstra);
end;
begin
	Main;
end.