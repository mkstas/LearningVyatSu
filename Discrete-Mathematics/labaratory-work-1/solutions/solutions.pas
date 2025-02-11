program solution;

uses Crt;

procedure print_menu();
begin
  clrscr();
  writeln('1. Ввод мощности множеств');
  writeln('2. Ввод множества рациональных чисел');
  writeln('3. Ввод множества действительных чисел');
  writeln('4. Ввод множества натуральных чисел');
  writeln('5. Ввод множества русских букв');
  writeln('6. Ввод множества латинских букв');
  writeln('7. Выполнить операции с множествами');
  writeln('0. Выход');
end;

var
  A, B, C, X: set of byte;
  D, E, Y, K: set of string;
  variant, p, n, i: byte;
  s: string;

begin
  print_menu();
  
  while true do
  begin
    write('> ');
    readln(variant);
    case variant of
      1:
        begin
          write('Мощность массива: ');
          readln(p);
        end;
      2:
        begin
          if p = 0 then
            writeln('Не введена мощность массива')
          else
          begin
            write('Множество рациональных чисел: ');
            for i := 1 to p do
            begin
              read(n);
              include(A, n);
            end;
          end;
        end;
      3:
        begin
          if p = 0 then
            writeln('Не введена мощность массива')
          else
          begin
            write('Множество действительных чисел: ');
            for i := 1 to p do
            begin
              read(n);
              include(B, n);
            end;
          end;
        end;
      4:
        begin
          if p = 0 then
            writeln('Не введена мощность массива')
          else
          begin
            write('Множество натуральных чисел: ');
            for i := 1 to p do
            begin
              read(n);
              include(C, n);
            end;
          end;
        end;
      5:
        begin
          if p = 0 then
            writeln('Не введена мощность массива')
          else
          begin
            write('Множество русских букв: ');
            for i := 1 to p do
            begin
              read(s);
              include(E, s);
            end;
          end;
        end;
      6:
        begin
          if p = 0 then
            writeln('Не введена мощность массива')
          else
          begin
            write('Множество латинских букв: ');
            for i := 1 to p do
            begin
              read(s);
              include(D, s);
            end;
          end;
        end;
      7:
        begin
          X := A * B * C;
          Y := (D + E) - (D * E);

          writeln(X);
          writeln(Y);
        end;
      0:
        begin
          exit;
        end
    else
      begin
        writeln('Неверный пункт меню');
      end;
    end;
  end;
end.