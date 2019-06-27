Amax = 0.3;
Amin = 15;

Fp = 1e6; Wp = Fp*2*pi;
Fr = 1.5e6;

Epsilon = sqrt(10.^(Amax / 10) - 1);
N = ceil(acosh(sqrt(10.^(Amin / 10) - 1) ./ Epsilon) ./ acosh(Fr/Fp))

[Zeros, Poles, K] = cheb1ap(N, Amax);

Den = poly(Poles);
NormCoefs = longDivisionSynthesis(Den);

Rc = 250
L1 = NormCoefs(1) *  Rc / Wp
C2 = NormCoefs(2) / (Rc * Wp)
L3 = NormCoefs(3) *  Rc / Wp
C4 = NormCoefs(4) / (Rc * Wp)
