{$codepage UTF8}

uses
  SysUtils;

var
  matrix: array [1..5, 1..5] of integer;
  i, j, k: integer;
  fileInput: text;
  fileLine: string;

begin
  assign(fileInput, 'input.txt');
  reset(fileInput);
  writeln('Матрица смежности', #10);

  write('  ');
  for i := 1 to 5 do
    write(' ', i, ' ');
  writeln();

  i := 1;

  while not Eof(fileInput) do
  begin
    write(i, '  ');
    readln(fileInput, fileLine);
    j := 1;

    for k := 1 to Length(fileLine) do
    begin
      if fileLine[k] <> ' ' then
      begin
        if (fileLine[k] = '1') or (i = j) then
          matrix[i][j] := 0
        else
          matrix[i][j] := 1;

        write(fileLine[k], '  ');
        j := j + 1;
      end;
    end;
    writeln();

    i := i + 1;
  end;
  writeln();

  writeln('Дополнение графа', #10);

  write('  ');
  for i := 1 to 5 do
    write(' ', i, ' ');
  writeln();

  for i := 1 to 5 do
  begin
    write(i, '  ');
    for j := 1 to 5 do
      write(matrix[i][j], '  ');
    writeln();
  end;

  readln;
end.