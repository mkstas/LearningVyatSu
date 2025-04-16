{$codepage UTF8}

uses
  SysUtils;

var
  input: text;
  line: string;
  i, j, k: integer;
  matrix: array [1..5, 1..7] of integer;

begin
  Assign(input, 'input.txt');
  Reset(input);
  i := 1;

  while not Eof(input) do
  begin
    readln(input, line);
    j := 1;

    for k := 1 to Length(line) do
    begin
      if line[k] <> ' ' then
      begin
        if (line[k] = '1') or (i = j) then
          matrix[i][j] := 0
        else
          matrix[i][j] := 1;

        j := j + 1;
      end;
    end;

    i := i + 1;
  end;

  writeln('Дополнение графа в виде матрицы смежности');

  for i := 1 to 5 do
  begin
    for j := 1 to 5 do
    begin
      write(matrix[i][j], ' ');
    end;
    writeln();
  end;

  readln;
end.