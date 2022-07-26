#include <teclado.h>
#include <stm32f1xx.h>
#include <timer_systick.h>

 typedef struct pines{
        Pin filas [4];
        Pin cols  [4];
    }pines;

static pines self ;

void teclado_init(void){


	for(int k=0; k<4 ; ++k){
        Pin_init(&self.filas[k],GPIOA,0+k);
        Pin_escribe(&self.filas[k],1);
        Pin_modo(&self.filas[k],CPIN_SALIDA_OD_2MHz);

        Pin_init(&self.cols[k],GPIOA,4+k);
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

        TimerSysTick_esperaMilisegundos(10);
        while (!Pin_lee(&self.cols[0]))  {valor = teclado [i][0];}  
        while (!Pin_lee(&self.cols[1]))  {valor = teclado [i][1];}  
        while (!Pin_lee(&self.cols[2]))  {valor = teclado [i][2];}
        while (!Pin_lee(&self.cols[3]))  {valor = teclado [i][3];}  

    }
    return valor ;
}


bool comprobarClave(char* clave){
	char claveDef[4]="1234";
    if (strcmp(clave,claveDef)==0)
    {
        return false;
    }
    return true;
}