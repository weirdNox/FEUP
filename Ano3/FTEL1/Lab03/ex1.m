%% Formas de onda e densidades espetrais de potencia de OOK e ASK

%% Parametros da simulacao
R = 1000; % debito binario
T = 1/R;
fc = 10*R; % frequencia da portadora
A = 1; % amplitude da portadora
fs = 10*fc; % frequencia de amostragem
ts = 1/fs;
t_sim = 1000*T; % mulltiplo de T
N_bits = R*t_sim;
N_amostras_bit = fs/R;
t = ts:ts:t_sim; % vetor do tempo

%% inicializar com zeros o vetor para guardar os bits gerados
x_bits = zeros(1, N_bits);

%% inicializar com zeros o vetor das amostras do sinal banda base
x = zeros(1, N_amostras_bit*N_bits);

%% semente do gerador
rng(37)
%% sequencia aleatoria de zeros e uns
x_bits = randi(2, 1, N_bits)-1;

%% sinal binario unipolar amostrado com N_amostras_bit
for j = 1:N_bits
    x(1, (j-1)*N_amostras_bit+1:j*N_amostras_bit) = x_bits(1,j);
end

%% gerar o sinal OOK
portadora = A*sin(2*pi*fc*t);
x_ook = x.*portadora;

%% gerar o sinal banda base de 2V e 5V a partir do sinal banda base x
x_2_5 = zeros(1,length(x));
x_2_5(find(x)) = 5;
x_2_5(find(1-x)) = 2;

%% gerar o sinal ASK modulando a portadora
x_ask = x_2_5.*portadora;

%% figura com os dez primeiros bits de x e x_2_5 e correspondentes sinais OOK e ASK
figure(1)
subplot(221)
plot([0:ts:10*T],[0 x(1,1:10*N_amostras_bit)]), title('Sinal Unipolar')
axis([0 10*T -2 2]), grid on
subplot(223)
plot([0:ts:10*T],[0 x_ook(1,1:10*N_amostras_bit)]), title('Sinal OOK')
axis([0 10*T -2 2]), grid on
subplot(222)
plot([0:ts:10*T],[0 x_2_5(1,1:10*N_amostras_bit)]), title('Sinal de 2V e 5V')
axis([0 10*T 0 6]), grid on
subplot(224)
plot([0:ts:10*T],[0 x_ask(1,1:10*N_amostras_bit)]), title('Sinal ASK')
axis([0 10*T -6 6]), grid on

%%% valores medios e potencias %%%
%% sinal x
x_dc = mean(x);
x_dc_teorico = mean([0 1]);
P_x = mean(x.^2);
P_x_teorico = ((1-0)/2)^2 + x_dc_teorico^2;
%sinal x_2_5
x_2_5_dc = mean(x_2_5);
x_2_5_dc_teorico = mean([2 5]);
P_x_2_5 = mean(x_2_5.^2);
P_x_2_5_teorico = ((5-2)/2)^2 + x_2_5_dc_teorico^2;
%% sinal OOK, x_ook
P_x_ook = mean(x_ook.^2);
P_x_ook_teorico = mean([1^2/2 0^2/2]);
%% sinal ASK 2V e 5V, x_ask
P_x_ask = mean(x_ask.^2);
P_x_ask_teorico = mean([5^2/2 2^2/2]);

%% gerar os espetros dos sinais OOK e ASK
figure(2)
subplot(221), pwelch(x, [],[],8192, fs), title('Sinal Unipolar')
axis([0 4 -100 0])
subplot(223), pwelch(x_ook, [],[],8192, fs), title('Sinal OOK')
axis([6 14 -100 0])
subplot(222), pwelch(x_2_5, [],[],8192, fs), title('Sinal de 2V e 5V')
axis([0 4 -100 0])
subplot(224), pwelch(x_ask, [],[],8192, fs), title('Sinal ASK')
axis([6 14 -100 0])

%%% Pergunta %%%
%% Qual a largura de banda do sinal ASK
%% Opcoes: R/2 ; R ; 2R ; 3/2R
%% Introduza a resposta no vetor Resposta
Resposta = '2R';
