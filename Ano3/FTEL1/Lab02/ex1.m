% Taxa de bit
R = 1000;

% Número de amostras por bit na simulação
N_amostras_bit = 100;

%frequência de amostragem da simulação numérica
fs = 100e3;

%período de amostragem da simulação
ts = 1/fs;

% duração dos impulsos: tempo de bit
Tb = 1/R;

%tempo de simulação 100ms
tsim = (1000e-3);

% Nbits, número de bits total usado na simulação
Nbits = tsim/Tb;

% No. total de amostras
N = Nbits*N_amostras_bit;

% instantes de amostragem
% tome atenção que a dimensão de t deve ser igual N
t = (0:ts:tsim-ts);

d = (1 - (-1));


% geração de N bits aleatórios entre 0 e 1
rng(37) %semente para geração dos números aleatórios

% sequência de bits transmitidos: sequência de 0s e 1s
n1 = -1;
n2 =  2;
bitTx = ceil(n1+n2*rand(1,Nbits));

% converter para NRZ polar com amplitude A = 1
A = 1;

r = find(~bitTx); %encontrar os elementos nulos correspondentes ao bit "0"
bitTx(r) = -1;    % trocar esses elementos por -1

% sequência de bits amostrada
matrix = ones(N_amostras_bit,Nbits);
g = bsxfun(@times, bitTx, matrix); % g é uma matriz com os bits gerados
g = A*reshape(g,1,[]); % converter para vector linha e multiplicar pela amplitude A

% gráfico da sequência de bits
subplot(2,1,1)
plot(t,g)
axis([0 0.01 -1.5 1.5])

% Adição de ruído AWGN, distribuição Gaussiana ou Normal
variancia = 0.02;

ruido = random('Normal', 0, sqrt(variancia), 1, N);

x = g+ruido;

subplot(2,1,2)
plot(t,x)
axis([0 0.01 -1.5 1.5])

eyediagram(x,N_amostras_bit,Tb)
set(gca,'color','black');
set(gca,'XColor','white');
set(gca,'YColor','white');
hline = findobj(gcf,'type','line');
set(hline,'Color', 'yellow');

set(gcf,'color','black');

fprintf('Qual o instante ideal de amostragem [0,Tb]?\n')

% instantes de amostragem no receptor
% Ts_1bit instante óptimo de amostragem para o primeiro bit [0, Tb]
Ts_1bit = Tb/2;
Ts = Ts_1bit:Tb:tsim;

iTs = find(t==Ts_1bit);
iTs=iTs:N_amostras_bit:N;

% nível de decisão
nivel_decisao = zeros(1,Nbits);

% ---------------------%%%%%%%%%%%%%%%%-------------------------

% Obter taxa de erros para vários valores de potência do ruído
variancia = [0.18 0.36 0.72 1.44];


for k=1:length(variancia)
  ruido = random('Normal', 0, sqrt(variancia(k)), 1, N);
  x = g+ruido;

  %% sinal amostrado
  xs = x(iTs);

  %% sinal (bits) recebidos ap?s decis?o
  a = 2;
  b = 1;
  bitRx = a*(xs > nivel_decisao)-b;

  %% taxa de  erros (probabilidade de erro)
  bits_errados = bitTx - bitRx;

  %% No. de bits errados: todos os elementos de "bits_errados" que não sejam nulos
  N_bits_errados(k) = length(find(abs(bits_errados)~=0));

  BER(k) = N_bits_errados(k)/Nbits;

  %% Cálculo da probabilidade de erro teórica
  P_b(k) = qfunc(d/(2*sqrt(variancia(k))));
end

% Cálculo de Eb/N0

N_0 = 2*variancia/fs;

E_b = Tb;

Eb_N0 = E_b./N_0;

Eb_N0_dB = 10*log10(Eb_N0);

fprintf('Var. \t  Bits \t  Eb/N0(dB) \t BER \t   Pb teorica\n')
fprintf('\t errados\n')

for k =1:length(variancia)
    fprintf('%g\t  %g\t  %g\t %g\t   %g\t\n', variancia(k), N_bits_errados(k), Eb_N0_dB(k), BER(k), P_b(k))
end
