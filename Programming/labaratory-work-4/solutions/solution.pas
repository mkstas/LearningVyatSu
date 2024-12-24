program solution;

type
    item = record
        data: integer;
        next, prev:byte;
    end;

    list = record
        items:array[1..100] of item;
        head, tail:byte;
    end;

var
    n, k, i, max, min:integer;
    L:list;

procedure push(var L:list; new_el:integer; k:integer);
begin
    L.items[new_el].data := k;

    if new_el <> 1 then
    begin
        L.items[new_el].prev := new_el;
        L.items[new_el - 1].next := new_el;
    end;
end;

begin
    L.head := 0;
    L.tail := 0;

    readln(n);

    for i := 1 to 2 * n do
    begin
        read(k);
        push(L, i, k);
    end;

    if L.items[1].data > L.items[2 * n].data then
        max := L.items[2 * n].data
    else
        max := L.items[1].data;

    for i := 2 to n do
    begin
        if L.items[i + 1].data > L.items[2 * n - (i - 1) * 2].data then
            min := L.items[2 * n - (i - 1) * 2].data
        else
            min := L.items[i + 1].data;

        if min > max then
            max := min;
    end;

    writeln(max);
end.