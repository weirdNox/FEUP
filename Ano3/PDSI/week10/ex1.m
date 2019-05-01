X = [3 2 1 0 0 0];
XDft = fft(X);

Y1 = X - ifft(real(XDft));
Y2 = ifft(j*imag(XDft));

figure(1); clf;
subplot(2, 1, 1); hold on; grid on;
stem(Y1);

subplot(2, 1, 2); hold on; grid on;
stem(Y2);
