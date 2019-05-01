%% Forma de onda e densidade espetral de potencia de BPSK
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

% inicializar com zeros o vetor para guardar os bits gerados
x_bits = zeros(1, N_bits);

% inicializar com zeros o vetor das amostras do sinal
x = zeros(1, N_amostras_bit*N_bits);

% semente do gerador
rng(37)
% sequencia aleatoria de zeros e uns
x_bits = randi(2, 1, N_bits)-1;

% sinal banda base unipolar amostrado
for j = 1:N_bits
    x(1, (j-1)*N_amostras_bit+1:j*N_amostras_bit) = x_bits(1,j);
end

% sinal banda base polar de amplitudes +1V e -1V
x = x*2-1;

% gerar o sinal BPSK
portadora = A*sin(2*pi*fc*t);
x_psk = x.*portadora;

% figura dos 8 bits iniciais
figure(1)
subplot(211)
plot([0:ts:8*T],[0 x(1,1:8*N_amostras_bit)]), title('Sinal Polar')
axis([0 8*T -2 2]), grid on
subplot(212)
plot([0:ts:8*T],[0 x_psk(1,1:8*N_amostras_bit)]), title('Sinal BPSK')
axis([0 8*T -2 2]), grid on

% potencias
P_x = mean(x.^2);
P_x_teorico = 1^2;
P_x_psk = mean(x_psk.^2);
P_x_psk_teorico = 1^2/2;

% gerar o espetro e visualizar o mesmo
figure(2)
subplot(211), pwelch(x, [],[],8192, fs), title('Sinal Polar')
axis([0 6 -100 0])
subplot(212), pwelch(x_psk, [],[],8192, fs), title('Sinal BPSK')
axis([4 16 -100 0])

%%% Pergunta %%%
% Ausencia da risca espetral na frequencia da portadora deve-se a DC nulo do sinal banda base
% Opcoes V ; F
Resposta = 'V';
