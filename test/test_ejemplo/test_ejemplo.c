#include <ejemplo.h>
#include <unity.h>
#include <timer_systick.h>
#include <ejemplo.h>

void setUp(void){}
void tearDown(void){}

static void suma_dos_numeros_34(void)
{    
    TEST_ASSERT_EQUAL_INT32(34,Ejemplo_suma(10,24));
} 

static void suma_dos_numeros_16(void)
{    
    TEST_ASSERT_EQUAL_INT32(16,Ejemplo_suma(8,8));
} 

int main(void)
{
    TimerSysTick_init();
    TimerSysTick_esperaMilisegundos(500);
    UNITY_BEGIN();
    RUN_TEST(suma_dos_numeros_34);
    RUN_TEST(suma_dos_numeros_16);
    UNITY_END();   
}