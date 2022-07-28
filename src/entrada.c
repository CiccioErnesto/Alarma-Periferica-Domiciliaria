#include "entrada.h"
#include <stdbool.h>
#include <string.h>
#include <teclado.h>

static bool comprobarClave(char* clave);

typedef struct Entrada{
    enum {
        ENTRADA_TECLA_LIBERADA,
        ENTRADA_TECLA_PRESIONADA
    } estado;
    char clave[4]; // memoria, no un estado en sí...
}Entrada;

static Entrada self;

void Entrada_init(void)
{
   teclado_init();
   self.estado = ENTRADA_TECLA_LIBERADA;
}
Evento Entrada_procesa(Evento  e)
{
	Evento esalida = EV_NULO;

    // si hay un evento externo lo transmite sin hacer más
    if(e != EV_NULO) return e;

    const char tecla = teclado_lee();

    switch (self.estado) // Estado...
    {
    case ENTRADA_TECLA_PRESIONADA:
        if (tecla == 0)
        {
            if (comprobarClave(self.clave))
            {
                esalida=EV_LLAVE;
            }
            self.estado = ENTRADA_TECLA_LIBERADA ;
        }
        
        break;
    case ENTRADA_TECLA_LIBERADA: 
        if(tecla != 0){   
            for (int i = 0; i < 3; i++)
            {
                self.clave[i]=self.clave[i+1];
            }
            self.clave[3]=tecla;
            self.estado = ENTRADA_TECLA_PRESIONADA;
        }
        break;
    default:
        self.estado = ENTRADA_TECLA_LIBERADA;
        break;
    }
	return esalida;
}


static bool comprobarClave(char* clave){
	char claveDef[]="1234";
    return strncmp(clave,claveDef,4) == 0;
}