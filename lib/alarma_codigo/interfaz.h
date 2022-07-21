#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <stdbool.h>

#include <evento.h>

#define ESC "\x1B"
#define CLRSCR ESC"c"

typedef struct Interfaz Interfaz;


struct Interfaz{
	bool sirena;
	bool indArmada;
	bool indDeteccion;
	bool indClave;
};

void Interfaz_init(Interfaz *self);
Evento Interfaz_actualiza(Interfaz *self, Evento e);
void Interfaz_dibuja(Interfaz *self);

#endif
