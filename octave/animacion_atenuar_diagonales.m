function animacion_atenuar_diagonales(B_original, B, k, deltaCoef)

% Muestro imagen original
figure;
imshow(B_original);
title("Original");

% Precomputo la DCT de la imagen
D = imagen_a_dct(B);

% Vector en el que voy a guardar los PSNR para cada iteración
psnrs = [];

% Matriz en la que voy a guardar la imagen con mejor PSNR obtenida
B_max_psnr = [];

% Genero el rango de coeficientes en el que voy a iterar
rango = 1:deltaCoef:length(B)^2;

% Figura nueva para la animación
figure;

for i = rango
    X = D;

    % El par (x0, y0) indica el primer elemento de la diagonal actual
    x0 = length(B);
    y0 = length(B);

    % El par (x, y) indica el coeficiente actual
    x = x0;
    y = y0;

    for j = i:length(B)^2
        % Atenúo coeficiente actual
        X(y, x) = X(y, x) * k;

        % Avanzo diagonalmente al siguiente coeficiente
        x--;
        y++;

        % Verifico si llegué al final de la diagonal actual
        if(x < 1 || y > length(B))
            % Avanzo a la siguiente diagonal
            if(y0 > 1)
                y0--;
            else
                x0--;
            endif
            x = x0; y = y0;
        endif
    end
    
    B_actual = dct_a_imagen(X);
    
    % Computo PSNR y lo guardo en el vector
    psnr_actual= psnr_img(B_original, B_actual);
    psnrs(end+1) = psnr_actual;

    % Si la imagen produjo el PSNR más grande hasta ahora, la guardo
    if(psnr_actual == max(psnrs))
        B_max_psnr = B_actual;
    endif;

    % Muestro iteración actual
    imshow(B_actual);
    title(sprintf('Conservando %d coeficientes de %d. PSNR = %f.', i, length(B)^2, psnr_actual));

    % Sin sleep no dibuja la animación
    sleep(0.1);
end

% Grafico los PSNR en función de la cantidad de coeficientes conservados
figure;
plot(rango, psnrs);
title(sprintf('PSNR para distintas cantidades de coeficientes conservados. Constante: %f.', k));
xlabel('Cantidad de coeficientes conservados en la DCT');
ylabel('PSNR');

% Muestro la imagen de la iteración que obtuvo mayor PSNR
[max_psnr, idx_max_psnr] = max(psnrs);
coeficientes_max_psnr = 1 + deltaCoef * idx_max_psnr;
figure;
imshow(B_max_psnr);
title(sprintf('Imagen con mayor PSNR. Constante: %f. Coeficientes conservados: %d. PSNR: %f.', k, coeficientes_max_psnr, max_psnr));