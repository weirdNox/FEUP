#include "sa.h"

// Timer Part
void start_timer(timer_t& T)
{
  T.start_time = millis();
  refresh_timer(T);
}

byte refresh_timer(timer_t& T)
{
  if(millis() - T.start_time > T.p * 100)
    T.q = 1;
  else
    T.q = 0;
}
