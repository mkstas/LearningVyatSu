program solution;

type
    node = record
        info: integer;
        next, prev:byte;
    end;

    list = record
        nodes:array[1..32] of node;
        first, last:byte;
    end;

var n, k, i, cur:integer;
    L:list;

procedure make_null(var L:list);
begin
    L.first := 0;
    L.last := 0;
end;

procedure insert(var L:list; k:integer; i:integer);
begin
    L.nodes[i].info := k;
end;

begin
    make_null(L);

    readln(n);

    for i := 1 to 2 * n do
    begin
        read(k);
        insert(L, k, i);
    end;

    for i := 1 to 2 * n do
    begin
        writeln(L.nodes[i].prev, ' ', L.nodes[i].info, ' ', L.nodes[i].next);
    end;
end.