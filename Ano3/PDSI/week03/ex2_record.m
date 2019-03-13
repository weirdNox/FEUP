Duration = 5;

BitDepth = 16;
SamplingFrequency = 22050;

Recording = audiorecorder(SamplingFrequency, BitDepth, 1);
recordblocking(Recording, Duration);

AudioData = getaudiodata(Recording, 'single');
