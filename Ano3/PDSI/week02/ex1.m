N = 5;
H = ones(1, N) / N;
Seq = [0:N-1];

figure(1); clf; hold on;
stem(Seq, H);
axis([-1 N 0 1/N*1.2]);
xlabel('n \rightarrow');
ylabel('Amplitude \rightarrow');


[Ht W] = freqz(H, 1.0, 512, 'whole');

%% Plot normalized by Pi
figure(2); clf;
subplot(2, 1, 1); hold on; grid on;
plot(W / pi, abs(Ht));
xlabel('\omega/\pi');
ylabel('Magnitude');

subplot(2, 1, 2);  hold on; grid on;
plot(W / pi, angle(Ht) / pi);
xlabel('\omega/\pi');
ylabel('Phase');
