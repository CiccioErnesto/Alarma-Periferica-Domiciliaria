#include "teclado.h"

char SalidaTeclado(int fila, int columna){
	char matriz[4][3]={
						{'1','2','3'},
						{'4','5','6'},
						{'7','8','9'},
						{'*','0','#'}
	};
	return (matriz[fila][columna]);
}

bool CompararClave(){
	char claveDef[5]="1234";
	int i,fila,col;
	bool salida=true;
	for(i=0;i<4;i++){
		printf("it: %d Ingresar fila: ",i);
		scanf("%d",&fila);//fila=getchar()
		printf("Ingresar columna: ");
		scanf("%d",&col);//col=getchar()
		if(claveDef[i]!=SalidaTeclado(fila,col)){
			salida=false;
		}
	}
	printf("Salida: %d",salida);
	return salida;
}