program exemplo3 (input, output);
var z, t :  integer;
   procedure g(t : integer);
   var x :  integer;
   begin
      t:=2*t;
      x:=2*t;
      z:=x+1
   end;
begin
   z:=3;
   t:=4;
   g(t); write (z,t);
   g(z); write (z,t);
   g(t+z); write (z,t);
   g(7); write (z,t)
end.
   