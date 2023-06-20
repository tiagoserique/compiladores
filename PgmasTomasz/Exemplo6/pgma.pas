program exercicio1 (input, output);
var t :  integer;
   function g(n,r : integer; var k:integer):integer;
   var t : integer
      function f(i: integer):integer;
      var s,t : integer;
      begin (* f *)
         s:=i*i;
         if i<s then
            begin
               k:=k+1;
               f:=0;
            end
         else
            begin
               f:=g(n-1,r-s,t)+f(i+1);
               k:=k+1
            end
      end (* f *)
   begin (* g *)
      if n=0 then
         begin
            k:=0;
            g:=g(n-1,r,t) + 2*f(1);
            k:=k+t;
         end
   end(* g *)

begin(* principal *)
   write (g(2,5,t),t)
end(* principal *)
