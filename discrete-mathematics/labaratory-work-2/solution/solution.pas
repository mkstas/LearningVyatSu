{$codepage UTF8}

var
  n, i, j, max: integer;
  matrix: array[1..10, 1..10] of integer;
  degrees: array[1..10] of integer;
  vertexes: array[1..10] of integer;

begin
  Randomize();

  repeat
    write('Введите размерность матрицы (4 <= n <= 10): ');
    readln(n);
  until ((n >= 4) and (n <= 10));

  writeln('Матрица смежности');
  writeln();

  write('    ');
  for i := 1 to n do
    write(' ', i, ' ');
  writeln();

  write('    ');
  for i := 2 to n do
    write('----');
  writeln();

  for i := 1 to n do
  begin
    write(' ', i, ' | ');
    for j := 1 to n do
    begin
      matrix[i][j] := Random(2);
      degrees[i] += matrix[i][j];
      write(matrix[i][j], '  ');
    end;
    writeln();
  end;
  writeln();

  max := 0;

  for i := 1 to n do
  begin
    if (degrees[i] > max) then
      max := degrees[i];
  end;

  j := 1;
  for i := 1 to n do
  begin
    if degrees[i] = max then
    begin
      vertexes[j] := i;
      j := j + 1;
    end;
  end;

  writeln('Вершины с максимальной полустепенью исхода');

  i := 1;
  while vertexes[i] <> 0 do
  begin
    write('Множество дуг для вершины ', vertexes[i], ': {');
    for j := 1 to n do
    begin
      if matrix[vertexes[i]][j] = 1 then
        write(' (', vertexes[i], ', ', j, ')');
    end;
    writeln(' }');
    i := i + 1;
  end;

  readln;
end.