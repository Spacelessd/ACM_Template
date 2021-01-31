unit BinaryHeap;

interface
const
	InfiniteValue = 10000000;
type
	TIndex = Longint;
	TKey = Longint;
	PBinaryNode = ^TBinaryNode;
	TBinaryNode = record
		Index: TIndex;
		Key: TKey;
	end;
	PBinaryHeap = ^TBinaryHeap;
	TBinaryHeap = object
		NodeNum: TIndex;
		MaxNodeNum: TIndex;
		Nodes: array of PBinaryNode;
		Maps: array of TIndex;
	public
		constructor Create(Size: TIndex);
		destructor Destory;
		procedure Insert(const Index: TIndex; const Key: TKey);
		procedure Delete(const Index: TIndex);
		function Minimum: PBinaryNode;
		procedure DeleteMin;
		procedure DecreaseKey(const Index: TIndex; const NewKey: TKey);
	private
		procedure Swap(var CurNodeA, CurNodeB: PBinaryNode);
		procedure Sink(Position: TIndex);
		procedure Rise(Position: TIndex);
	end;

implementation

constructor TBinaryHeap.Create(Size: TIndex);
var
	Index: TIndex;
begin
	MaxNodeNum := Size;
	NodeNum := 0;

	SetLength(Nodes, Size + 1);
	SetLength(Maps, Size + 1);
	for Index := 1 to Size do
	begin
		Nodes[Index] := nil;
		Maps[Index] := 0;
	end;
end;

destructor TBinaryHeap.Destory;
var
	Index: TIndex;
begin
	for Index := 1 to MaxNodeNum do
		if Nodes[Index] <> nil then
			Dispose(Nodes[Index]);
end;

procedure TBinaryHeap.Insert(const Index: TIndex; const Key: TKey);
var
	NewNode: PBinaryNode;
begin
	Inc(NodeNum);
	New(NewNode);
	NewNode^.Index := Index;
	NewNode^.Key := Key;
	Nodes[NodeNum] := NewNode;
	Maps[Index] := NodeNum;
	Rise(NodeNum);
end;

procedure TBinaryHeap.Delete(const Index: TIndex);
var
	Position: TIndex;
begin
	Position := Maps[Index];
	if Position = 0 then Exit;
	Maps[Index] := 0;
	Dispose(Nodes[Position]);
	Nodes[Position] := Nodes[NodeNum];
	Maps[Nodes[NodeNum]^.Index] := Position;
	Nodes[NodeNum] := nil;
	Dec(NodeNum);
	Sink(Position);
end;

function TBinaryHeap.Minimum: PBinaryNode;
begin
	Result := Nodes[1];
end;

procedure TBinaryHeap.DeleteMin;
begin
	Delete(Nodes[1]^.Index);
end;

procedure TBinaryHeap.DecreaseKey(const Index: TIndex; const NewKey: TKey);
var
	Position: TIndex;
begin
	Position := Maps[Index];
	if Position = 0 then Exit;
	if Nodes[Position]^.Key < NewKey then Exit;
	Nodes[Position]^.Key := NewKey;
	Rise(Position);
end;

procedure TBinaryHeap.Swap(var CurNodeA, CurNodeB: PBinaryNode);
var
	TmpNode: PBinaryNode;
	Position: TIndex;
begin
	TmpNode := CurNodeA;
	CurNodeA := CurNodeB;
	CurNodeB := TmpNode;
	Position := Maps[CurNodeA^.Index];
	Maps[CurNodeA^.Index] := Maps[CurNodeB^.Index];
	Maps[CurNodeB^.Index] := Position;
end;

procedure TBinaryHeap.Sink(Position: TIndex);
var
	ChildPosition: TIndex;
begin
	while Position shl 1 <= NodeNum do
	begin
		ChildPosition := Position shl 1;
		if ChildPosition < NodeNum then
			if Nodes[ChildPosition + 1]^.Key < Nodes[ChildPosition]^.Key then
				Inc(ChildPosition);
		if Nodes[ChildPosition]^.Key >= Nodes[Position]^.Key then Break;
		Swap(Nodes[ChildPosition], Nodes[Position]);
		Position := ChildPosition;
	end;
end;

procedure TBinaryHeap.Rise(Position: TIndex);
begin
	while Position > 1 do
	begin
		if Nodes[Position shr 1]^.Key <= Nodes[Position]^.Key then Break;
		Swap(Nodes[Position shr 1], Nodes[Position]);
		Position := Position shr 1;
	end;
end;
begin
end.
