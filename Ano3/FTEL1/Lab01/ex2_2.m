L = 32;
N = log2(L);
A = 87.6;
Max = 1;
Min = -Max;

Fs = 10e3;
Ts = 1/Fs;
TSim = 1;
T = [0:Ts:TSim];
X = (3*cos(40*pi*T) + 2*sin(240*pi*T))*(1/4.902);

[Boundary, Codebook, Delta] = quantizationInfo(N, Min, Max);

Xc = compand(X, A, Max, 'A/compressor');
[~, Xq] = quantiz(Xc, Boundary, Codebook);
Z = compand(Xq, A, Max, 'A/expander');

figure(1); clf; hold on;
plot(T, X);
plot(T, Z, 'o');
