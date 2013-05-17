function dibujar(vector_1, vector_2, vector_3)

color_vector_1 = 'black';
color_vector_2 = 'red';
color_vector_3 = 'blue';
leyenda        = {'Original'};

if(exist('vector_2')) leyenda{end + 1} = 'Con ruido'; endif;
if(exist('vector_3')) leyenda{end + 1} = 'Luego de filtrar'; endif;

M = matriz_dct(length(vector_1));

figure;
hold on;
plot(vector_1,  'color', color_vector_1);
if(exist('vector_2')) plot(vector_2, 'color', color_vector_2); endif;
if(exist('vector_3')) plot(vector_3, 'color', color_vector_3); endif;
hold off;
title('Datos');
legend(leyenda);

figure;
hold on;
plot(M * vector_1,  'color', color_vector_1);
if(exist('vector_2')) plot(M * vector_2, 'color', color_vector_2); endif;
if(exist('vector_3')) plot(M * vector_3, 'color', color_vector_3); endif;
hold off;
title('DCT');
legend(leyenda);