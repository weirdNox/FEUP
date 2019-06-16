Numerator = 2;
Denominator = [1 0.4];

Length = 50;
TimeN = [0:Length-1];
Input = ones(1, Length);

Output = filter(Numerator, Denominator, Input);
Expected = 2 * (1 - (-0.4).^(TimeN + 1)) ./ 1.4;

figure(1); clf;
subplot(2, 1, 1); hold on; grid on;
stem(TimeN, Output);

subplot(2, 1, 2); hold on; grid on;
stem(TimeN, Expected);
