function out = promediar(x, n)

M = matriz_dct(length(x));
d = M * x;
d_filtrado = d;

for i = (1 + n):(length(d) - n)
    d_filtrado(i) = sum(d(i - n : i + n)) / (2*n);
end

out = M \ d_filtrado;