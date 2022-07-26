#include <alarma.h>
#include <interfaz.h>
#include <evento.h>
#include <app.h>
#include <stm32f1xx.h>
#include <timer_systick.h>
#include <pin_gpio.h>


typedef struct App {
    Alarma alarma;
	Interfaz interfaz;
	Evento e ;
    struct {
        Pin filas [4];
        Pin cols  [4];
        Pin armada ;
		Pin deteccion;
		Pin sirena ;
    }pines;
}App;

static App self ={.e = EV_NULO};


static void iniciaRelojGPIO(void){  
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN ; //Puerto A
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN ;   //Puerto B
    //RCC->APB2ENR |= RCC_APB2ENR_IOPCEN ;   //Puerto C
}

void App_init (void){
    enum{VALOR_PIN_LED_ENCENDIDO = 0};
    TimerSysTick_init();
    iniciaRelojGPIO();
   
    Alarma_init(&self.alarma);
	
   
   for(int k=0; k<4 ; ++k){
        Pin_init(&self.pines.filas[k],GPIOA,0+k);
        Pin_escribe(&self.pines.filas[k],1);
        Pin_modo(&self.pines.filas[k],CPIN_SALIDA_OD_2MHz);

        Pin_init(&self.pines.cols[k],GPIOA,4+k);
        Pin_escribe(&self.pines.cols[k],1);
        Pin_modo(&self.pines.cols[k],CPIN_ENTRADA_PULL);
   }

   //init pines armada, det. y sirena.

    //Pin_init(&self.pines.armada,GPIOx,nropin);
    Pin_escribe(&self.pines.armada,!VALOR_PIN_LED_ENCENDIDO); 
    Pin_modo(&self.pines.armada,CPIN_SALIDA_2MHz);
    
    Interfaz_init(&self.interfaz,&self.pines.armada,&self.pines.deteccion,&self.pines.sirena,VALOR_PIN_LED_ENCENDIDO);

    self.e = EV_NULO;
}

static Evento entrada(Evento  e);

void App_loop (void){
    Interfaz_presenta(&self.interfaz);
	self.e = entrada(self.e);
	self.e = Alarma_procesa(&self.alarma, self.e);
	self.e = Interfaz_actualiza(&self.interfaz,self.e);
    TimerSysTick_esperaMilisegundos(10);
}



static Evento entrada(Evento  e)
{
	
	Evento esalida = EV_NULO;
	if(e)
		esalida = e;
	else{
		// proceso de teclado...
	}
	return esalida;
}