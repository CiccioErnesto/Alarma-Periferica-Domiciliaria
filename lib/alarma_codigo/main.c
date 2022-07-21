/**
 * # Ejemplo de alarma sencillo.
 * 
 * Consta de tres partes, una entrada, una salida y la lógica de alarma. Las 
 * partes están conectadas por eventos consumidos y generados por las mismas.
 * Cada parte tiene una entrada de evento y una salida de evento. Si el evento
 * de entrada es consumido podrá dar origen a un evento de salida adecuado o
 * bien al evento nulo. Si el evento no es consumido debe propagarse a la 
 * salida.
 * 
 * Cada evento será propagado en el lazo principal hasta ser consumido. Si un
 * evento nunca es consumido entonces quedará un lazo infinito sin trabajo útil.
 * 
 * Circuito de los eventos:
 * 
 * +--Entrada --> Alarma --> Interfaz--v
 * ^-----------------------------------+
 * 
 * Entrada, al principio del lazo, recibe inicialmente el evento nulo.
 * 
 * ## Parte de entrada
 * 
 * Implementada por la función `Evento entrada(Evento e)`. Si el evento aceptado
 * `e` es un evento válido (no es el evento nulo) entonces propagará el evento a
 * su salida sin hacer más. Caso contrario tomará un caracter de la entrada
 * estándar (el usuario debe escribir un caracter y presionar enter) y generará
 * un evento de acuerdo a la asignación
 * a -> EV_LLAVE
 * d -> EV_DETECCION
 * f -> EV_FIN_DETECCION
 * x -> EV_SALIR
 * 
 * ## Parte salida
 * 
 * Implementada por la clase `Interfaz`. Una instancia de dicha clase acepta los
 * siguientes métodos:
 * - init(): constructor (debe ser el primer método llamado para un objeto)
 * - dibuja(): dibuja en la consola la interfaz según el estado actual de las 
 *              salidas.
 * - Evento actualiza(Evento e): toma como argumento un evento. Consume los 
 *              eventos `EV_ARMADA`, `EV_DESARMADA`, `EV_DETECCION` e
 *              `EV_FIN_DETECCION`.
 *              Actualiza las salidas según los eventos consumidos.
 *              Propaga todo evento no consumido.
 * NOTA 1: Cuando recibe el evento `EV_ARMADA` en caso de estar activada la
 * indicacion de deteccion genera un nuevo evento `EV_DETECCION` puesto que el
 * sistema de entrada no generará eventos detección duplicados.
 * 
 * NOTA 2: Los métodos tienen implícito un prefijo con el nombre de la clase
 * separado del nombre por un caracter subraya '_' y un primer argumento puntero
 * al tipo de la clase. Así el método init será implementado por la función
 * 
 *  `void Interfaz_init(Interfaz *self);`
 * 
 * ## Lógica de la alarma
 * 
 * Implementada mediante una máquina de estado en la clase Alarma. La
 * implementación de máquina de estado es con switch anidados (admite mejora).
 * Los estados están implementados mediante la enumeración `EstadoAlarma`. La 
 * clase admite los siguientes métodos:
 * 
 * - init(): Constructor, debe ser el primer método en invocarse luego de crear
 *          un objeto.
 * - Evento procesa(Evento e): Procesa un evento, modificando posiblemente el
 *          estado de la alarma y emitiendo un evento para controlar la salida.
 * 
 */


#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include <teclado.h>
#include <evento.h>
#include <alarma.h>
#include <interfaz.h>

static Evento entrada(Evento  e)
{
	
	Evento esalida = EV_NULO;
	if(e)
		esalida = e;
	else{
	    printf(">");
		switch(getchar()){
		break;case 'a':
			esalida = EV_LLAVE;
		break;case 'd':
			esalida = EV_DETECCION;
		break;case 'f':
			esalida = EV_FIN_DETECCION;
		break;case 'x':
			esalida = EV_SALIR;
		break;case '\n':
		break;case '\r':
		break;default:
			printf("Comando no reconocido!\n");
			sleep(1);
		break;
		}
	}
	return esalida;
}

int main(void)
{
	Alarma alarma;
	Interfaz interfaz;
	Evento e = EV_NULO;

	Alarma_init(&alarma);
	Interfaz_init(&interfaz);

	while(e != EV_SALIR)
	{
		Interfaz_dibuja(&interfaz);
		e = entrada(e);
		e = Alarma_procesa(&alarma, e);
		e = Interfaz_actualiza(&interfaz,e);
		usleep(1000);
	}
	printf(CLRSCR);
	return 0;
}
