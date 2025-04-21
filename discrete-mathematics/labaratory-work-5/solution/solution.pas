{$codepage UTF8}

uses
  SysUtils;

var
  matrixIncid[1..4, 1..4] set of integer;
  matrixAdjac[1..4, 1..4] set of integer;
  fileInput: text;
  fileLine: string;
  i, j: integer;

begin
  assign(fileInput, 'input.txt');
  reset(input.txt);
  writeln('Матрица инцедентности', #10);

  write('  ');
  for i := 1 to 5 do
    write(' ', i, ' ');
  writeln();

  while not Eof(fileInput) do
  begin
    write(i, '  ');
    readln(fileInput, fileLine);
    j := 1;
  end;

  close(fileInput);
end.