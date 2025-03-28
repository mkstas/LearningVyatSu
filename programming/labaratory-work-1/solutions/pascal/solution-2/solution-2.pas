program solution2;

var M, sum, i:integer;
var N:longint;

begin
    readln(N);
    readln(M);
    sum := 0;
    for i := 1 to M do
    begin
        sum += N mod 10;
        N := N div 10;
    end;
    writeln(sum);
end.