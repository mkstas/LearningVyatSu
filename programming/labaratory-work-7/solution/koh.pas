Unit KOH;
Interface
procedure KOHDraw(x, y, l, u: Real; t: Integer;sx,sy:Integer);
procedure Scale(z:integer);
Implementation
Uses GraphABC;
var k:integer:=4;
    (x,y,sx,sy,l,t):=(10,354,1,1,400,4);
procedure KOHDraw(x, y, l, u: Real; t: Integer;sx,sy:Integer);
  procedure Draw2(var x, y: Real; l, u: Real; t: Integer);
  begin
    KOHDraw(x, y, l, u, t,sx,sy);
    x := x + l * cos(u);
    y := y - l * sin(u);
  end;
begin
  SetCoordinateScale(sx,sy);
  if t > 0 then
  begin
    l := l / 3;
    Draw2(x, y, l, u, t - 1);
    Draw2(x, y, l, u + pi / 3, t - 1);
    Draw2(x, y, l, u - pi / 3, t - 1);
    Draw2(x, y, l, u, t - 1);  
  end
  else
    Line(Round(x), Round(y), Round(x + cos(u) * l), Round(y - sin(u) * l))
end;
procedure Scale(z:integer);
Begin
  Case z of
    VK_Z:t+=1;
    VK_X:t-=1;
    VK_Up:Begin sx+=1;sy+=1; End;
    VK_Down:Begin sx-=1;sy-=1; End;
    VK_S:y+=10;
    VK_W:y-=10;
    VK_A:x-=10;
    VK_D:x+=10;
  end;
  Window.Clear;
  KOHDraw(x, y, l, pi / 3, t,sx,sy);
  KOHDraw(x+400, y, l, pi, t,sx,sy);
  KOHDraw(x+200, y - 346, l, -pi / 3, t,sx,sy);
  Redraw;
end;
Begin
  SetWindowSize(425, 500);
  SetWindowCaption('Фракталы: Снежинка Коха');
  KOHDraw(x, y, t, pi / 3, k,sx,sy);
  KOHDraw(x + 400, y, t,  pi, k,sx,sy);
  KOHDraw(x + 200, 8, t, -pi / 3, k,sx,sy);
  LockDrawing;
  OnKeyDown:=Scale;
end.