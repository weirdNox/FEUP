figure(1); clf; hold on;

%% Using filter
X = [1/2 1 1/2 0 0];
B = [1/4 1/4 1/4];
A = 1;
Y = filter(B, A, X);

N = [0:length(Y)-1];
stem(N, Y, '+');


%% After solving for the impulse response
X = [1/2 1 1/2];
H = [1/4 1/4 1/4];
Y = conv(X, H);

N = [0:length(Y)-1];
stem(N, Y);
