program exemplo74 (input, output);
var z, x: integer;
   procedure g(t:integer);
   var y : integer;
   begin
      y:=t*t; z:=z+x+y;
      write(z)
   end;

   procedure h (y : integer);
   var x : integer;
      procedure f(y : integer);
      var t : integer;
      begin
         t:=z+x+y; g(t);
         z:=t
      end;
   begin
      x:=y+1;
      f(x);
      g(z+x)
   end;
begin
   z:=1;
   x:=3;
   h(x);
   g(x);
   write(x,z)
end.
   

