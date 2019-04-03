function NormCoefs = longDivisionSynthesis(TransfDen)
  Len = length(TransfDen);
  DEven = TransfDen;
  DOdd = TransfDen;

  if(mod(Len, 2) == 1)
    DEven(2:2:end) = 0;
    DOdd(1:2:end) = 0;
    DOdd = DOdd(2:end);

    Num = DEven;
    Den = DOdd;
  else
    DOdd(2:2:end) = 0;
    DEven(1:2:end) = 0;
    DEven = DEven(2:end);

    Num = DOdd;
    Den = DEven;
  end

  NormCoefs = zeros(1, Len-1);
  for(I = 1:(Len-1))
    [Quotient, Remainder] = deconv(Num, Den);
    NormCoefs(Len-I) = Quotient(1);
    Num = Den;
    Den = Remainder(3:end);
  end
end
