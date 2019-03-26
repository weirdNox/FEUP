C = 0.0;
D = 0.8;
ImpRespSampleCount = 30;
FreqRespSampleCount = 512;

while(C <= 2.0)
  Num = [1 0 C];
  Den = [1 0 D];

  figure(1); clf;
  ImpResp = impz(Num, Den, ImpRespSampleCount);
  stem([0:ImpRespSampleCount-1], ImpResp);

  figure(2); clf;
  zplane(Num, Den);

  figure(3);
  [FreqResp FreqW] = freqz(Num, Den, FreqRespSampleCount, 'whole');
  plot(FreqW/pi, abs(FreqResp));
  axis([0 2 0 5]);

  figure(4);
  plot(FreqW/pi, angle(FreqResp));

  C = C + 0.05;
  pause;
end
