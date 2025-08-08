type
  TIntArray = array of Integer;
  TIntArray2D = array of TIntArray;
  TRect = record
    startRow, startCol, endRow, endCol: Integer;
  end;

var
  inputFile, outputFile: TextFile;
  imageMatrix, coveredMatrix: TIntArray2D;
  rectangles: array of TRect;
  rowCount, colCount, totalCoveredCells, totalCells, rectangleCount: Integer;
  currentLine: string;
  i, j, row, col, heightStep, widthStep: Integer;
  maxArea, startValue, minWidth, currentWidth, area: Integer;
  maxRect: TRect;

begin
  Assign(inputFile, 'task1.txt');
  Reset(inputFile);

  Readln(inputFile, rowCount, colCount);

  SetLength(imageMatrix, rowCount);
  SetLength(coveredMatrix, rowCount);

  for i := 0 to rowCount - 1 do
  begin
    SetLength(imageMatrix[i], colCount);
    SetLength(coveredMatrix[i], colCount);
    for j := 0 to colCount - 1 do
      coveredMatrix[i][j] := 0;
  end;

  for i := 0 to rowCount - 1 do
  begin
    Readln(inputFile, currentLine);
    for j := 1 to colCount do
      imageMatrix[i][j-1] := Ord(currentLine[j]) - Ord('0');
  end;

  Close(inputFile);

  totalCells := rowCount * colCount;
  totalCoveredCells := 0;
  rectangleCount := 0;
  SetLength(rectangles, totalCells);

  while totalCoveredCells < totalCells do
  begin
    maxArea := 0;
    maxRect.startRow := -1;

    for row := 0 to rowCount - 1 do
    for col := 0 to colCount - 1 do
    begin
      if coveredMatrix[row][col] = 1 then Continue;

      startValue := imageMatrix[row][col];
      minWidth := colCount;

      for heightStep := 0 to rowCount - 1 - row do
      begin
        if (row + heightStep >= rowCount) or (coveredMatrix[row + heightStep][col] = 1) then Break;
        if imageMatrix[row + heightStep][col] <> startValue then Break;

        currentWidth := 0;
        for widthStep := 0 to colCount - 1 - col do
        begin
          if (col + widthStep >= colCount) or (coveredMatrix[row + heightStep][col + widthStep] = 1) then Break;
          if imageMatrix[row + heightStep][col + widthStep] <> startValue then Break;
          currentWidth := widthStep + 1;
        end;

        if currentWidth < minWidth then 
          minWidth := currentWidth;
          
        area := (heightStep + 1) * minWidth;
        if area > maxArea then
        begin
          maxArea := area;
          maxRect.startRow := row;
          maxRect.startCol := col;
          maxRect.endRow := row + heightStep;
          maxRect.endCol := col + minWidth - 1;
        end;
      end;
    end;

    if maxArea = 0 then Break;

    rectangles[rectangleCount] := maxRect;
    Inc(rectangleCount);

    for i := maxRect.startRow to maxRect.endRow do
      for j := maxRect.startCol to maxRect.endCol do
        if coveredMatrix[i][j] = 0 then
        begin
          coveredMatrix[i][j] := 1;
          Inc(totalCoveredCells);
        end;
  end;

  Assign(outputFile, 'ans1.txt');
  Rewrite(outputFile);

  Writeln(outputFile, rectangleCount);

  for i := 0 to rectangleCount - 1 do
    Writeln(outputFile, 
            rectangles[i].startRow, ' ',
            rectangles[i].startCol, ' ',
            rectangles[i].endRow, ' ',
            rectangles[i].endCol);

  Close(outputFile);
end.
