program varsGlobais (input, output);
var a, b, c: integer;
    k1, temp: integer;
    te: boolean;
    m, n, s : integer;
begin
    a:=0;
    temp:=10;

    read(a);
    write(10+1,a,temp);

    te := (a > b) and (b = c);

    read(m,n);
    s:=0;
    while m<=n do
    begin
        s:=s+m*m;
        write (m,s);
        m:=m+1
    end


end.