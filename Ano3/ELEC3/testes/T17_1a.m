F1 = 100e3;
F2 = 4e6;
F3 = 800e3;
F4 = 1.25e6;

F01 = sqrt(F1*F2);
F02 = sqrt(F3*F4);

F1Prime = F02^2/F2;
F3Prime = F01^2/F4;

Wr1 = (F2 - F1Prime)/(F4-F3);
Wr2 = (F2 - F1)/(F4-F3Prime);

F1 = F1Prime;
Wr = Wr1;
F0 = F02;

B = 2*pi*(F2-F1);
W0 = 2*pi*F0;

Epsilon = 1;
Amax = 10*log10(1 + Epsilon^2);
Amin = 40;
N = ceil(log10((10.^(Amin / 10) - 1) ./ Epsilon.^2) / (2*log10(Wr1)));

[Zeros Poles K] = buttap(N);
Num = poly(Zeros);
Den = poly(Poles);
