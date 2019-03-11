Max =  1.3;
Min = -Max;
X = [1.2 -0.4 0.1];
Zc = compand(X, 10, Max, 'mu/compressor');

N = 4;
[Boundary, Codebook, Delta] = quantizationInfo(N, Min, Max);
[~, Zq] = quantiz(Zc, Boundary, Codebook);

Z = compand(Zq, 10, Max, 'mu/expander');

%% figure(1); clf; hold on;
%% plot(1:length(X), X);
%% plot(1:length(Z), Z);
