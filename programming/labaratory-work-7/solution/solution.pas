uses
  GraphABC, Dragon;

var
  depth: integer = 1;
  x: integer = 500;
  y: integer = 150;
  sx: integer = 1;
  sy: integer = 1;

procedure Scale(key: integer);
begin
  case key of
    VK_Z:
      begin
        if depth <= 10 then 
          depth += 1 
        else
          exit;
      end;
    VK_X:
      begin
        if depth > 1 then
          depth -= 1
        else
          exit;
      end;
    VK_S:
      if sx < 4 then
      begin
        sx := sx + 1;
        sy := sy + 1;
        x := 500 div sx; y := 150 div sy;
      end;
    VK_D:
      if sx > 1 then
      begin
        sx := sx - 1;
        sy := sy - 1;
        x := 500 div sx; y := 150 div sy;
      end;
    VK_UP:
      y := y - 10;
    VK_DOWN:
      y := y + 10;
    VK_LEFT:
      x := x - 10;
    VK_RIGHT:
      x := x + 10;
  end;

  Window.Clear();
  DrawFractal(x, y, sx, sy, depth);
end;

begin

  SetWindowSize(800, 600);
  OnKeyDown := Scale;
  DrawFractal(x, y, sx, sy, depth);

end.