program solution13;

var N, i:integer;
var ring, nums: array[1..128] of integer;

begin
    read(N);

    for i := 1 to N do
        read(ring[i]);

    for i := 1 to N do
    begin
        if ring[i] = 0 then
            case i of
                1: nums[i] := ring[N] + ring[N - 1];
                2: nums[i] := ring[1] + ring[N];
                else nums[i] := ring[i - 1] + ring[i - 2];
            end
        else
            nums[i] := ring[i];
    end;

    for i := 1 to N do
        write(nums[i], ' ');
end.