function XDft =  fftTest(Type, NumPeriods, Length)
  SamplingFreq = 48828.125;
  SamplingTime = 1/SamplingFreq;

  if(nargin < 3)
    Length = 64;
  end
  TimeN = [0:Length-1];

  switch Type
    case 'sin'
      X = sin(2*pi*TimeN*NumPeriods/Length);
    case 'saw'
      X = sawtooth(2*pi*TimeN*NumPeriods/Length);
    case 'triangle'
      X = sawtooth(2*pi*TimeN*NumPeriods/Length, 0.5);
    case 'square'
      X = square(2*pi*TimeN*NumPeriods/Length);
    otherwise
      error("Not a valid type given");
  end

  PeriodTime = SamplingTime*Length / NumPeriods;
  Frequency = 1/PeriodTime

  XDft = fft(X);
  XDftSquared = XDft.*conj(XDft);

  figure(1); clf;
  stem(TimeN/SamplingFreq*1000, X);
  axis([0 Length/SamplingFreq*1000 -1.2 1.2]);
  title('Sinal temporal');
  xlabel('Tempo (ms)');
  ylabel('Amplitude');

  figure(2); clf;
  stem([0:Length/2-1], 10*log10(1+XDftSquared(1:Length/2)), 'filled');
  xlim([0 Length/2-1]);
  title('Análise Espetral');
  xlabel('Risca');
  ylabel('Densidade Espetral Potência (dB)');
end
