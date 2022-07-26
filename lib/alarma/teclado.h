#ifndef TECLADO_H
#define TECLADO_H

#include <stdio.h>
#include <stdbool.h>
#include <pin_gpio.h>
#include <string.h>


void teclado_init(void);
char teclado_lee(void);
bool comprobarClave(char* clave);

#endif