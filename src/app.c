#include <alarma.h>
#include <interfaz.h>
#include <evento.h>
#include <teclado.h>
#include <app.h>
#include <stm32f1xx.h>
#include <timer_systick.h>
#include <pin_gpio.h>


char clave[4]={"0000"};

typedef struct App {
    Alarma alarma;
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
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN ; //Puerto A
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN ;   //Puerto B
    //RCC->APB2ENR |= RCC_APB2ENR_IOPCEN ;   //Puerto C
}

void App_init(void){
    enum{VALOR_PIN_LED_ENCENDIDO = 0};
    TimerSysTick_init();
    iniciaRelojGPIO();
   
    Alarma_init(&self.alarma);
	
    // Inicio teclado
    // debo iniciar el puerto dentro de teclado.c o esta bien en app. ?
    
   teclado_init();
   teclado_lee();
   
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
	char tecla,auxTecla;
	Evento esalida = EV_NULO;
    if ((tecla=teclado_lee())!=0)
    {
        e=EV_TECLA_PRESIONADA;
    }
    
    switch (e)
    {
    case EV_TECLA_LIBERADA:
        if (comprobarClave(clave))
        {
            esalida=EV_LLAVE;
        }
        break;
    case EV_TECLA_PRESIONADA:
        do {
            auxTecla=tecla;
        } while((tecla=teclado_lee())!=0);

        for (int i = 0; i < 3; i++)
        {
            clave[i]=clave[i+1];
        }
        clave[3]=auxTecla;

        esalida=EV_TECLA_LIBERADA;

        break;
    default:
        esalida=e;
        break;
    }
	return esalida;
}