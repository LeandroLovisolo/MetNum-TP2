function dibujar(original, con_ruido, sin_ruido)

color_original  = "black";
color_con_ruido = "red";
color_sin_ruido = "blue";
leyenda         = {"Original"};

if(exist("con_ruido")) leyenda{end + 1} = "Con ruido"; endif;
if(exist("sin_ruido")) leyenda{end + 1} = "Sin ruido"; endif;

M = matriz_dct(length(original));

figure;
hold on;
plot(original,  "color", color_original);
if(exist("con_ruido")) plot(con_ruido, "color", color_con_ruido); endif;
if(exist("sin_ruido")) plot(sin_ruido, "color", color_sin_ruido); endif;
title("Datos");
legend(leyenda);

figure;
hold on;
plot(M * original,  "color", color_original);
if(exist("con_ruido")) plot(M * con_ruido, "color", color_con_ruido); endif;
if(exist("sin_ruido")) plot(M * sin_ruido, "color", color_sin_ruido); endif;
title("DCT");
legend(leyenda);