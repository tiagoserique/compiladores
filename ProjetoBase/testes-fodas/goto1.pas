program goto1 (input, output);
label 100, 200;
var x  : integer;
begin

  read (x);
  100:
  if x < 1
    then goto 200;
  write(x);
  x:=x-1;
  goto 100;

  200: write(0);

end.
