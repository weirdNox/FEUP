Max =  1.5;
Min = -Max;
X = [1.2 -0.4 0.1];

Miu = 10;
Zc = compand(X, Miu, Max, 'mu/compressor');

N = 4;
[Boundary, Codebook, Delta] = quantizationInfo(N, Min, Max);
[~, Zq] = quantiz(Zc, Boundary, Codebook);

Z = compand(Zq, Miu, Max, 'mu/expander');

%% figure(1); clf; hold on;
%% plot(1:length(X), X);
%% plot(1:length(Z), Z);
