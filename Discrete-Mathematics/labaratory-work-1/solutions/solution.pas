program solution;

var
  A, B, C, D, E: set of string;
  bf: string;
  p, i: byte;
  error: boolean;
  number: real;

begin
  error := true;
  
  repeat
    write('Введите мощность множества (не более 10): ');
    try
      readln(p);
      error := false;
    except
      writeln('Неверный формат ввода');
    end;
  until (p >= 1) and (p <= 10) and not error;
  
  write('Введите множество (A) действительных чисел (-100 - 100): ');
  i := 0;
  while i < p do
  begin
    try
      read(number);
      if (number > 100) or (number < -100) then
      begin
        writeln('Выход за пределы значения числа');
        continue;
      end;
      bf := FloatToStr(number);
      if bf in A then
      begin
        writeln('Число ', bf, ' уже входит в множество');
        continue;
      end;
      include(A, bf);
      i := i + 1;
    except
      writeln('Неверный формат ввода');
    end;
  end;
  readln();
  
  write('Введите множество (B) рациональых чисел (-100 - 100): ');
  i := 0;
  while i < p do
  begin
    try
      read(number);
      if (number > 100) or (number < -100) then
      begin
        writeln('Выход за пределы значения числа');
        continue;
      end;
      bf := FloatToStr(number);
      if bf in B then
      begin
        writeln('Число ', bf, ' уже входит в множество');
        continue;
      end;
      include(B, bf);
      i := i + 1;
    except
      writeln('Неверный формат ввода');
    end;
  end;
  readln();
  
  write('Введите множество (С) натуральных чисел (1 - 100): ');
  i := 0;
  while i < p do
  begin
    try
      read(number);
      if (frac(number) <> 0) or (number < 1) then
      begin
        writeln('Число ', number, ' не является натуральным');
        continue;
      end;
      if number > 100 then
      begin
        writeln('Превышен предел значения числа');
        continue;
      end;
      bf := FloatToStr(number);
      if bf in C then
      begin
        writeln('Число ', bf, ' уже входит в множество');
        continue;
      end;
      include(C, bf);
      i := i + 1;
    except
      writeln('Неверный формат ввода');
    end;
  end;
  readln();
  
  writeln('A = ', A);
  writeln('B = ', B);
  writeln('C = ', C);
  writeln('X = A * B * C = ', A * B * C);
end.