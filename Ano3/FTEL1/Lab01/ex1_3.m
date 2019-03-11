function [qnoise_power, SNR_dB] = ex3(N, signal_power)

% Nª de níveis
L = 2^N;

% Intervalo de quantização
m_min = -1;
m_max = 1;

% Diferença entre níveis de quantização
delta = 2*m_max/L


% Potência teórica do ruído de quantização
qnoise_power = delta^2/12

% Razão sinal-ruído
SNR = signal_power/qnoise_power

SNR_dB = 10*log10(SNR)

end
