#ifndef sa_h
#define sa_h

#include "Arduino.h"

void init_hardware(void);

// Timer Stuff
typedef struct {
  unsigned long start_time;
  unsigned long p;
  byte q;
} timer_t;


#endif
