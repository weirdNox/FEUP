N = 2;

[Zeros Poles K] = buttap(N);
Num = poly(Zeros);
Den = poly(Poles);

Coef = longDivisionSynthesis(Den);

R = 75;
L1 = Coef(1)*B*R/W0^2
C1 = 1/(Coef(1)*B*R)
L2 = R/(Coef(2)*B)
C2 = Coef(2)*B/(W0^2*R)
