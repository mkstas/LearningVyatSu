program solution17;

var N, K, i, j, length, sum:integer;
var nums: array[1..128] of integer;

begin
    read(N, K);

    for i := 1 to N do
        read(nums[i]);

    length := 0;

    for i := 1 to N do
    begin
        sum := 0;
        for j := i to N do
        begin
            sum += nums[j];
            if (sum <= K) and (j - i + 1 > length) then
                length := j - i + 1;
        end;
    end;

    write(length);
end.