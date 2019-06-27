%% Example usage:
%%   bode(sym2tf(subs(Wn^2 / (s^2 + s*2*Zeta*Wn + Wn^2), {Wn, Zeta}, {2*pi*10e3, 1/sqrt(2)})))

function [ tfobj ] = sym2tf( symobj, Ts)
  if isnumeric(symobj)
    tfobj=symobj;
    return;
  end

  [n,d]=numden(symobj);
  num=sym2poly(n);
  den=sym2poly(d);

  if nargin==1
    tfobj=tf(num,den);
  else
    tfobj=tf(num,den,Ts);
  end
end
