[Sound, SamplingFreq] = audioread('vogal.wav');
SampleCount = length(Sound);

SliceLength = 512;
FirstSample = 2.7339e4;
Range = [FirstSample : FirstSample+SliceLength-1];
Slice = Sound(Range);

AutoCorr = xcorr(Slice);

PaddedDft = fft(Slice, 2*SliceLength);
PaddedDft = abs(PaddedDft).^2;
Result = ifft(PaddedDft);
Result = fftshift(Result); % NOTE(nox): In order to move the 0 to the center

figure(1); clf; grid; hold on;
plot([0:SampleCount-1], Sound);
plot(Range, Slice, 'r');
xlabel('Amostra');
ylabel('Amplitude');

figure(2); clf; grid; hold on;
plot([1 : 2*SliceLength-1] - SliceLength, AutoCorr);
plot([1 : 2*SliceLength] - SliceLength - 1, Result);
