Duration = 3;

BitDepth = 16;
SamplingFrequency = 22050;

Recording = audiorecorder(SamplingFrequency, BitDepth, 1);
recordblocking(Recording, Duration);

Audio = getaudiodata(Recording, 'single').';

%% NOTE(nox): Frequency reversal
Audio1 = (-1).^[0:length(Audio)-1] .* Audio;

%% NOTE(nox): Interpolation
InterpolationFactor = 3;
FilterLength = 101;

FilterDelay = (FilterLength-1)/2;
FilterImpResp = sinc(([0 : FilterLength-1] - FilterDelay) / InterpolationFactor);

Audio2 = conv(upsample(Audio, InterpolationFactor), FilterImpResp);

%% NOTE(nox): Time reversal
Audio3 = Audio(length(Audio):-1:1);
