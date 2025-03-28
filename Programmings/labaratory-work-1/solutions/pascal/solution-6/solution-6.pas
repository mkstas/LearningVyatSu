program solution6;

var x1, y1, x2, y2, S:int64;

begin
    readln(x1, y1, x2, y2);

    if x1 < 0 then
        x1 := 0;
    if y1 < 0 then
        y1 := 0;
    if x2 < 0 then
        x2 := 0;
    if y2 < 0 then
        y2 := 0;

    S := (x1 - x2) * (y1 - y2);

    if S < 0 then
        S *= -1;

    writeln(S);
end.