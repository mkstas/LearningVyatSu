type
  TIntArray = array of integer;
  TIntArray2D = array of TIntArray;

var
  input, output: TextFile;
  adjacency, neighbors: TIntArray2D;
  colors: TIntArray;
  vertexes, edges, vertex1, vertex2: integer;
  i, j, color, max: integer;

begin
  Assign(input, 'task3.txt');
  Reset(input);

  Read(input, vertexes);
  Read(input, edges);

  SetLength(adjacency, vertexes, vertexes);

  while not Eof(input) do
  begin
    Read(input, vertex1);
    Read(input, vertex2);

    adjacency[vertex1 - 1, vertex2 - 1] := 1;
    adjacency[vertex2 - 1, vertex1 - 1] := 1;
  end;

  Close(input);

  SetLength(neighbors, vertexes);

  for i := 0 to vertexes - 1 do
    for j := 0 to vertexes - 1 do
    begin
      if (i <> j) and (adjacency[i, j] <> 0) then
      begin
        SetLength(neighbors[i], Length(neighbors[i]) + 1);
        neighbors[i, High(neighbors[i])] := j + 1;
      end;
    end;

  SetLength(colors, vertexes);

  color := 1;

  for i := 0 to vertexes - 1 do
  begin

    for j := 0 to vertexes - 1 do
      if colors[neighbors[i, j] - 1] = 1 then
      begin
        color += 1;
        Break;
      end;

    for j := 0 to Length(neighbors[i]) - 1 do
      if colors[neighbors[i, j] - 1] = 0 then
        colors[neighbors[i, j] - 1] := color;
  end;

  max := colors[0];

  for i := 1 to vertexes - 1 do
    if colors[i] > max then
      max := colors[i];

  Assign(output, 'ans3.txt');
  Rewrite(output);
  Append(output);

  Writeln(output, max);

  for i := 0 to vertexes - 1 do
    Write(output, colors[i], ' ');

  Close(output);
end.
