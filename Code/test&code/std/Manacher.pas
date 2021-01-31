Procedure Manacher;
  Var
    i,j,k:longint;
  Begin
    i:=1; j:=0;
    while i<=len do
      Begin
        while ((i-j>0) and (i+j<len) and (st[i-j]=st[i+j+1])) do inc(j);
        r[i]:=j; k:=1;
        while (k<=r[i]) and (r[i-k]<>r[i]-k) do
          Begin
            if r[i-k]<r[i]-k then r[i+k]:=r[i-k]
                             else r[i+k]:=r[i]-k;
            inc(k);
          End;
        inc(i,k);
        if j-k>0 then dec(j,k)
                 else j:=0;
      End;
  End;


