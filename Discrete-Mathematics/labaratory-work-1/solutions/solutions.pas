program solution;

var
  A, B, C, D, E, X, Y, K: set of string;
  p, i: byte;
  number: real;
  symbol: char;
  bf: string;

begin
  repeat
    write('Введите мощность множества (не более 10): ');
    readln(p);
  until (p >= 1) and (p <= 10);
  
  write('Введите множество (A) действительных чисел: ');
  
  i := 0;
  
  while i < p do
  begin
    read(number);
    bf := FloatToStr(number);
    
    if bf in B then
    begin
      writeln('Число ', bf, ' уже входит во множетсво');
      write('Введите множество действительных чисел: ');
      continue;
    end
    else
    begin
      include(A, bf);
      i := i + 1;
    end;
  end;
  
  write('Введите множество (B) рациональных чисел: ');
  
  i := 0;
  
  while i < p do
  begin
    read(number);
    bf := FloatToStr(number);
    
    if bf in B then
    begin
      writeln('Число ', bf, ' уже входит во множетсво');
      write('Введите множество рациональных чисел: ');
      continue;
    end
    else
    begin
      include(B, bf);
      i := i + 1;
    end;
  end;
  
  write('Введите множество (C) натуральных чисел: ');
  
  i := 0;
  
  while i < p do
  begin
    read(number);
    bf := FloatToStr(int(number));
    
    if bf in C then
    begin
      writeln('Число ', bf, ' уже входит во множетсво');
      write('Введите корректное натуральное число: ');
      continue;
    end
    else
    begin
      include(C, bf);
      i := i + 1;
    end;
  end;
  
  write('Введите множество (D) латинских букв: ');
  
  i := 0;
  
  while i < p do
  begin
    read(symbol);
    bf := symbol;
    
    if bf in D then
    begin
      writeln('Буква ', bf, ' уже входит во множетсво');
      write('Введите корректную латинскую букву: ');
      continue;
    end
    else
    begin
      include(D, bf);
      i := i + 1;
    end;
  end;
  
  write('Введите множество (E) русских букв: ');
  
  i := 0;
  
  while i < p do
  begin
    read(symbol);
    bf := symbol;
    
    if bf in E then
    begin
      writeln('Буква ', bf, ' уже входит во множетсво');
      write('Введите корректную русскую букву: ');
      continue;
    end
    else
    begin
      include(E, bf);
      i := i + 1;
    end;
  end;
  
  X := A * B * C;
  Y := (D + E) - (D * E);
  K := X + Y;
  
  writeln('A = ', A);
  writeln('B = ', B);
  writeln('C = ', C);
  writeln('D = ', D);
  writeln('E = ', E);
  writeln('X = A * B * C = ', X);
  writeln('Y = (D + E) - (D * E) = ', Y);
  writeln('K = X + Y = ', K);
  writeln('Итоговая мощность множества: ', K.count);
end.