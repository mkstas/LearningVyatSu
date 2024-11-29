program solution21;

var N, i, ans:integer;
var a: array[1..64] of integer;

begin
    read(N);

    for i := 1 to N do
        read(a[i]);

    ans := 1;

    for i := 2 to N - 1 do
    begin
        if (a[i] <= a[i - 1]) and (a[i] >= a[i + 1]) or
            (a[i] >= a[i - 1]) and (a[i] <= a[i + 1]) then
            ans := 0;
    end;

    if ans = 1 then
        write('Yes')
    else
        write('No');
end.