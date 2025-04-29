{$codepage UTF8}

unit Queue;

interface

  type
    PNode = ^TNode;

    TNode = record
      data: integer;
      next: PNode;
    end;

    TQueue = record
      head, tail: PNode;
    end;

  procedure init(var queue: TQueue);
  procedure push(var queue: TQueue; value: integer);
  procedure pop(var queue: TQueue);
  procedure print(var queue: TQueue);

implementation

  procedure init(var queue: TQueue);
  begin
    queue.head := nil;
    queue.tail := nil;
  end;

  procedure push(var queue: TQueue; value: integer);
  var
    node: PNode;
  begin
    new(node);
    node^.data := value;
    node^.next := nil;

    if queue.head = nil then
      queue.head := node
    else
      queue.tail^.next := node;

    queue.tail := node;
  end;

  procedure pop(var queue: TQueue);
  begin
    queue.head := queue.head^.next;

    if queue.head = nil then
      queue.tail := nil;
  end;

  procedure print(var queue: TQueue);
  begin
    writeln(queue.head^.data);
  end;

end.