/**
 * @file systick_isr.c
 * @author Fernando A. Miranda Bonomi (fmirandabonomi@herrera.unt.edu.ar)
 * @brief Implementación simple de ISR de SysTick generando un contador de milisegundos.
 */
#include <timer_systick.h>

static volatile uint32_t ticks;

uint32_t TimerSysTick_getMilisegundos(void)
{
    return ticks;
}

void SysTick_Handler(void)
{
    ticks ++;
}