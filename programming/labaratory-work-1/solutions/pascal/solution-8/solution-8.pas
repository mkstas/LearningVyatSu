program solution8;

var N, i, ans, eng, ger, fra:integer;

begin
    readln(N);
    eng := 0;
    ger := 0;
    fra := 0;
    while N <> 0 do
    begin
        readln(ans);
        if ans = 1 then
            eng += 1;
        if ans = 2 then
            ger += 1;
        if ans = 3 then
            fra += 1;
        N -= 1
    end;
    writeln(eng);
    writeln(ger);
    writeln(fra);
end.