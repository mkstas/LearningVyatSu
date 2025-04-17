{$codepage UTF8}

uses
  SysUtils;

var
  input: text;
  line: string;
  i, j, k, max: integer;
  matrix: array [1..5, 1..7] of integer;
  degrees: array [1..5] of integer;
  vertexes: array[1..5] of integer;

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
      if (line[k] <> ' ') and (line[k] <> '-') then
      begin
        if line[k - 1] = '-' then
          matrix[i][j] := StrToInt(line[k]) * -1
        else
          matrix[i][j] := StrToInt(line[k]);

        if (matrix[i][j] = -1) or (matrix[i][j] = 2) then
          degrees[i] += 1;

        j := j + 1;
      end;
    end;

    i := i + 1;
  end;

  Close(input);

  writeln('Матрица инцидентности');
  writeln();

  write('     ');
  for i := 1 to 7 do
    write(' ', i, ' ');
  writeln();

  write('    ');
  for i := 2 to 7 do
    write('----');
  writeln();

  for i := 1 to 5 do
  begin
    write(' ', i, ' | ');
    for j := 1 to 7 do
      if matrix[i][j] = -1 then
        write(matrix[i][j], ' ')
      else
        write(' ', matrix[i][j], ' ');
    writeln();
  end;
  writeln();

  max := 0;

  for i := 1 to 5 do
  begin
    if (degrees[i] > max) then
      max := degrees[i];
  end;

  j := 1;
  for i := 1 to 5 do
  begin
    if degrees[i] = max then
    begin
      vertexes[j] := i;
      j := j + 1;
    end;
  end;

  writeln('Вершины с максимальной полустепенью захода');

  i := 1;
  while vertexes[i] <> 0 do
  begin
    write('Множество дуг для вершины ', vertexes[i], ': {');
    for j := 1 to 7 do
    begin
      if (matrix[vertexes[i]][j] = -1) or (matrix[vertexes[i]][j] = 2) then
        write(' ', j);
    end;
    writeln(' }');
    i := i + 1;
  end;

  readln;
end.