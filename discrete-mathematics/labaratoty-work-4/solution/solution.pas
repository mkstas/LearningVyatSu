{$codepage UTF8}

uses
  SysUtils;

var
  input: text;
  line: string;
  i, j, k: integer;
  matrix: array [1..5, 1..5] of integer;

begin
  Assign(input, 'input.txt');
  Reset(input);

  writeln('Матрица смежности');
  writeln();

  write('    ');
  for i := 1 to 5 do
    write(' ', i, ' ');
  writeln();

  write('    ');
  for i := 2 to 5 do
    write('----');
  writeln();

  i := 1;

  while not Eof(input) do
  begin
    readln(input, line);
    j := 1;

    write(' ', j, ' | ');
    for k := 1 to Length(line) do
    begin
      if line[k] <> ' ' then
      begin
        if (line[k] = '1') or (i = j) then
          matrix[i][j] := 0
        else
          matrix[i][j] := 1;

        write(line[k], '  ');

        j := j + 1;
      end;
    end;
    writeln();

    i := i + 1;
  end;
  writeln();

  writeln('Дополнение графа');
  writeln();

  write('    ');
  for i := 1 to 5 do
    write(' ', i, ' ');
  writeln();

  write('    ');
  for i := 2 to 5 do
    write('----');
  writeln();

  for i := 1 to 5 do
  begin
    write(' ', i, ' | ');
    for j := 1 to 5 do
    begin
      write(matrix[i][j], '  ');
    end;
    writeln();
  end;

  readln;
end.