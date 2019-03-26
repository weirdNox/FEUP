wn = [2/5 3/5];
[Num, Den] = butter(3, wn, 'stop');
freqz(Num, Den)
[H W] = freqz(Num, Den);

figure(1); clf;
plot(W/pi, abs(H));

figure(2); clf;
zplane(Num, Den);
