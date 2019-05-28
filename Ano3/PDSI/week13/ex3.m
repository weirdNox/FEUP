%% ====================================================================================================
%% NOTE(nox): Parameters
SamplingTime = 0.04; % NOTE(nox): In seconds
SamplingFreq = 6000;
FftLength = 2048;

UpsamplingFactor = 3;
FilterLength = 61;

%% ====================================================================================================
%% NOTE(nox): Sampling
SamplingPeriod = 1/SamplingFreq;
SamplingInstants = [0 : SamplingPeriod : SamplingTime-SamplingPeriod];

Signal = 3*cos(2*pi*500*SamplingInstants) + 2*cos(2*pi*750*SamplingInstants) + cos(2*pi*1000*SamplingInstants);
[H, W] = freqz(Signal, 1.0, FftLength, 'whole', SamplingFreq);

%% ====================================================================================================
%% NOTE(nox): Upsampling
UpsampledFreq = UpsamplingFactor*SamplingFreq;
UpsampledPeriod = 1/UpsampledFreq;

UpsampledSignal = upsample(Signal, UpsamplingFactor);
[UpsampledPsd, W] = freqz(UpsampledSignal, 1.0, FftLength, 'whole', UpsampledFreq);

%% ====================================================================================================
%% NOTE(nox): Filtering
Time = [0 : FilterLength-1];
Delay = (FilterLength - 1)/2;

%% NOTE(nox): sinc() is centered at the origin, so we need to center it by subtracting the delay
FilterImpResp = sinc((Time - Delay) / UpsamplingFactor);
[FilterFreqResp Freqs] = freqz(FilterImpResp, 1.0, FftLength, 'whole');

FilteredSignal = conv(UpsampledSignal, FilterImpResp);
[FilteredPsd, W] = freqz(FilteredSignal, 1.0, FftLength, 'whole', UpsamplingFactor*SamplingFreq);

%% ====================================================================================================
%% NOTE(nox): Visualization
figure(1); clf;
plot(W, abs(H))
xlabel('Frequência (Hz)');
ylabel('Magnitude');
title('Espectro do sinal de entrada');

figure(2); clf;
plot(Freqs/pi, abs(FilterFreqResp));

figure(3); clf;
plot(W, abs(UpsampledPsd));
title('Espetro do sinal sobreamostrado');

figure(4); clf;
plot(W, abs(FilteredPsd));
title('Espetro do sinal sobreamostrado e filtrado');

figure(5); clf;
subplot(3, 1, 1); grid; hold on;
plot([0:SamplingPeriod:SamplingTime-SamplingPeriod], Signal);
title('Sinal original');

subplot(3, 1, 2); grid; hold on;
plot([0:UpsampledPeriod:SamplingTime-UpsampledPeriod], UpsampledSignal);
title('Sinal sobreamostrado');

subplot(3, 1, 3); grid; hold on;
plot([0:UpsampledPeriod:SamplingTime-UpsampledPeriod], FilteredSignal(1+Delay:end-Delay));
title('Sinal sobreamostrado e filtrado');
