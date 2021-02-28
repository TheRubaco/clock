# clock LEDS with timer -> STM32cubeIDE

### Materiales:
1. Microcontrolador STM32F103
2. Tarjeta con 12 LEDS ubicados como en la figura 1, resistencias y pulsador.
3. Programador.
4. Buzzer 3V-5V.

### Requerimientos:
1. Únicamente usar el módulo del TIMER del microcontrolador y los GPIO necesarios.
2. Los L.E.D.s deben estar ubicados de tal forma que representen los números de un reloj análogo.
3. El sistema se debe comportar como un reloj, debe contar HORAS, MINUTOS y SEGUNDOS, manejando dos
MODOS: MODO RUN, MODO SET y MODO SET ALARMA. El sistema debe emitir un sonido de 4 pulsos espaciados
150ms para indicar que es la hora de la ALARMA. Para apagar la alarma basta con pulsar una vez el botón.
4. En MODO RUN el sistema opera normalmente contando internamente el tiempo. Para visualizar la HORA ACTUAL,
se debe pulsar UNA VEZ (corto tiempo entre 1ms – 1000ms) el botón. El sistema debe visualizar encendiendo el
LED que corresponde a las HORAS y parpadear 5 veces cada 300ms el LED que corresponde a los MINUTOS
(aproximados al múltiplo de 5 más cercano) lo cual corresponde a 1500ms de visualización, después se deben
APAGAR los LEDS.
5. En MODO SET el sistema recibe la información para fijar la HORA ACTUAL y LA ALARMA. Para pasar a MODO SET
se debe mantener pulsado el botón 10000ms. Para confirmar el paso al modo SET se debe emitir un sonido de (2)
dos pulsos con intervalos de 300ms. Una vez en el MODO SET, se debe encender el LED que corresponde a las
HORAS y pulsando UNA VEZ (corto tiempo 1ms – 1000ms) para aumentar su valor con incrementos de UNA HORA.
Para pasar a ingresar el valor de los MINUTOS, se debe mantener pulsado el botón 5000ms y debe encender el
LED correspondiente a los MINUTOS, para confirmar el paso MINUTOS se debe emitir un sonido de (3) tres pulsos
con intervalos de 300ms y pulsando UNA VEZ (corto tiempo 1ms – 1000ms) para aumentar su valor con
incrementos de 5 MINUTOS. Para volver a MODO RUN se debe mantener pulsado el botón 5000ms y para
confirmar el paso al modo RUN se deme emitir un sonido de un pulso de 2000ms.
6. Para pasar al MODO SET ALARMA se debe mantener pulsado el botón entre 5000ms y 6000ms. Para confirmar el
paso al MODO SET ALARMA se debe emitir un sonido de (3) tres pulsos con intervalos de 300ms. El procedimiento
para ajustar la hora de la alarma debe ser el mismo que se usa para ajustar la hora.
