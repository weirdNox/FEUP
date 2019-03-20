Num = [1 2 1];
Den = [1 -0.5 -0.5];

ImpulseResponse = impz(Num, Den, 30);

figure(1);
stem([0:length(ImpulseResponse)-1], ImpulseResponse);

CalculatedImpulseResponse = 8/3 + 1/3*(-1/2).^[0:length(ImpulseResponse)-1];
CalculatedImpulseResponse(1) = CalculatedImpulseResponse(1) - 2;

figure(2);
stem([0:length(ImpulseResponse)-1], ImpulseResponse.' - CalculatedImpulseResponse);
