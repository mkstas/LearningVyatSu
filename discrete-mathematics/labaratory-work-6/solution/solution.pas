{$codepage UTF8}

uses
  SysUtils;

const
  MAX_SIZE = 5;

type
  TMatrix = array[1..MAX_SIZE, 1..MAX_SIZE] of integer;
  TVisited = array[1..MAX_SIZE] of boolean;
  TPath = array[1..MAX_SIZE] of integer;

var
  adjacency: TMatrix;
  visited: TVisited;
  path: TPath;
  startVertex: integer;

procedure ReadMatrix(var matrix: TMatrix);
var
  fileInput: text;
  fileLine: string;
  i, j, k: integer;
begin
  Assign(fileInput, 'input.txt');
  Reset(fileInput);

  i := 1;
  while not Eof(fileInput) do
  begin
    Readln(fileInput, fileLine);

    j := 1;
    for k := 1 to Length(fileLine) do
    begin
      if fileLine[k] <> ' ' then
      begin
        matrix[i, j] := StrToInt(fileLine[k]);
        j := j + 1;
      end;
    end;
    i := i + 1;
  end;

  Close(fileInput);
end;

procedure PrintMatrix(var matrix: TMatrix);
var
  i, j: integer;
begin
  Write('  ');
  for i := 1 to MAX_SIZE do
    Write(' ', i, ' ');
  Writeln();

  for i := 1 to MAX_SIZE do
  begin
    Write(i, '  ');
    for j := 1 to MAX_SIZE do
      Write(matrix[i, j], '  ');
    Writeln();
  end;
end;

procedure PrintPath(pathLength: integer);
var
  i: integer;
begin
  for i := 1 to pathLength - 1 do
    Write(path[i], ' -> ');
  Writeln(path[pathLength]);
end;

procedure DFS(current, target, pathLength: integer);
var
  i: integer;
begin
  visited[current] := true;
  path[pathLength] := current;

  if current <> target then
  begin
    for i := 1 to MAX_SIZE do
      if (adjacency[current, i] <> 0) and not visited[i] then
        DFS(i, target, pathLength + 1);
  end
  else
    PrintPath(pathLength);

  visited[current] := false;
end;

procedure FindAllPaths(startVertex: integer);
var
  i: integer;
begin
  for i := 1 to MAX_SIZE do
    visited[i] := false;

  for i := 1 to MAX_SIZE do
    if i <> startVertex then
      DFS(startVertex, i, 1);
end;

begin

  ReadMatrix(adjacency);
  Writeln(#10, 'Матрица смежности', #10);
  PrintMatrix(adjacency);

  Write(#10, 'Введите начальную вершину: ');
  Readln(startVertex);

  Writeln('Список всех элементарных путей');
  FindAllPaths(startVertex);

  Readln;

end.