{$codepage UTF8}

uses
  SysUtils;

const
  MAX_SIZE = 5;

type
  TMatrix = array[1..MAX_SIZE, 1..MAX_SIZE] of integer;

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

var
  adjacency: TMatrix;

begin

  ReadMatrix(adjacency);
  Writeln(#10, 'Матрица смежности', #10);
  PrintMatrix(adjacency);

end.