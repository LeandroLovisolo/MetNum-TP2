function M = matriz_dct(N)

unos = ones(N,1);
C = [1; unos(1:N-1)+1] / N;
C = sqrt(C);
t = ([0:N-1]' + 0.5) * (pi/N);
f = [0:N-1]';
Mo = (C * unos') .* cos(f * t');
M = round(Mo * 128);