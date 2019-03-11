% Nº de bits N

N = 5;

m_min = -1;
m_max = 1;

[boundary, codebook, delta] = scalar_quantizer_enconder(N, m_min, m_max)

% frequência de amostragem
fs = 10e3; % 10kHz

% tempo de amostragem ts
ts = 1/fs;

% intervalo de simulação de 0 a 0.1s, com passo ts (segundos)
t = [0:ts:1];

x_in = (3*cos(40*pi*t) + 2*sin(240*pi*t))*(1/4.902);

subplot(3,1,1)
plot(t,x_in)
xlabel('t (s)')
ylabel('x_{in}')

% sinal quantizado xq : use a função mquantiz
[idx, xq] = mquantiz(x_in, boundary, codebook);

subplot(3,1,2)
plot(t,x_in,t,xq,'+')
xlabel('t (s)')
ylabel('x_{in}, x_q')

% sinal de erro
eq = x_in - xq;

subplot(3,1,3)
plot(t,eq)
xlabel('t (s)')
ylabel('e_q')

% erro máximo
max_eq_est = max(eq)
fprintf('%6.2f\n',max_eq_est)

%Erro máximo teórico
max_eq_teorico = delta/2

% potência teórica de ruído de quantização
NQ_teorico = delta^2/12

% potência do ruído de quantização
NQ_est = sum(eq.^2)/length(eq)

% potência do sinal
P = sum(x_in.^2)/length(x_in)

% Razão sinal-ruído
SNR_dB = 10*log10(P/NQ_est)
