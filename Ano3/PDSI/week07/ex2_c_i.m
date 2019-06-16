Beta = 0.5*exp(j*pi/4);
Num = conv([-Beta' 1], [-Beta 1]);
Den = conv([1 -Beta], [1 -Beta']);

[FreqResp, Freqs] = freqz(Num, Den, 512);
figure(1); clf;
plot(Freqs, abs(FreqResp));

figure(2); clf;
plot(grpdelay(Num, Den));

figure(3); clf;
zplane(Num, Den);
