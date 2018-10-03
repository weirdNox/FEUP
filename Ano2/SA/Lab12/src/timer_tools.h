/*
 * timer_tools.h
 *
 */

#ifndef TIMER_TOOLS_H_
#define TIMER_TOOLS_H_

#include <sys/time.h>

typedef struct {
	struct timeval start_value;
	int delta;
} ms_timer;

void start_timer(ms_timer* timer, int delta_time_ms);

int get_timer(ms_timer* timer);

#endif /* TIMER_TOOLS_H_ */
