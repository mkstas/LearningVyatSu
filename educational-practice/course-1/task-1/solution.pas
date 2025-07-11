procedure CountSquares(side: integer; fileName: string);
const
  SQR_CNT = 30;
  SQR_SIDE = 200;
var
  count: integer;
  output: TextFile;
begin
  Assign(output, fileName);
  Rewrite(output);
  Append(output);

  count := (side div SQR_SIDE) * (side div SQR_SIDE) * SQR_CNT;

  Writeln(output, count);

  Close(output);
end;

begin
  CountSquares(400, 'ans1.txt');
  CountSquares(1000, 'ans2.txt');
  CountSquares(3000, 'ans3.txt');
end.
