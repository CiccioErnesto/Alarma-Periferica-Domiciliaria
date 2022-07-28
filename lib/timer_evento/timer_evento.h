#ifndef TIMER_EVENTO_H
#define TIMER_EVENTO_H
#include <evento.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct TimerEvento{
    enum{TIMER_EVENTO_ESPERA,TIMER_EVENTO_ACTIVO} estado;
    uint32_t inicio;
    uint32_t duracion;
}TimerEvento;

void TimerEvento_init(TimerEvento *self);
Evento TimerEvento_procesa(TimerEvento *self,Evento e);
void TimerEvento_inicia(TimerEvento *self,uint32_t duracion_ms);
void TimerEvento_cancela(TimerEvento *self);

#endif
