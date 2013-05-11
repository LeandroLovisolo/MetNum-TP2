function out = recortar(x, n)

M = matriz_dct(length(x));
d = M * x;
d(n:end) = 0;
out = M \ d;