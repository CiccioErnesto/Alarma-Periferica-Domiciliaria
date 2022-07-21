#ifndef ALARMA_H
#define ALARMA_H
#include <stdbool.h>
#include <evento.h>

typedef struct Alarma Alarma;
typedef enum EstadoAlarma EstadoAlarma;

enum EstadoAlarma {
	ALARMA_DESARMADA,
	ALARMA_ARMADA,
	ALARMA_DISPARADA,
	// -- Fin estados --
	NUM_ESTADO_ALARMA
};

struct Alarma{
	EstadoAlarma estado;
};

void Alarma_init(Alarma *self);
Evento Alarma_procesa(Alarma *self,Evento e);

#endif
