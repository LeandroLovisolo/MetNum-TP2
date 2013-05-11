function x = ruido_normal_interpolado(n, i, media, varianza)

xi = ruido_normal(n/i, media, varianza);
x = interp1([1:n/i], xi, [1:(1/i):(n/i+1)]);
x = x';
x = x(1:n);
for i = 1:n
    if(isna(x(i)))
        x(i) = 0;
    end
end