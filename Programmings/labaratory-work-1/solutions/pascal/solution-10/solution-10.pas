program solution10;

var M, K, i, j, good_group, sum_skip, n_skip:integer;
var avg_skip:real;

begin
    readln(M);
    good_group := 0;
    for i := 1 to M do
    begin
        read(K);
        sum_skip := 0;
        for j := 1 to K do
        begin
            read(n_skip);
            sum_skip += n_skip;
        end;
        avg_skip := sum_skip / K;
        if (avg_skip < 10) and (good_group = 0) then
            good_group := i;
    end;
    if (good_group <> 0) then
        writeln('The good group ', good_group)
    else
        writeln('No');
end.