program teste (input, output); 
var m, n, s : integer;
begin
   read(m,n);
   s:=0;
   while m<=n do
   begin
      s:=s+m*m;
      write (m,s);
      m:=m+1
   end
   

   
end.
