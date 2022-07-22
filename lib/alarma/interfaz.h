#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <stdbool.h>
#include <pin_gpio.h>
#include <evento.h>

typedef struct Interfaz Interfaz;


struct Interfaz{
	bool sirena;
	bool indArmada;
	bool indDeteccion;
	bool indClave;
	struct{
		Pin *armada ;
		Pin *deteccion;
		Pin *sirena ;
	}pines;
	bool estadoPinActivo;
};

void Interfaz_init(Interfaz *self,Pin *armada,Pin *deteccion,Pin *sirena, bool estadoPinActivo);
Evento Interfaz_actualiza(Interfaz *self, Evento e);
void Interfaz_presenta(Interfaz *self);


#endif
