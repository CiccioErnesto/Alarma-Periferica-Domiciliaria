#ifndef PIN_GPIO_H
#define PIN_GPIO_H

#include <stm32f1xx.h>

typedef struct Pin {
        GPIO_TypeDef * puerto ;
        int nrPin ;
} Pin ;

typedef enum ConfigPin {
    CPIN_ANALOGICO      = 0b0000,
    CPIN_ENTRADA        = 0b0100,
    CPIN_ENTRADA_PULL   = 0b1000,
    CPIN_SALIDA_2Mhz    = 0b0010,
    CPIN_SALIDA_10Mhz   = 0b0001,
    CPIN_SALIDA_50Mhz   = 0b0011,

}ConfigPin ;

void Pin_init(Pin * self, GPIO_TypeDef * puerto, int nrPin);
void Pin_modo(Pin * self, ConfigPin cfg);
int  Pin_lee(Pin * self);
int  Pin_leesalida(Pin * self);
void Pin_escribe(Pin * self, int valor);


#endif