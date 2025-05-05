{$codepage UTF8}

unit Queue;

interface

  type
    PNode = ^TNode;

    TNode = record
      data: string;
      next: PNode;
    end;

    TQueue = record
      head, tail: PNode;
    end;

  function check(var queue: TQueue): boolean;
  procedure init(var queue: TQueue);
  procedure push(var queue: TQueue; value: string);
  procedure pop(var queue: TQueue);
  procedure print(var queue: TQueue);

implementation

  function check(var queue: TQueue): boolean;
  begin
    if queue.head = nil then
    begin
      writeln('Очередь пуста');
      exit(true);
    end;
    writeln('Очередь не пуста');
    check := false;
  end;

  procedure init(var queue: TQueue);
  begin
    queue.head := nil;
    queue.tail := nil;
  end;

  procedure push(var queue: TQueue; value: string);
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
    if check(queue) then exit;

    queue.head := queue.head^.next;

    if queue.head = nil then
      queue.tail := nil;
  end;

  procedure print(var queue: TQueue);
  var
    node: PNode;
  begin
    if check(queue) then
      exit;

    node := queue.head;

    while node <> nil do
    begin
      write(node^.data, ' ');
      node := node^.next;
    end;

    writeln();
  end;

end.