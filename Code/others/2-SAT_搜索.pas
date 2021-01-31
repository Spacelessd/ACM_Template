Const
	MaxNodeNum = ;
	MaxEdgeNum = ;
Type
	TEdge = Record
		Start,Target,PrevEdge:TIndex;
	End;
	TSat2 = Object
		NodeNum,EdgeNum:TIndex;
		Last:Array [-MaxNodeNum..MaxNodeNum] Of TIndex;
		Edge:Array [1..MaxEdgeNum] Of TEdge;
		Visit,VisitBackup:Array [1..MaxNodeNum] Of Boolean;
		Select:Array [-MaxNodeNum..MaxNodeNum] Of Boolean;
		P:Boolean;
		Procedure Initialize(FNodeNum:TIndex);
		Procedure AddEdge(X,Y:TIndex);
		Procedure Search(CurNode:TIndex);
		Procedure Main;
	End;
	Procedure TSat2.Initialize(FNodeNum:TIndex);
	Begin
		EdgeNum := 0 ;
		NodeNum := FNodeNum ;
		FillChar(Last,SizeOf(Last),0);
	End;
	Procedure TSat2.AddEdge(X,Y:TIndex);
	Begin
		Inc(EdgeNum);
		With Edge[EdgeNum] Do
		Begin
			Start := X ;
			Target := Y ;
			PrevEdge := Last[X] ;
			Last[X] := EdgeNum ;
		End;
	End;
	Procedure TSat2.Search(CurNode:TIndex);
	Var
		CurEdge:TIndex;
	Begin
		If (Not P) Then
			Exit;
		Visit[Abs(CurNode)] := True ;
		Select[CurNode] := True ;
		Select[-CurNode] := False ;
		CurEdge := Last[CurNode] ;
		While (CurEdge > 0) Do
			With Edge[CurEdge] Do
			Begin
				If (Not Visit[Abs(Target)]) Then
					Search(-Target)
				Else
					If (Not Select[-Target]) Then
					Begin
						P := False ;
						Visit[Abs(CurNode)] := False ;
						Exit;
					End;
				CurEdge := PrevEdge ;
			End;
		If (Not P) Then
			Visit[Abs(CurNode)] := False ;
	End;
	Procedure TSat2.Main;
	Var
		I:TIndex;
	Begin
		FillChar(Visit,SizeOf(Visit),False);
		FillChar(Select,SizeOf(Select),False);
		For I := 1 To NodeNum Do
		Begin
			If (Not Visit[I]) Then
			Begin
				P := True ;
				Search(I);
				If (Not P) Then
				Begin
					P := True ;
					Search(-I);
					If (Not P) Then
					Begin
						WriteLn('Terrible');
						Exit;
					End;
				End;
			End;
		End;
	End;
Var
	Sat2:TSat2;


