#include <stdio.h>
#include <interfaz.h>


void Interfaz_init(Interfaz *self,Pin *armada,Pin *deteccion,Pin *sirena, bool estadoPinActivo)
{
    *self = (Interfaz){
		.pines = {
			.armada 	= armada,
			.deteccion 	= deteccion,
			.sirena		= sirena
		},
		.estadoPinActivo = estadoPinActivo
	};
}

Evento Interfaz_actualiza(Interfaz *self, Evento e) // ESTA FUNCION SE COMPORTA COMO UN LACH, pero podria decirse que se encuentra un maquina de estado en el.
{
	Evento esalida = EV_NULO;
	switch(e){
	case EV_ALERTA:
		self->sirena = true;
		self->indDeteccion = true;  // Alerta implica detección
	break;case EV_FIN_ALERTA:
		self->sirena = false;
	break;case EV_ARMADA:			
		self->indArmada = true;
		if (self->indDeteccion)
		    esalida = EV_DETECCION; // Recuerda que hay una detección activa.
	break;case EV_DESARMADA:
		self->sirena = false;
		self->indArmada = false;
	break;case EV_DETECCION:
		self->indDeteccion = true;
	break;case EV_FIN_DETECCION:
		self->indDeteccion = false;
	break;default:
		esalida = e;
	}
	return esalida;
}

static void Interfaz_ledOn(Interfaz *self, Pin *led)
{
	Pin_escribe(led, self->estadoPinActivo);
}
static void Interfaz_ledOff(Interfaz *self, Pin *led)
{
	Pin_escribe(led, !self->estadoPinActivo);
}


void Interfaz_presenta(Interfaz *self)
{
    if (self->indDeteccion) 
		Interfaz_ledOn(self,self->pines.deteccion);
	else 
		Interfaz_ledOff(self,self->pines.deteccion);

	if (self->indArmada) 
		Interfaz_ledOn(self,self->pines.armada);
	else 
		Interfaz_ledOff(self,self->pines.armada);

	if (self->sirena) 
		Interfaz_ledOn(self,self->pines.sirena);
	else 
		Interfaz_ledOff(self,self->pines.sirena);		
}
