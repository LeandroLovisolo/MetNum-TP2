function X = imagen_a_dct_vector(B)

D = imagen_a_dct(B);
X = zeros(1, length(B)^2);


% El par (x0, y0) indica el primer elemento de la diagonal actual
x0 = 1;
y0 = 1;

% El par (x, y) indica el elemento actual de la matriz
x = x0;
y = y0;

for i = 1:length(B)^2
    % Agrego el coeficiente actual
    X(i) = D(y, x);

    % Avanzo diagonalmente al siguiente coeficiente
    x--;
    y++;

    % Verifico si llegué al final de la diagonal actual
    if(x < 1 || y > length(B))
        % Avanzo a la siguiente diagonal
        if(x0 < length(B))
            x0++;
        else
            y0++;
        endif
        x = x0; y = y0;
    endif
end