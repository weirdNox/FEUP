N = 8;
Time = [0 : N-1];
K = Time;
X = 0.5*(1 - cos(2*pi*Time/N));

DftX = fft(X);

figure(1); clf;
stem(K, real(DftX));
axis([-1 8 -3 5]);
