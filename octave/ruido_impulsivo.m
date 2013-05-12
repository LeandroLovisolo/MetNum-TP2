function Br = ruido_impulsivo(B, p, q)

Br = B;

for i = 1:size(B)(1)
    for j = 1:size(B)(2)
        r = rand();
        if(r < p) Br(i, j) = 0;   endif;
        if(r > q) Br(i, j) = 255; endif;
    end
end