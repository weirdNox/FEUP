Num = 0;
while Num < 30
    Num = input('Insert a number ');
end
NumSequence = [0:Num-1];

Alpha = 0.95*exp(j*pi/3);
H = Alpha.^NumSequence;

figure(1);
plot(NumSequence, abs(H));
title('Complex exponential');
xlabel('NumSequence \rightarrow');
ylabel('Magnitude \rightarrow');
legend('Envelope');

figure(2);
subplot(3, 1, 1);
stem(NumSequence, real(H));

subplot(3, 1, 2);
X = [zeros(1, 20) ones(1, 10) zeros(1, Num-30)];
stem(NumSequence, X);

subplot(3, 1, 3);
Y = conv(X, real(H));
stem(NumSequence, Y(1:Num), 'pentagram');
