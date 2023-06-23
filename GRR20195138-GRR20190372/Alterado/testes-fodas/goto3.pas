
program goto1 (input, output);
var x  : integer;

  procedure p;
  label 100;
  begin
    100: write(-1)
  end;

begin
  goto 100;
end.
