Max = 1;
Min = -Max;

Fs = 10e3;
Ts = 1/Fs;
TSim = 1;
T = [0:Ts:TSim];
X = (3*cos(40*pi*T) + 2*sin(240*pi*T))*(1/4.902);

N = [3, 5, 7];

quantAnalysis(X,    N, Min, Max);
quantAnalysis(X/10, N, Min, Max);

fprintf('Q1: SNR não varia tanto com a quantização não uniforme (V/F) -> %s\n', 'V');

function [SigPower, NoisePower, SnrDb, NoisePowerA, SnrDbA] = compQuantizExp(X, N, Min, Max)
  SigPower = mean(X.^2);
  [Boundary, Codebook, Delta] = quantizationInfo(N, Min, Max);

  %% ------------------------------------------------------------------------------------------
  %% Non-uniform quantization: Lei A
  [~, XQuant] = quantiz(X, Boundary, Codebook);

  QuantErr = X - XQuant;
  NoisePower = mean(QuantErr.^2);

  SnrDb = 10*log10(SigPower/NoisePower);

  %% ------------------------------------------------------------------------------------------
  %% Non-uniform quantization: Lei A
  A = 87.6;
  XComp = compand(X, A, Max, 'A/compressor');
  [~, XCompQuant] = quantiz(XComp, Boundary, Codebook);
  XExpanded = compand(XCompQuant, A, Max, 'A/expander');

  QuantErrA = X - XExpanded;
  NoisePowerA = mean(QuantErrA.^2);

  SnrDbA = 10*log10(SigPower/NoisePowerA);
end

function quantAnalysis(X, N, Min, Max)
  fprintf('%-1s  %-4s  %-12s  %-12s  %-16s  %-16s  %-16s\n', 'N', 'L', 'Potência (W)', 'Ruído (W)', 'SNR Unif (dB)', 'Ruído Lei A (W)', 'SNR Lei A (dB)');
  for Idx = 1:length(N)
    [SigPower, NoisePower, SnrDb, NoisePowerA, SnrDbA]= compQuantizExp(X, N(Idx), Min, Max);
    fprintf('%-1i  %-4i  %-12g  %-12g  %-16g  %-16g  %-16g\n', N(Idx), 2^N(Idx), SigPower, NoisePower, SnrDb, NoisePowerA, SnrDbA);
  end
  fprintf('\n')
end
