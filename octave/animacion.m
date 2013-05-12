function animacion(B_original, B)

% Muestro imagen original
figure;
imshow(B_original);
title("Original");

% Precomputo la DCT de la imagen
D = imagen_a_dct(B);

% Vector en el que voy a guardar los PSNR para cada iteración
psnrs = [];

% Genero el rango de filas en el que voy a iterar
deltaFilas = 8;
rango = deltaFilas:deltaFilas:length(B);

% Figura nueva para la animación
figure;

for i = rango
    % Elimino todas las filas desde i hasta el final
    X = D;
    X(i:end, :) = 0;
    B_actual = dct_a_imagen(X);
    
    % Computo PSNR y lo guardo en el vector
    psnr_actual= psnr_img(B_original, B_actual);
    psnrs(end+1) = psnr_actual;

    % Muestro iteración actual
    imshow(B_actual);
    title(sprintf('%d filas de %d. PSNR = %f.', i, length(B), psnr_actual));

    % Sin sleep no dibuja la animación
    sleep(0.1);
end

% Grafico los PSNR en función de la cantidad de filas conservadas
figure;
plot(rango, psnrs);
title("PSNR para distintas cantidades de filas conservadas");
xlabel("Cantidad de filas conservadas en la DCT");
ylabel("PSNR");

% Muestro la imagen de la iteración que obtuvo mayor PSNR
[max_psnr, idx_max_psnr] = max(psnrs);
filas = deltaFilas * idx_max_psnr;
D(filas:end, :) = 0;
figure;
imshow(dct_a_imagen(D));
title(sprintf('Imagen con mayor PSNR. Filas conservadas: %d. PSNR: %f.', filas, max_psnr));