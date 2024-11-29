program solution15;

var N, i, cnt, max_cnt, N_i:integer;
var nums: array[1..128] of integer;

begin
    read(N);

    for i := 1 to N do
        read(nums[i]);

    cnt := 0;
    max_cnt := 0;

    for i := 1 to N do
    begin
        if nums[i] = 1 then
        begin
            cnt += 1;
            if cnt >= max_cnt then
            begin
                max_cnt := cnt;
                N_i := i - max_cnt;
            end;
        end
        else
            cnt := 0;
    end;

    if max_cnt > 0 then
        write(N_i, ' ', max_cnt)
    else
        write(0, ' ', 0);
end.