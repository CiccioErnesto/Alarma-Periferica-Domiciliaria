
#include <main.h>
#include <stm32f1xx.h>
#include <timer_systick.h>
#include <pin_gpio.h>

// Ejemplo de implementacion en hardware sencillo, falta definir el antirrebote, que no funcionaba.

static Pin pinled ;
static Pin pinLlave;
static Pin pinzona ;

static void iniciaRelojGPIO(void){  
    //RCC->APB2ENR |= RCC_APB2ENR_IOPAEN ; //Puerto A
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN ;   //Puerto B
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN ;   //Puerto C
}

void setup (void){

    TimerSysTick_init();
    iniciaRelojGPIO();
    Pin_init(&pinled,   GPIOC , 13);
    Pin_init(&pinLlave, GPIOC , 7);
    Pin_init(&pinzona,  GPIOC , 4);
    
    Pin_modo(&pinled,   CPIN_SALIDA_2Mhz);
    Pin_modo(&pinled,   CPIN_ENTRADA_PULL);
    Pin_escribe(&pinLlave,1); //Pull-up
    Pin_modo(&pinled,   CPIN_ENTRADA_PULL);
    Pin_escribe(&pinzona, 1); //Pull-up
   
}

void loop (void){
    TimerSysTick_esperaMilisegundos(10);
   Pin_escribe(&pinled, Pin_lee(&pinLlave) | Pin_lee(&pinzona));
}