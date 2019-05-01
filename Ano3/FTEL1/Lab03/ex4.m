%% Detecao coerente de BPSK e OOK
% Parametros da simulacao
R = 1000;
T = 1/R;
fc = 10*R;
A = 1;
fs = 10*fc;
ts = 1/fs;
t_sim = 5000*T; % simulacao de 5s
N_bits = R*t_sim;
N_amostras_bit = fs/R;
t = ts:ts:t_sim;

% inicializar com zeros vetores dos bits na emissao e rececao
x_bits = zeros(1, N_bits);
xr_psk_bits = zeros(1, N_bits);
xr_ook_bits = zeros(1, N_bits);

% inicializar com zeros o vetor das amostras do sinal unipolar
x = zeros(1, N_bits*N_amostras_bit);

% semente do gerador
rng(37);
% sequencia aleatoria de zeros e uns
x_bits = randi([0 1],[1 N_bits]);

% sinal binario unipolar amostrado
for j = 1:N_bits
    x(1, (j-1)*N_amostras_bit+1:j*N_amostras_bit) = x_bits(1,j);
end

% gerar sinais ook e psk
portadora = A*sin(2*pi*fc*t);
x_ook = x.*portadora;
x_psk = (2*x-1).*portadora;

% parametros para PSK
var_psk = [10 20 40 80];
Eb_psk = A^2/2*T;
No_psk = 2*var_psk/fs;
EbNo_psk = Eb_psk./No_psk;
EbNodB_psk = 10*log10(EbNo_psk);

% parametros para OOK
var_ook = var_psk/4;
Eb_ook = A^2/2*T/2;
No_ook = 2*var_psk/fs;
EbNo_ook = Eb_ook./No_ook;
EbNodB_ook = 10*log10(EbNo_ook);

for j = 1:length(var_psk)
   % ____________________________ PSK ____________________________
    rng(67);
    ruido = random('Normal', 0, sqrt(var_psk(j)), 1, length(x_psk));
    % sinal psk recebido com ruido
    xr_psk = x_psk + ruido;
    % desmodulacao, decisao e probabilidade de erro estimada e teorica de psk
    G = 2; % para compensar o fator 1/2 do produto
    y_psk = (xr_psk.*portadora)*G; % obter sinal antes do integrador usando o gnaho G = 2
    z_psk = intdump(y_psk, N_amostras_bit);
    nivel_decisao_psk = 0;
    xr_psk_bits(find(z_psk >  nivel_decisao_psk)) = 1;
    xr_psk_bits(find(z_psk <= nivel_decisao_psk)) = 0;
    N_bits_errados_psk(j) = sum(abs(x_bits-xr_psk_bits));
    Pe_psk(j) = N_bits_errados_psk(j)/N_bits;
    Pe_psk_teor(j) = qfunc(sqrt(2*EbNo_psk(j)));

    %% OOK
    rng(76);
    ruido = random('Normal', 0, sqrt(var_ook(j)), 1, length(x_ook));
    xr_ook = x_ook + ruido;
    G = 2;
    y_ook = (xr_ook.*portadora)*G;
    z_ook = intdump(y_ook, N_amostras_bit);
    nivel_decisao_ook = 0.5;
    xr_ook_bits(find(z_ook >  nivel_decisao_ook)) = 1;
    xr_ook_bits(find(z_ook <= nivel_decisao_ook)) = 0;
    N_bits_errados_ook(j) = sum(abs(x_bits-xr_ook_bits));
    Pe_ook(j) = N_bits_errados_ook(j)/N_bits;
    Pe_ook_teor(j) = qfunc(sqrt(EbNo_ook(j)));

end

% visualizar resultados das simulacoes
Pe_psk
Pe_psk_teor
Pe_ook
Pe_ook_teor

% gerar o grafico
EBNO_dB = -6:.01:10;
EBNO = 10.^(EBNO_dB/10);
PE_PSK_CURVA = qfunc(sqrt(2*EBNO));
PE_OOK_CURVA = qfunc(sqrt(EBNO));
semilogy(EBNO_dB,PE_PSK_CURVA,EbNodB_psk,Pe_psk,'bo',EBNO_dB,PE_OOK_CURVA,EbNodB_ook,Pe_ook,'ro')
grid on
axis([-6 10 1e-3 1]), legend('P_e (PSK)','P_e estim (PSK)', 'P_e (OOK)','P_e estim (OOK)');

%%% Pergunta %%%
% Nesta simulacao podemos considerar que a portadora do recetor tem um erro de fase ou de frequencia
% Erro de fase na desmodulacao PSK
% Suponha que a portadora do desmodulador PSK apresenta um erro de fase
% Qual o valor do erro de fase que produz maior taxxa de erros?
Resposta = '180'; % coloque na string o valor do erro de fase em graus
