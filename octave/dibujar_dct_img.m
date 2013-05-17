function dibujar(vector_1, vector_2, vector_3)

color_vector_1 = 'black';
color_vector_2 = 'red';
color_vector_3 = 'blue';
leyenda = {};

leyenda{end + 1} = 'Con ruido';
leyenda{end + 1} = 'Original';
leyenda{end + 1} = 'Luego de filtrar';

figure;
hold on;
plot(vector_2, 'color', color_vector_2);
plot(vector_1,  'color', color_vector_1);
plot(vector_3, 'color', color_vector_3);
hold off;
title('DCT');
legend(leyenda);