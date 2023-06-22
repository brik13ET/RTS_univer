#ifndef STATISTIC_H
#define STATISTIC_H
#include <stdint.h>

float*	Stat_ticksToTime(uint64_t*, uint16_t, float);
float	Stat_minf(float*, uint16_t);
float	Stat_maxf(float*, uint16_t);
void	Stat_normf(float*, uint16_t);
void	Stat_histf(float*, uint16_t, uint8_t);
float	Stat_avgu64	(uint64_t*,	size_t);


#endif