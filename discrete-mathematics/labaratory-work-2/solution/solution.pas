{$codepage UTF8}

var
  n, i, j, max, vertex: integer;
  matrix: array[1..10, 1..10] of integer;
  degrees: array[1..10] of integer;

begin
  Randomize();

  repeat
    write('Введите размерность матрицы (4 <= n <= 10): ');
    readln(n);
  until ((n >= 4) and (n <= 10));

  writeln('Матрица смежности');

  for i := 1 to n do
  begin
    for j := 1 to n do
    begin
      matrix[i][j] := Random(2);
      degrees[i] += matrix[i][j];
      write(matrix[i][j], '  ');
    end;
    writeln();
  end;

  max := degrees[1];
  vertex := 1;

  for i := 2 to n do
  begin
    if degrees[i] > max then
    begin
      max := degrees[i];
      vertex := i;
    end;
  end;

  writeln('Вершина с максимальной полустепенью исхода: ', vertex);
  write('Множество дуг для вершины ', vertex, ': {');

  for j := 1 to n do
  begin
    if matrix[vertex][j] = 1 then
      write(' (', vertex, ', ', j, ') ');
  end;
  write('}');

  readln;
end.