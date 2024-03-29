#ifndef EVENTO_H
#define EVENTO_H

typedef enum Evento Evento;


enum Evento {
	EV_NULO = 0,
	// Eventos del sector de entrada
	EV_DETECCION,           // Indica que el circuito de detección se activó
	EV_FIN_DETECCION,       // Indica que el circuito de detección se desactivó
	EV_LLAVE,               // Indica que se recibió un comando de armar/desarmar
	// Eventos de la alarma
	EV_ALERTA,              // Indica el inicio de una condición de alerta
	EV_ARMADA,              // Indica el armado de la alarma
	EV_DESARMADA,           // Indica el desarme de la alarma. Implica fin alerta.
	EV_FIN_ALERTA,			// Indica que finaliza una condición de alerta
	// Eventos de control
	EV_TIMEOUT,
	// -Fin de eventos-
	NUM_EVENTOS
};

#endif
