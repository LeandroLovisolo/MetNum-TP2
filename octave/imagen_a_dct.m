function D = imagen_a_dct(B)

M = matriz_dct(length(B));
D = M * double(B) * M';