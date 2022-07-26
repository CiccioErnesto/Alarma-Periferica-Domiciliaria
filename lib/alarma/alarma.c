#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <alarma.h>
#include <teclado.h>

    

void Alarma_init(Alarma *self)
{
	self->estado = ALARMA_DESARMADA;
}
Evento Alarma_procesa(Alarma *self,Evento e)
{
	Evento esalida = EV_NULO;
	switch(self->estado){
	break;case ALARMA_ARMADA:
		switch(e){
		break;case EV_LLAVE:
			self->estado = ALARMA_DESARMADA;
			esalida = EV_DESARMADA;
		break;case EV_DETECCION:
			self->estado = ALARMA_DISPARADA;
			esalida = EV_ALERTA;
		break;default:
			esalida = e;
		break;
		}
	break;case ALARMA_DESARMADA:
		switch(e){
		break;case EV_LLAVE:
			self->estado = ALARMA_ARMADA;
			esalida = EV_ARMADA;
		break;default:
			esalida = e;
		break;
		}
	break;case ALARMA_DISPARADA:
		switch(e){
		break;case EV_LLAVE:
			self->estado = ALARMA_DESARMADA;
			esalida = EV_DESARMADA;
		break;default:
			esalida = e;
		}
	break;default:
		self->estado = ALARMA_DESARMADA;
		esalida = EV_DESARMADA;
	break;
	}
	return esalida;
}
