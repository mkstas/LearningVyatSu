{$codepage UTF8}

uses
  SysUtils;

var
  input: text;
  line: string;
  i, j, k, max, vertex: integer;
  matrix: array [1..5, 1..7] of integer;
  degrees: array [1..5] of integer;

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

  max := degrees[1];
  vertex := 1;

  for i := 2 to 5 do
  begin
    if degrees[i] > max then
    begin
      max := degrees[i];
      vertex := i;
    end;
  end;

  writeln('Вершина с максимальной полустепенью захода: ', vertex);
  write('Множество дуг для вершины ', vertex, ': {');

  for j := 1 to 7 do
  begin
    if (matrix[vertex][j] = -1) or (matrix[vertex][j] = 2) then
      write(' ', j, ' ');
  end;
  write('}');

  readln;
end.