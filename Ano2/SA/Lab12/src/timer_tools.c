/*
 * timer_tools.c
 *
 */

#include "timer_tools.h"

ms_timer timer0;
unsigned long cur_time=0;


void start_timer(ms_timer* timer, int ms)
{
  gettimeofday(&(timer->start_value), NULL);
  timer->delta = ms;
}

int get_timer(ms_timer* timer)
{
  double dt;
  struct timeval act;
  gettimeofday(&act, NULL);
  dt = (act.tv_sec * 1000 + act.tv_usec / 1000) - (timer->start_value.tv_sec * 1000 + timer->start_value.tv_usec / 1000.0);
  if (dt > timer->delta)
	  return 1;
  else
	  return 0;
}


int get_timer_time(ms_timer* timer)
{
  struct timeval act;
  gettimeofday(&act, NULL);
  return (act.tv_sec * 1000 + act.tv_usec / 1000) - (timer->start_value.tv_sec * 1000 + timer->start_value.tv_usec / 1000.0);
}
