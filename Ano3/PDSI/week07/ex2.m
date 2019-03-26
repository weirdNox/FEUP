Alfa = 0.8*exp(j*pi/3);
Num = poly([Alfa Alfa' 1/Alfa 1/Alfa']);
Den = 1.0;

ImpulseResponse = impz(Num, Den, 8);

figure(1);
stem([0:length(ImpulseResponse)-1], ImpulseResponse);
axis([-1 8 -3 4]);

figure(2);
zplane(Num, Den);

%% Group delay is 2 samples, which can easily be seen in FIR filters by the distance from 0 to the center
%% of the impulse response
figure(3);
plot(grpdelay(Num, Den));
