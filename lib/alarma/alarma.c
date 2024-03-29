#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <alarma.h>
#include <teclado.h>

    

void Alarma_init(Alarma *self,TimerEvento *timer)
{
	self->estado = ALARMA_DESARMADA;
	self->timer  = timer;
}
Evento Alarma_procesa(Alarma *self,Evento e)
{
	Evento esalida = EV_NULO;
	switch(self->estado){
	case ALARMA_ARMADA:
		switch(e){
		case EV_LLAVE:
			self->estado = ALARMA_DESARMADA;
			esalida = EV_DESARMADA;
		break;case EV_DETECCION:
			self->estado = ALARMA_DISPARADA;
			esalida = EV_ALERTA;
		break;default:
			esalida = e;
		}
	break;case ALARMA_DESARMADA:
		switch(e){
		case EV_LLAVE:
			self->estado = ALARMA_ARMADA;
			esalida = EV_ARMADA;
		break;default:
			esalida = e;
		}
	break;case ALARMA_DISPARADA:
		switch(e){
		case EV_LLAVE:
			self->estado = ALARMA_DESARMADA;
			esalida = EV_DESARMADA;
		break;case EV_FIN_DETECCION:
			TimerEvento_inicia(self->timer,40000UL);
			esalida = EV_FIN_DETECCION;
		break;case EV_DETECCION:
			TimerEvento_cancela(self->timer);
			esalida = EV_DETECCION;
		break;case EV_TIMEOUT:
			self->estado = ALARMA_ARMADA;
			esalida = EV_FIN_ALERTA;
		break;default:
			esalida = e;
		}
	break;default:
		self->estado = ALARMA_DESARMADA;
		esalida = EV_DESARMADA;
	}
	return esalida;
}

