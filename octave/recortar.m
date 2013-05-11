function out = recortar(x, n)

M = matriz_dct(length(x));
d = M * x;
d(floor(length(d) - (length(d) / n)) : end) = 0;
out = M \ d;