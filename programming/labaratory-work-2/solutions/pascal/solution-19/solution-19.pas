program solution19;

var N, M, i, j, sum:integer;
var avg, min_avg:real;
var matrix: array[1..16, 1..16] of integer;

begin
    read(N, M);

    for i := 1 to N do
    begin
        for j := 1 to M do
            read(matrix[i][j]);
    end;

    for i := 1 to N do
    begin
        sum := 0;
        for j := 1 to M do
            sum += matrix[i][j];

        avg := sum / M;

        if i = 1 then
            min_avg := avg;

        if avg < min_avg then
            min_avg := avg;
    end;

    write(min_avg:0:2);
end.