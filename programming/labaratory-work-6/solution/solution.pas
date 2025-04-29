{$codepage UTF8}

uses Queue;

var
  q: TQueue;

begin
  init(q);
  push(q, 10);
  push(q, 20);
  print(q);
  pop(q);
  print(q);
end.