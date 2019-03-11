function [Boundary, Codebook, Delta] = quantizationInfo(N, Min, Max, Type)
  %% NOTE(nox): If Type is passed in, Boundary includes Min and Max

  assert( Min  < Max);
  assert(-Min == Max);

  L = 2^N;
  Delta = 2*Max/L;

  Boundary(1) = Min;
  for(Idx = 1:L)
    Boundary(Idx+1) = Boundary(Idx) + Delta;
    Codebook(Idx)   = Boundary(Idx) + Delta/2;
  end

  if(~exist('Type', 'var'))
    Boundary = Boundary(2:end-1);
  end
end
