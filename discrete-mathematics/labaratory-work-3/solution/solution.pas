{$codepage UTF8}

uses
  SysUtils;

var
  matrix: array [1..5, 1..7] of integer;
  degrees: array [1..5] of integer;
  vertexes: array[1..5] of integer;
  i, j, k, max: integer;
  fileInput: text;
  fileLine: string;

begin
  assign(fileInput, 'input.txt');
  reset(fileInput);
  writeln('Матрица инцидентности', #10);

  write('  ');
  for i := 1 to 7 do
    write(' ', i, ' ');
  writeln();

  i := 1;

  while not Eof(fileInput) do
  begin
    write(i, ' ');
    readln(fileInput, fileLine);
    j := 1;

    for k := 1 to Length(fileLine) do
    begin
      if (fileLine[k] <> ' ') and (fileLine[k] <> '-') then
      begin
        if fileLine[k - 1] = '-' then
        begin
          matrix[i][j] := StrToInt(fileLine[k]) * -1;
          write(matrix[i][j], ' ')
        end
        else
        begin
          matrix[i][j] := StrToInt(fileLine[k]);
          write(' ', matrix[i][j], ' ');
        end;

        if (matrix[i][j] = -1) or (matrix[i][j] = 2) then
          degrees[i] += 1;

        j := j + 1;
      end;
    end;
    writeln();

    i := i + 1;
  end;
  writeln();

  max := degrees[1];

  for i := 2 to 5 do
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