#include <teclado.h>
#include <stm32f1xx.h>
#include <timer_systick.h>

 typedef struct pines{
        Pin filas [4];
        Pin cols  [4];
    }pines;

static pines self ;

void teclado_init(void){

    Pin_init(&self.filas[0],GPIOA,7);
    Pin_init(&self.filas[1],GPIOA,6);
    Pin_init(&self.filas[2],GPIOA,5);
    Pin_init(&self.filas[3],GPIOA,4);
    Pin_init(&self.cols[0],GPIOA,3);
    Pin_init(&self.cols[1],GPIOA,2);
    Pin_init(&self.cols[2],GPIOA,1);
    Pin_init(&self.cols[3],GPIOA,0);

	for(int k=0; k<4 ; ++k){
        Pin_escribe(&self.filas[k],1);
        Pin_modo(&self.filas[k],CPIN_SALIDA_OD_2MHz);
        Pin_escribe(&self.cols[k],1);
        Pin_modo(&self.cols[k],CPIN_ENTRADA_PULL);
   }

}	

char teclado_lee(void){
	char teclado[4][4]={
						{'1','2','3','A'},
						{'4','5','6','B'},
						{'7','8','9','C'},
						{'*','0','#','D'}
	};


	int i = 0 ;
	char valor = 0 ;

    for (i=0 ; i < 4 ; i++ ){
       
        Pin_escribe(&self.filas[i],0);

        TimerSysTick_esperaMilisegundos(1);
        // comprobar si la columna es 0 (tecla presionada) PERO NO ESPERAR QUE SE LIBERE
       for ( int k = 0; k < 4; k++)
       {
        if(!Pin_lee(&self.cols[k])) {valor = teclado [i][k];}
       } 

        // Desactivar la fila (poner en 1

        Pin_escribe(&self.filas[i],1);

    }
    return valor ;
}
