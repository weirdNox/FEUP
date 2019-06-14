Num = 0;
while Num < 30
    Num = input('Insert a number (>= 30) ');
end
NumSequence = [0:Num-1];

Alpha = 0.95*exp(j*pi/3);
H = Alpha.^NumSequence;

figure(1); clf;
plot(NumSequence, abs(H));
title('Complex exponential');
xlabel('NumSequence \rightarrow');
ylabel('Magnitude \rightarrow');
legend('Envelope');

figure(2); clf;
subplot(3, 1, 1);
stem(NumSequence, real(H));

subplot(3, 1, 2);
X = [zeros(1, 20) ones(1, 10) zeros(1, Num-30)];
stem(NumSequence, X);

subplot(3, 1, 3);
Y = conv(X, real(H));
stem(NumSequence, Y(1:Num), 'pentagram');

%% NOTE(nox): Extra questions
%% i) sum(H .* conj(H)) → Sum of the element-wise multiplication between H and its conjugate
%%    H * H' → Calculates the conjugate transposition of H and multiplies it with H
%%
%%    Both are the dot product of H with itself (complex dot produt).

%% ii) For real vectors, there is no difference between ' and .'; however, for complex vectors, it is an
%%     alternative definition for the dot product that loses some properties.
%%     H .* H is just the element-wise multiplication with itself.

%% iii) We could have used filter with 1 as the denominator; the difference is that the length of the
%%      returned vector would already be the size of the input vector

%% iv) whos is the long form version of who
