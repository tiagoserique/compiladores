program cmdIf (input, output);
var i, j: integer;
begin
    read(j);
    i:=0;
    while (i < j) do
    begin
        if (i div 2 * 2 = i)
        then write(i,0)
        else write(i,1);
        i := i+1
    end;
end.