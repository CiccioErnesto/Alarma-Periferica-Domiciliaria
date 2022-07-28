#include "deteccion.h"
#include <pin_gpio.h>
#include <timer_systick.h>

typedef struct Deteccion 
{
    Pin zona;
    enum {
        ESTADO_NO_DETECTADO,
        ESTADO_DETECTADO
    } estado;
}Deteccion;

static Deteccion self ;

void Deteccion_init(void)
{
    Pin_init(&self.zona,GPIOB,4);
    Pin_escribe(&self.zona,1);
    Pin_modo(&self.zona,CPIN_ENTRADA_PULL);
    self.estado = ESTADO_NO_DETECTADO;
}
Evento Deteccion_procesa(Evento e)
{
    if (e != EV_NULO) return e;

    switch (self.estado)
    {
    case ESTADO_NO_DETECTADO:
        if (!Pin_lee(&self.zona))
        {
            self.estado = ESTADO_DETECTADO ;
            e = EV_DETECCION;
        }
        
        break;
    case ESTADO_DETECTADO: 
        if(Pin_lee(&self.zona)){
            self.estado = ESTADO_NO_DETECTADO;
            e = EV_FIN_DETECCION ;
        }
        break;
    default:
        self.estado = ESTADO_NO_DETECTADO;
        e = EV_FIN_DETECCION;
        break;
    }

    return e;
}
