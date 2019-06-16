Num = [1 -.4];
Den = [1 -.8 .64];

figure(1); clf;
zplane(Num, Den);

MaxLen = max(length(Num), length(Den));
Zeros = roots([Num, zeros(1, MaxLen - length(Num))])

[Residues, Poles, Direct] = residuez(Num, Den)

[ImpResp, TimeN] = impz(Num, Den, 40);
figure(2); clf;
stem(TimeN, ImpResp);
