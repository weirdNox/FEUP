B = 0.3
A = [1 -0.7];
X = [1 zeros(1, 49)];
Y = filter(B, A, X);

figure(1); clf;
stem([0:length(Y)-1], Y);
