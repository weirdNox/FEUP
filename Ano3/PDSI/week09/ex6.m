%% NOTE(nox): Signal from the exercise
X0 = [0 1 1 0];
X  = [zeros(1, length(X0)), X0];

X0Dft = fft(X0);
XDft  = fft(X);

SpacedX0Dft = reshape([X0Dft; zeros(size(X0Dft))], 1, []);

figure(1); clf;
subplot(3, 1, 1); hold on;
stem([0:1:length(X)-1], X);

subplot(3, 1, 2); hold on;
plot([0:1:length(XDft)-1], abs(XDft),  '-o');
plot([0:2:length(XDft)-1], abs(X0Dft), '-o');

subplot(3, 1, 3); hold on;
plot([0:1:length(XDft)-1], angle(XDft),  '-o');
plot([0:2:length(XDft)-1], angle(X0Dft), '-o');

%% NOTE(nox): Other signal
N = 1024*4;
Time = linspace(0, 4*pi, N);
X0 = sawtooth(Time);
X  = [zeros(1, length(X0)), X0];

X0Dft = fft(X0);
XDft  = fft(X);

figure(2); clf; hold on;
plot([0:1:length(XDft)/2-1], abs(XDft(1:length(XDft)/2)),   '-o');
stem([0:2:length(XDft)/2-1], abs(X0Dft(1:length(X0Dft)/2)), 'm');
