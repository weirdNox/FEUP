NumPoints = 30;
N = [0:NumPoints-1];

X = [ones(1, 10) zeros(1, NumPoints-10)];
H = 2.^(-N);
Conv = conv(X, H);

figure(1); clf; hold on;
plot(N, Conv(1:NumPoints));
stem(N, Conv(1:NumPoints));
