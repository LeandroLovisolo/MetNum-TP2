function out = umbralizar(x, umbral)

M = matriz_dct(length(x));
d = M * x;

for i = 1:length(d)
    if(abs(d(i)) <= umbral)
        d(i) = 0;
    endif
end

out = M \ d;