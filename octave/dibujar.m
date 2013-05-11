function dibujar(original, con_ruido)

color_original = "blue"
color_ruido    = "red"
leyenda        = {"Original", "Con ruido"}

M = matriz_dct(length(original));

figure;
hold on;
plot(original, "color", color_original);
plot(con_ruido, "color", color_ruido);
title("Datos");
legend(leyenda);

figure;
hold on;
plot(M * original, "color", color_original);
plot(M * con_ruido, "color", color_ruido);
title("DCT");
legend(leyenda);