#include  <pin_gpio.h>

void Pin_init(Pin * self, GPIO_TypeDef * puerto, int nrPin){
    self->puerto = puerto;
    self->nrPin  = nrPin;
}

void Pin_modo(Pin * self, ConfigPin cfg){
    
    if(self->nrPin < 8 ){
        int pos = 4*self->nrPin;
        uint32_t mascaraCfg = 0xF << pos ;
        self->puerto->CRL = (self->puerto->CRL & ~mascaraCfg) | (cfg << pos);
    }else{
        int pos = 4*(self->nrPin-8);
        uint32_t mascaraCfg = 0xF << pos ;
        self->puerto->CRH = (self->puerto->CRH & ~mascaraCfg) | (cfg << pos);
    }
}

int  Pin_lee(Pin * self){
    uint32_t  mascaraPin = 1 << self->nrPin ;
    return (self->puerto->IDR & mascaraPin) != 0  ;
}

void Pin_escribe(Pin * self, int valor){

    if(valor == 0){
         self->puerto->BRR = 1 << self->nrPin;
    }    
    else {
        self->puerto->BSRR = 1 << self->nrPin;
    }

}

int  Pin_leesalida(Pin * self){
    uint32_t  mascaraPin = 1 << self->nrPin ;
    return (self->puerto->ODR & mascaraPin) != 0  ;
}