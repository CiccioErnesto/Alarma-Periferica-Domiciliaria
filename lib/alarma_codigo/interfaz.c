#include <stdio.h>
#include <interfaz.h>

void Interfaz_init(Interfaz *self)
{
    *self = (Interfaz){};
}

Evento Interfaz_actualiza(Interfaz *self, Evento e)
{
	Evento esalida = EV_NULO;
	switch(e){
	break;case EV_ALERTA:
		self->sirena = true;
		self->indDeteccion = true;  // Alerta implica detección
	break;case EV_ARMADA:
		self->indArmada = true;
		self->indClave = false;
		if (self->indDeteccion)
		    esalida = EV_DETECCION; // Recuerda que hay una detección activa.
	break;case EV_DESARMADA:
		self->indClave = false;
		self->sirena = false;
		self->indArmada = false;
	break;case EV_DETECCION:
		self->indDeteccion = true;
	break;case EV_FIN_DETECCION:
		self->indDeteccion = false;
	break;case EV_CLAVE_INCORRECTA:
		self->indClave = true;
	break;default:
		esalida = e;
	}
	return esalida;
}
void Interfaz_dibuja(Interfaz *self)
{
    enum {D,A,S,C,NR_IND};
    static const char *const indicadores[NR_IND][2] = {
        [D][true] ="DETECCION",
        [D][false]="#########",
        [A][true] ="ARMADA",
        [A][false]="######",
        [S][true] ="SIRENA",
        [S][false]="######",
        [C][false]="",
        [C][true]="Clave Incorrecta"
    };
	printf(CLRSCR"a LLAVE\nd DETECCION\nf FIN_DETECCION\nx SALIR\n\n");
	printf("%s %s %s\n\n",
	    indicadores[D][self->indDeteccion],
	    indicadores[A][self->indArmada],
	    indicadores[S][self->sirena]);
	printf("%s\n",indicadores[C][self->indClave]);
}
