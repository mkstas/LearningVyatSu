type
  TIntArray = array of uint64;

var
  dividers: TIntArray;
  input, output: TextFile;
  number, i: uint64;

begin
  Assign(input, 'task1.txt');
  Reset(input);

  Read(input, number);

  Close(input);

  SetLength(dividers, 0);

  i := 1;
  while i <> Trunc(Sqrt(number)) do
  begin
    if (number mod i) = 0 then
    begin
      SetLength(dividers, Length(dividers) + 2);
      dividers[Length(dividers) - 2] := i;
      dividers[Length(dividers) - 1] := number div i;
    end;
    i += 1;
  end;

  Assign(output, 'ans1.txt');
  Rewrite(output);
  Append(output);

  Writeln(output, Length(dividers));

  i := 0;
  while i <> Length(dividers) do
  begin
    Writeln(output, dividers[i]);
    i += 1;
  end;

  Close(output);
end.
