N = 64;
Time = [0 : N-1];
K = Time;
YDft = 1 ./ (1 - .5*exp(-j * K * 2 * pi / N));
Y = ifft(YDft);

AnalyticY = (2 .^ (-Time)) ./ (1 - 2^(-N));

figure(1); clf;
subplot(3, 1, 1);
stem(real(Y));

subplot(3, 1, 2);
stem(AnalyticY);

subplot(3, 1, 3);
stem(real(Y) - AnalyticY);
