program solution4;

var n, min_n, i, i_n:integer;

begin
    read(n);
    min_n := n;
    i := 0;
    i_n := 0;
    while n <> 0 do
    begin
        i += 1;
        read(n);
        if min_n > n then
        begin
            min_n := n;
            i_n := i;
        end;
    end;
    writeln(i_n);
end.