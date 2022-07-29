/*
Autor :  Ciccio, Ernesto José
Carrera: Ingenieria Electrónica
Materia: Electrónica IV 
*/

#include <alarma.h>
#include <interfaz.h>
#include <evento.h>
#include <app.h>
#include <stm32f1xx.h>
#include <timer_systick.h>
#include <pin_gpio.h>
#include <timer_evento.h>
#include "entrada.h"
#include "deteccion.h"

typedef struct App {
    Alarma alarma;
    TimerEvento timer;
	Interfaz interfaz;
	Evento e ;
    struct {
        Pin armada ;
		Pin deteccion;
		Pin sirena ;
    }pines;
}App;


static App self ={.e = EV_NULO};


static void iniciaRelojGPIO(void){  
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN ;   //Puerto A
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN ;   //Puerto B
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN ;   //Puerto C
}

void App_init(void){
    enum{VALOR_PIN_LED_ENCENDIDO = 0};
    TimerSysTick_init();
    iniciaRelojGPIO();
   
    TimerEvento_init(&self.timer);
    Alarma_init(&self.alarma,&self.timer);
	
    Entrada_init();
    Deteccion_init();    
    
    //init pines armada, det. y sirena.

    // Pin armada ;
    
    Pin_init(&self.pines.armada,GPIOC,13);
    Pin_escribe(&self.pines.armada,!VALOR_PIN_LED_ENCENDIDO); 
    Pin_modo(&self.pines.armada,CPIN_SALIDA_OD_2MHz);

    // Pin deteccion;

    Pin_init(&self.pines.deteccion,GPIOB,8);
    Pin_escribe(&self.pines.deteccion,!VALOR_PIN_LED_ENCENDIDO); 
    Pin_modo(&self.pines.deteccion,CPIN_SALIDA_OD_2MHz);

    // Pin sirena ;

    Pin_init(&self.pines.sirena,GPIOB,6);
    Pin_escribe(&self.pines.sirena,!VALOR_PIN_LED_ENCENDIDO); 
    Pin_modo(&self.pines.sirena,CPIN_SALIDA_OD_2MHz);
    
    Interfaz_init(&self.interfaz,&self.pines.armada,&self.pines.deteccion,&self.pines.sirena,VALOR_PIN_LED_ENCENDIDO);

    self.e = EV_NULO;
}

void App_loop (void){
    Interfaz_presenta(&self.interfaz); // salidas al exterior .
    self.e = Deteccion_procesa(self.e);
    self.e = TimerEvento_procesa(&self.timer,self.e);
	self.e = Entrada_procesa(self.e);
	self.e = Alarma_procesa(&self.alarma, self.e);
	self.e = Interfaz_actualiza(&self.interfaz,self.e); // Esta funcion actua como Latch, pero puede modelase considerarse como maquina de estado. 
}
