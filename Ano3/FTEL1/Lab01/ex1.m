% boundary = níveis de decisão
% defina o vector cujos elementos são os níveis de decisão do
% quantizador uniforme de 2bits/amostra no intervalo [-1,1] do sinal de entrada
N = 2;
L = 2^N;
Max = 1;
Delta = 2*Max/L;

boundary = [-1 -0.5 0 0.5 1]

% codebook = níveis de quantização

codebook = [-0.75 -0.25 0.25 0.75]
