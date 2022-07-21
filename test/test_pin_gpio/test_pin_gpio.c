#include <unity.h>
#include <timer_systick.h>
#include <pin_gpio.h>
#include <stm32f1xx.h>

static GPIO_TypeDef miPuerto;

static Pin miPinL, miPinH ;

enum {
    PIN_L            = 7, 
    MASCARA_L        = 1<<7,
    IDR_PRUEBA_L_0   = ~MASCARA_L,
    IDR_PRUEBA_L_1   = MASCARA_L,
    ODR_PRUEBA_L_0   = IDR_PRUEBA_L_0,
    ODR_PRUEBA_L_1   = IDR_PRUEBA_L_1,
    CRL_RESET        = 0x44444444UL,
    CRL_ENTRADA_PULL = 0x84444444UL,
    CRL_SALIDA_2Mhz  = 0x24444444UL,
    PIN_H            = 8,
    MASCARA_H        = 1<<8,
    IDR_PRUEBA_H_0   = ~MASCARA_H,
    IDR_PRUEBA_H_1   = MASCARA_H,
    ODR_PRUEBA_H_0   = IDR_PRUEBA_H_0,
    ODR_PRUEBA_H_1   = IDR_PRUEBA_H_1,
    CRH_RESET        = 0x44444444UL,
    CRH_ENTRADA_PULL = 0x44444448UL,
    CRH_SALIDA_2Mhz  = 0x44444442UL,
};

void setUp(void){
    miPuerto = (GPIO_TypeDef){.CRL= CRL_RESET, .CRH = CRH_RESET};
    Pin_init(&miPinL,&miPuerto,PIN_L);
    Pin_init(&miPinH,&miPuerto,PIN_H);
}
void tearDown(void){}

static void debe_configurar_pin_entrada_pull(void){

    TEST_ASSERT_EQUAL_HEX32(CRL_RESET,miPuerto.CRL);
    Pin_modo(&miPinL,CPIN_ENTRADA_PULL);
    TEST_ASSERT_EQUAL_HEX32(CRL_ENTRADA_PULL,miPuerto.CRL);

    TEST_ASSERT_EQUAL_HEX32(CRH_RESET,miPuerto.CRH);
    Pin_modo(&miPinH,CPIN_ENTRADA_PULL);
    TEST_ASSERT_EQUAL_HEX32(CRH_ENTRADA_PULL,miPuerto.CRH);
}

static void debe_configurar_pin_salida(void){

    TEST_ASSERT_EQUAL_HEX32(CRL_RESET,miPuerto.CRL);
    Pin_modo(&miPinL,CPIN_SALIDA_2Mhz);
    TEST_ASSERT_EQUAL_HEX32(CRL_SALIDA_2Mhz,miPuerto.CRL);

    TEST_ASSERT_EQUAL_HEX32(CRH_RESET,miPuerto.CRH);
    Pin_modo(&miPinH,CPIN_SALIDA_2Mhz);
    TEST_ASSERT_EQUAL_HEX32(CRH_SALIDA_2Mhz,miPuerto.CRH);
}

static void debe_leer_entrada(void)
{
miPuerto.IDR =  IDR_PRUEBA_L_0;
TEST_ASSERT_EQUAL(0,Pin_lee(&miPinL));
miPuerto.IDR = IDR_PRUEBA_L_1 ;
TEST_ASSERT_EQUAL(1,Pin_lee(&miPinL));

miPuerto.IDR =  IDR_PRUEBA_H_0;
TEST_ASSERT_EQUAL(0,Pin_lee(&miPinH));
miPuerto.IDR = IDR_PRUEBA_H_1 ;
TEST_ASSERT_EQUAL(1,Pin_lee(&miPinH));

}

static void debe_escribir_salida_L0 (void){

    Pin_escribe(&miPinL,0);
    TEST_ASSERT_EQUAL_HEX32(MASCARA_L,miPuerto.BRR | (miPuerto.BSRR >> 16));

}

static void debe_escribir_salida_H0 (void){

    Pin_escribe(&miPinH,0);
    TEST_ASSERT_EQUAL_HEX32(MASCARA_H,miPuerto.BRR | (miPuerto.BSRR >> 16));

}

static void debe_escribir_salida_L1 (void){

    Pin_escribe(&miPinL,1);
    TEST_ASSERT_EQUAL_HEX32(MASCARA_L,miPuerto.BSRR);

}

static void debe_escribir_salida_H1 (void){

    Pin_escribe(&miPinH,1);
    TEST_ASSERT_EQUAL_HEX32(MASCARA_H,miPuerto.BSRR);

}

static void debe_leer_salida(void)
{
miPuerto.ODR = ODR_PRUEBA_L_0;
TEST_ASSERT_EQUAL(0,Pin_leesalida(&miPinL));
miPuerto.ODR = ODR_PRUEBA_L_1 ;
TEST_ASSERT_EQUAL(1,Pin_leesalida(&miPinL));

miPuerto.ODR = ODR_PRUEBA_H_0;
TEST_ASSERT_EQUAL(0,Pin_leesalida(&miPinH));
miPuerto.ODR = ODR_PRUEBA_H_1 ;
TEST_ASSERT_EQUAL(1,Pin_leesalida(&miPinH));

}


int main(void)
{
    TimerSysTick_init();
    TimerSysTick_esperaMilisegundos(500);
    UNITY_BEGIN();
    RUN_TEST(debe_configurar_pin_entrada_pull);
    RUN_TEST(debe_configurar_pin_salida);
    RUN_TEST(debe_leer_entrada);
    RUN_TEST(debe_escribir_salida_L0);
    RUN_TEST(debe_escribir_salida_H0);
    RUN_TEST(debe_escribir_salida_L1);
    RUN_TEST(debe_escribir_salida_H1);
    RUN_TEST(debe_leer_salida);

    UNITY_END();   
}



