program solution;

var
  A, B, C, D, E: set of string;
  bf: string;
  p, i: byte;
  error: boolean;
  number: real;
  numerator, denominator: integer;
  symbol: char;

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
  
  writeln('Введите множество (B) рациональых чисел: ');
  i := 0;
  while i < p do
  begin
    try
      write('Введите числитель: ');
      readln(numerator);
      repeat
        write('Введите знаменатель: ');
        read(denominator);
        if denominator < 1 then
          writeln('Знаменатель не может быть меньше 1');
      until denominator > 0;
      number := int(numerator) / int(denominator);
      bf := FloatToStr(number);
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
  
  write('Введите множество (D) латинских букв: ');
  i := 0;
  while i < p do
  begin
    try
      read(symbol);
      if ord(symbol) = 32 then continue;
      if ((ord(symbol) >= 65) and (ord(symbol) <= 90)) or 
          ((ord(symbol) >= 97) and (ord(symbol) <= 122)) then
        bf := symbol
      else
      begin
        writeln('Буква ', symbol, ' не является латинской');
        continue;
      end;
      if bf in D then
      begin
        writeln('Буква ', bf, ' уже входит в множество');
        continue;
      end;
      include(D, bf);
      i := i + 1;
    except
      writeln('Неверный формат ввода');
    end;
  end;
  readln();
  
  write('Введите множество (E) русских букв: ');
  i := 0;
  while i < p do
  begin
    try
      read(symbol);
      if (ord(symbol) >= 1040) and (ord(symbol) <= 1103) then
        bf := symbol
      else
      begin
        writeln('Буква ', symbol, ' не является латинской');
        continue;
      end;
      if bf in E then
      begin
        writeln('Буква ', bf, ' уже входит в множество');
        continue;
      end;
      include(E, bf);
      i := i + 1;
    except
      writeln('Неверный формат ввода');
    end;
  end;
  readln();
  
  writeln('A = ', A, ' ');
  writeln('B = ', B, ' ');
  writeln('C = ', C);
  writeln('D = ', D, ' ');
  writeln('E = ', E);
  writeln('X = A * B * C = ', A * B * C);
  writeln('Y = (E + D) - (E * D) = ', (E + D) - (E * D));
  writeln('K = X + Y = ', (A * B * C) + ((E + D) - (E * D)));
  writeln('Мощность множества K = ', ((A * B * C) + ((E + D) - (E * D))).count);
  readln;
end.