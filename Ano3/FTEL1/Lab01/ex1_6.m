%% Intervalo onde o sinal está definido
m_max =1;
m_min =-1;

%% frequência de amostragem
fs = 10e3;

%% tempo de amostragem ts
ts = 1/fs;

%% tempo de simulação 1 s
tsim = 1;

%% instantes de amostragem
t = [0:ts:tsim];

%% Cálculo do sinal de entrada
x_in = (3*cos(40*pi*t) + 2*sin(240*pi*t))*(1/4.902);

%% Nº de bits/amostra
N = 2:6;

for n=1:length(N)
  N(n)
  [Pot_teorico(n), Pot_est(n), NQ_teorico(n), NQ_est(n), SNR_dB_teorico(n), SNR_dB_est(n)]= signal_quantizer(x_in,N(n),m_min,m_max,fs);
end

format shortg
tabela = [N', Pot_est', NQ_est', SNR_dB_est', SNR_dB_teorico']

%% Observe os espectros obtidos e diga se a seguinte afirmação é verdadeira ou falsa

fprintf('Q1: H%s medida que se aumentam os n%sveis de quantiza%s%so,\n ', char(225), char(237), char(231), char(227))
fprintf('o espectro do sinal quantizado aproxima-se do sinal de entrada. (V/F)?\n\n')

%% Introduza a sua resposta no vector 'Resposta'
%% Resposta = 'V' ou Resposta = 'F'

Resposta_1 = 'V';

fprintf('Q2: Os valores estimados e te%sricos da rela%s%so sinal ru%sdo de quantiza%s%so diferem um pouco.\n',char(243), char(231), char(227),char(237),char(231), char(227) )
fprintf('A que atribui esse facto? (op%s%so: 1, 2 ou 3)\n\n', char(231), char(227))

%% Introduza a sua resposta no vector 'Resposta_2'
%% Resposta_2 = '1' ou Resposta_2 = '2' ou Resposta_2 = '3'

Resposta_2 = '3';

%%--------------------%%%%%%%%%%%%%%%%%%--------------------%%

function [P_teorico, P_est, NQ_teorico, NQ_est, SNR_dB_teorico, SNR_dB_est] = signal_quantizer(x,Nbits, m_min,m_max, fs)

  [boundary, codebook, delta] = scalar_quantizer_enconder(Nbits, m_min, m_max)

  [idx, xq ] = mquantiz(x, boundary, codebook);

  eq = x-xq;

  NQ_teorico = delta^2/12;

  NQ_est = mean(eq.^2);

  P_est = mean(x.^2);

  P_teorico = ((3/4.902)^2 + (2/4.902)^2)/2;

  SNR_dB_est = 10*log10(P_est/NQ_est);

  SNR_dB_teorico = 1.8 + 6*Nbits + 20*log10(m_max/m_max);

  %% gráfico do espectro do sinal x e do correspondente sinal de saída quantizado

  if (Nbits == 2) || (Nbits == 6)
    figure
    subplot(2,1,1)
    pwelch(x,[],[],[],fs)
    axis([0 0.5 -80 -15])
    subplot(2,1,2)
    pwelch(xq,[],[],[],fs)
    axis([0 0.5 -80 -15])
  end

end
