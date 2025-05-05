unit Dragon;

interface

uses
  GraphABC;

procedure DrawFractal(x, y, sx, sy, depth: integer);

implementation

  var
    angle: integer;

  procedure Draw();
  begin
    angle := angle mod 4;
    case angle of
      0: LineRel(10, 0);
      1, -3: LineRel(0, 10);
      2, -2: LineRel(-10, 0);
      3, -1: LineRel(0, -10);
    end;
  end;

  procedure Fractal(depth, turn: integer);
  begin
    if depth < 1 then
    begin
      Draw();
      exit;
    end;

    Fractal(depth - 1, 1);
    angle := angle + turn;
    Fractal(depth - 1, -1);
  end;

  procedure DrawFractal(x, y, sx, sy, depth: integer);
  var
    wrappedX, wrappedY: integer;
    visibleWidth, visibleHeight: integer;
  begin
    SetCoordinateScale(sx, sy);

    visibleWidth := WindowWidth div sx;
    visibleHeight := WindowHeight div sy;

    wrappedX := x mod visibleWidth;
    wrappedY := y mod visibleHeight;

    if wrappedX < 0 then wrappedX := wrappedX + visibleWidth;
    if wrappedY < 0 then wrappedY := wrappedY + visibleHeight;

    MoveTo(wrappedX, wrappedY);
    angle := 0;
    Fractal(depth, 1);
  end;

end.