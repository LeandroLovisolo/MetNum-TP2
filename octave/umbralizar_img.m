function out = umbralizar_img(B, umbral)

D = imagen_a_dct(B);

for i = 1:length(D)
    for j = 1:length(D)
        if(abs(D(i,j)) <= umbral)
            D(i,j) = 0;
            printf('Eliminando coeficiente (%d, %d)\n', i, j);
        endif
    end
end

out = dct_a_imagen(D);