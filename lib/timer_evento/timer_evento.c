#include <timer_evento.h>
#include <timer_systick.h>

void TimerEvento_init(TimerEvento *self)
{
    (*self) = (TimerEvento){.estado = TIMER_EVENTO_ESPERA};
}
Evento TimerEvento_procesa(TimerEvento *self,Evento e)
{
    if(e != EV_NULO) return e;

    switch (self->estado)
    {
    case TIMER_EVENTO_ESPERA:
        break;
    case TIMER_EVENTO_ACTIVO:{
        const uint32_t tiempoTranscurrido = TimerSysTick_getMilisegundos() - self->inicio;
        if ( tiempoTranscurrido >= self->duracion)
        {
            self->estado = TIMER_EVENTO_ESPERA ;
            e = EV_TIMEOUT;
        }
    break;    
    }
    default:
    break;
    }
    return e ;
}
void TimerEvento_inicia(TimerEvento *self,uint32_t duracion_ms)
{
    self->estado = TIMER_EVENTO_ACTIVO;
    self->inicio = TimerSysTick_getMilisegundos();
    self->duracion = duracion_ms;
}
void TimerEvento_cancela(TimerEvento *self)
{
    self->estado = TIMER_EVENTO_ESPERA ;
}
