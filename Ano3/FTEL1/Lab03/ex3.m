%% Formatacao em cosseno elevado
% Parametros da simulacao
R = 1000;
T = 1/R;
fc = 10*R;
A = 1;
fs = 10*fc;
ts = 1/fs;
t_sim = 1000*T;
N_bits = R*t_sim;
N_amostras_bit = fs/R;
t = ts:ts:t_sim;

% inicializar com zeros
x_bits = zeros(1, N_bits);

% semente do gerador
rng(37)
% sequencia aleatoria de zeros e uns
x_bits = randi(2, 1, N_bits)-1;

% sinal binario polar
x = x_bits*2-1;

% para usar no filtro em cosseno elevado
rolloff = [0 0.5 1];
span = 8;
sps = N_amostras_bit;

% obter os graficos temporais banda base e banda de canal e espetro PSK
fig_numbr = 1;
for j = 1:length(rolloff)
    % coeficientes do filtro em cosseno elevado
    rcosFilter = rcosdesign(rolloff(j), span, sps, 'normal');
    % sinal polar filtrado
    x_rcos = upfirdn(x, rcosFilter, N_amostras_bit);
    % multiplicar x_rcos por um ganho de 10 e truncar vetor r_rcos ao comprimento de t
    x_rcos = 10*x_rcos(1:length(t));

    % gerar o sinal BPSK
    portadora = A*sin(2*pi*fc*t);
    x_psk = x_rcos.*portadora;

    % plot de 10 bits do 20 ao 30
    figure(fig_numbr)
    subplot(311)
    plot([10*T:ts:20*T], x_rcos(1,10*N_amostras_bit : 20*N_amostras_bit)),
    title(strcat('Sinal Polar com roll-off =',num2str(rolloff(j)))), grid on,
    axis([10*T 20*T -2 2])
    subplot(312)
    plot([10*T:ts:20*T], x_psk(1,10*N_amostras_bit : 20*N_amostras_bit)), title('Sinal BPSK')
    grid on, axis([10*T 20*T -2 2])
    subplot(313)
    % plot do espetro
    pwelch(x_psk, [],[],8192, fs), title('Sinal BPSK'), grid on
    axis([8 12 -100 0])

    fig_numbr = fig_numbr + 1;
end

% obter os diagramas de olho
for j = 1:length(rolloff)
    rcosFilter = rcosdesign(rolloff(j), span, sps, 'normal');
    x_rcos = upfirdn(x, rcosFilter, N_amostras_bit);
    x_rcos = 10*x_rcos(1:length(t));
    eyediagram(x_rcos(10*N_amostras_bit:length(x_rcos)),2*N_amostras_bit,T)
end

%%% Pergunta 1 %%%
% Larguras de banda
% Para o caso de roll off 0.75 a largura de banda, em Hz, do sinal PSK sera:
% Opcoes: 650 ; 1000 ; 1300
Resposta1 = '1300';

%%% Pergunta 2 %%%
% Interferencia inter-simbolica
% Pode correr esta simulacao usando filtro em raiz de cosseno elevado
% Se usarmos este filtro apenas no recetor nao teremos ISI (Verdadeiro ou falso?)
% Opcoes: V ; F
Resposta2 = 'F';

%%% Pergunta 3 %%%
% Fator de roll-off
% Supondo que o relogio recuperado no recetor tem ruido de fase,
% nesse caso e' preferivel usar o fator de roll-off de valor
% Opcoes: 0 ; 0.5 ; 1
Resposta3 = '1';
