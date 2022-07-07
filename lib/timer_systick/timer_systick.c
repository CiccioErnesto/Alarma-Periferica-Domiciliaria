#include <timer_systick.h>
#include <stm32f1xx.h>

void TimerSysTick_init(void)
{
    /* El máximo valor de ciclosPorMilisegundo es 
       0xFFFFFFFF/1000 = 0x418937
       y tiene 23bits, así que siempre será posible
       escribir (ciclosPorMilisegundo-1) en el registro de carga
       de SysTick y SysTick_Config siempre funcionará */
    SystemCoreClockUpdate();
    const uint32_t ciclosPorMilisegundo = SystemCoreClock/1000;
    SysTick_Config(ciclosPorMilisegundo);
}

void TimerSysTick_esperaMilisegundos(uint32_t tiempo)
{
    if (tiempo == 0) tiempo = 1;
    uint32_t final = tiempo + TimerSysTick_getMilisegundos();
    while (TimerSysTick_getMilisegundos() != final);
}
