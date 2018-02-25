#ifndef PROJ_TYPES_H
#define PROJ_TYPES_H

#include "Arduino.h"

// Timer Stuff
typedef struct {
  unsigned long start_time;
  unsigned long p;
  byte q;
} timer_t;


#endif // PROJ_TYPES_H 
