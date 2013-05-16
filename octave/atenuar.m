function out = atenuar(X, coefInicial, coefFinal, k)

M = matriz_dct(length(X));
D = M * X;

for i=coefInicial:coefFinal
    D(i) = D(i) * k;
end

out = M \ D;