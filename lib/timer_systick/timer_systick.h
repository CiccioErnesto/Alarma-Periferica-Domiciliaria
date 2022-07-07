#ifndef TIMER_SYSTICK_H
#define TIMER_SYSTICK_H
#include <stdint.h>

void TimerSysTick_init(void);
uint32_t TimerSysTick_getMilisegundos(void);
void TimerSysTick_esperaMilisegundos(uint32_t tiempo);

#endif