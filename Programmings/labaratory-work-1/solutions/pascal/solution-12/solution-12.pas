program solution12;

var n, i, sum:integer;

begin
    readln(n);
    sum := 0;
    for i := 1 to n - 1 do
    begin
        if n mod i = 0 then
            sum += i;
    end;
    if sum = n then
        writeln('YES')
    else
        writeln('NO');
end.