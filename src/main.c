/**
 * @file main.c
 * @author Fernando A. Miranda Bonomi (fmirandabonomi@herrera.unt.edu.ar)
 * @brief Esqueleto de aplicación con una función de configuración y un lazo infinito.
 */
#include <main.h>

int main(void)
{
    setup();
    for(;;)loop();
    return 0;
}
