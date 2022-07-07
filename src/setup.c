/**
 * @file setup.c
 * @author Fernando A. Miranda Bonomi (fmirandabonomi@herrera.unt.edu.ar)
 * @brief Configuración básica: 
 *      - Pin 13 del puerto C (led del bluepill) como salida 2MHz PushPull
 *      - Interrupción SysTick cada 1ms
 */
#include <main.h>
#include <timer_systick.h>
#include <stm32f1xx.h>

inline static void conectaRelojPuertoC(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
}

inline static void configuraPin13PuertoC_SalidaPushPull_2MHz_inicial_1(void)
{
    GPIOC->BSRR |= GPIO_BSRR_BS13;
    GPIOC->CRH = (GPIOC->CRH & ~(GPIO_CRH_MODE13|GPIO_CRH_CNF13))|(GPIO_CRH_MODE13_1);
}

void setup(void)
{
    conectaRelojPuertoC();
    configuraPin13PuertoC_SalidaPushPull_2MHz_inicial_1();
    TimerSysTick_init();
}
