Alfa = 0.8*exp(j*pi/3);
Num = poly([Alfa Alfa' Alfa Alfa'])/abs(Alfa)^2;
Den = 1.0;

ImpulseResponse = impz(Num, Den);

figure(1); clf; hold on; grid;
stem([0:length(ImpulseResponse)-1], ImpulseResponse);
axis([-1 length(Num) -3 4]);

figure(2); clf;
zplane(Num, Den);

figure(3); clf;
plot(grpdelay(Num, Den));

figure(4); clf;
freqz(Num, Den, 512);
