# plantilla-e4-2022
Plantilla de proyecto para la materia Electrónica 4 de la carrera Ingeniería Electrónica, Facultad de Ciencias Exactas y Tecnología, Universidad Nacional de Tucumán.

Proyecto mínimo de PlatformIO para bluepill_f103c8 con framework CMSYS. 

Programa sencillo de parpadeo de LED integrado a la placa bluepill, para verificar funcionamiento del entorno y programador.

Configuración para pruebas usando la salida serial USART1, pin 9, con configuración 115200-8-n-1. Una librería de ejemplo y su correspondiente conjunto de pruebas para verificar la conexión serial y el funcionamiento de las pruebas en PlatformIO.

Para usar hay que modificar platformio.ini y reemplazar el valor de `test_port` por el puerto serie correcto para la configuración de cada máquina.
