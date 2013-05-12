function B = dct_a_imagen(D)

M = matriz_dct(length(D));
B = uint8((M \ (M \ D)')');