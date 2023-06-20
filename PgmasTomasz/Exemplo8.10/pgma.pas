program exemplo1 (input, output);
var k : integer;
procedure p(    n : integer; var g:integer);
var h : integer;
begin
   if n<2 then
      g:=g+n
   else
   begin
      h:=g;
      p(n-1,h);
      g:=h;
      p(n-2, g)
   end;
   write(n,g)
end;
begin
   k:=0;
   p(3,k)
end.
   
      
