% Inicialização:
K = 20; % Número de amostras por bit

% Período de bit
Tb = 1/1000;

%% Período de amostragem
fs = K/Tb;
Ts = 1/fs;

% vector dos tempos
t = [0:Ts:Tb];

% Definição das formas de onda:
A = 1;

s_0 = A*ones(1, K); % forma de onda do símbolo "0": impulso positivo <----

s_1 = -s_0; % forma de onda do símbolo "1"

% Inicialização dos vectores de saída
x = zeros(1,K);
y = zeros(1,K);


% Resposta do filtro óptimo

h_opt = s_0(end:-1:1);

% Case 1: noise-N(O,O)
noise = random('Normal', 0, 0, 1, K);

% Sub-case s = s_0:
s = s_0;

x = s+noise;

% Resposta do filtro adaptado
% O factor Ts resulta da conversão da convolução contínua para discreta
y = Ts*conv(x,h_opt);


% Plotting the results:
subplot(3,2,1)
plot(t/Tb,[0 y(1:K)],'-k')
title('(a) \sigma^2 = 0 & s_0','fontsize',10)
xlabel('t/T_b')
axis([0 1 -1.5e-3 1.5e-3])
grid

% Sub-case s = s_1:
s=s_1;

x=s+noise;

y=Ts*conv(x,h_opt);

% Plotting the results:
subplot(3,2,2)
plot(t/Tb,[0 y(1:K)],'-k')
title('(b) \sigma^2= 0 & s_1','fontsize',10)
xlabel('t/T_b')
axis([0 1 -1.5e-3 1.5e-3])
grid

%____________________________________________________

% Case 2: noise-N(0,0.1) %sigma = 0.1
noise=random('Normal', 0, 0.1, 1, K);


% Sub-case s = s_0:
s = s_0;

x = s+noise;

y = Ts*conv(x,h_opt);

% Plotting the results:
subplot(3,2,3)
plot(t/Tb,[0 y(1:K)],'-k')
title('(c) \sigma2= 0.1 & s_{0}','fontsize',10) %
xlabel('t/T_b')
axis([0 1 -1.5e-3 1.5e-3])
grid

%Sub-case s = s_1:
s = s_1;

x = s+noise; % received signal <----

y = Ts*conv(x,h_opt);

% Plotting the results:
subplot(3,2,4)
plot(t/Tb,[0 y(1:K)],'-k')
title('(d) \sigma^2 = 0.1 & s_1','fontsize',10)
xlabel('t/T_b')
axis([0 1 -1.5e-3 1.5e-3])
grid

%___________________________________________________
% Case 3: noise-N(O,1), sigma = 1
noise = random('Normal', 0, 1, 1, K);

% Sub-case s = s_0:
s = s_0;

x = s + noise;

y = Ts*conv(x,h_opt);

% Plotting the results:
subplot(3,2,5)
plot(t/Tb,[0 y(1 :K)],'-k')
title('(e) \sigma^2= 1 & s_0','fontsize',10)
xlabel('t/T_b')
axis([0 1 -1.5e-3 1.5e-3])
grid

% Sub-case s = s_1:
s = s_1;

x=s + noise;

y=Ts*conv(x,h_opt);

% Plotting the results:
subplot(3,2,6)
plot(t/Tb,[0 y(1 :K)],'-k')
title('(f) \sigma^2= 1 & s_{1}','fontsize',10)
xlabel('t/T_b')
axis([0 1 -1.5e-3 1.5e-3])
grid

% Questões
fprintf('Qual o instante ideal de amostragem?\n')

Q1 = Tb;

fprintf('Q1 =%g (s)\n',Q1)


fprintf('Sem ruído adicionado qual o valor da forma de onda no instante de amostragem?\n')

%símbolo s0
Q2_s0 =  1e-3;
fprintf('Q_s0 =%g\n',Q2_s0')


Q2_s1 = -1e-3;
fprintf('Q_s1 =%g\n',Q2_s1')

fprintf('Admitindo que o ruído nos níveis "0" e "1" são iguais e que ocorrem igual probabilidade, qual o valor óptimo para o nível de decisão?\n')

Q3 = 0;
fprintf('Q_3 =%g\n',Q3')

fprintf('Se o ruído do nível "1" for 2x superior ao ruído do nível "0", calcule neste caso o valor óptimo do nível de decisão\n')

sigma0 = 0.25;
sigma1 = 2*0.25;
Q4 = ((2^(1/2)*(3*log(2) + 32)^(1/2))/6 - 5/3);
fprintf('Q4 =%g\n',Q4')
