% boundary_points = níveis de decisão

boundary = [-1 -0.5 0 0.5 1]

% codebook = níveis de quantização

codebook = [-0.75 -0.25 0.25 0.75]

% Sequência

x = [0.7000   -0.3000   -0.9000    0.1000   -0.4000    0.2000    0.6000    0.8000] ;

[idx, xq ] = mquantiz(x, boundary, codebook)

% Defina o código binário de saída, sob a forma ex:
% binary_code= ['11'; '00'; '10'; '00'; '10'; '00'; '10'; '11'];

binary_code= ['11'; '01'; '00'; '10'; '01'; '10'; '11'; '11'];

eq = x - xq;

% Apresentação de resultados

[x', xq', eq']

binary_code
