# Proyecto_Circuitos_Digitales
# Telón automatizado con ESP32

## Descripción

Este proyecto consiste en la construcción de un sistema automatizado para controlar la subida y bajada de un telón mediante un motor DC y una placa ESP32.

El sistema utiliza un pulsador para iniciar el movimiento y cambiar el sentido de giro del motor. También cuenta con un sensor de luz que permite detener el movimiento cuando el usuario pasa la mano sobre él, generando una sombra. Adicionalmente, se incorpora un buzzer para emitir alertas sonoras.

El circuito fue montado en una maqueta funcional, en la que se integraron los componentes electrónicos y el mecanismo de movimiento.

## Componentes

• ESP32 DevKit V1 (30 pines).
• Motor DC amarillo (motor TT).
• Módulo puente H L9110S.
• Módulo de fotorresistencia (LDR de 3 pines).
• Pulsador genérico.
• Resistencia de 10 kΩ.
• Buzzer genérico (zumbador).
• Protoboard y cables jumper.
• Fuente de alimentación externa de 6 V.

## Funcionamiento

El sistema funciona mediante una máquina de estados que controla las diferentes etapas del movimiento del telón.

- **Pulsador:** inicia el movimiento y permite cambiar el sentido de giro del motor.
- **Motor DC:** se encarga de enrollar o desenrollar el telón.
- **Sensor de luz:** detecta cuando el usuario genera una sombra al pasar la mano sobre él y envía una señal para detener el motor.
- **Buzzer:** genera alertas sonoras durante el funcionamiento del sistema.

El sensor de luz trabaja con lógica invertida: cuando recibe luz entrega LOW y cuando detecta sombra entrega HIGH.

## Conexiones

La ESP32 recibe las señales del pulsador y del sensor de luz mediante sus entradas digitales. El motor se conecta a través de un puente H, que permite controlar su sentido de giro y manejar su alimentación externa. El pulsador utiliza una resistencia de 10 kΩ en configuración pull-down para mantener su estado en LOW mientras no está presionado.

La conexión entre la fuente externa del motor y la ESP32 debe compartir GND para garantizar una referencia común.

## Programación

El código fue desarrollado en Arduino IDE utilizando el soporte para placas ESP32.

Algunas de las funciones y elementos utilizados son:

enum: organiza los diferentes estados del sistema.

millis(): permite controlar el tiempo entre lecturas del pulsador y evitar rebotes.

tone(): genera el sonido del buzzer.

noTone(): detiene el sonido.

directionUp = !directionUp: permite alternar el sentido de giro del motor.

Serial: permite visualizar información del funcionamiento mediante el monitor serial.


## Consideraciones

Este proyecto fue desarrollado como una maqueta funcional, por lo que sus dimensiones y materiales se adaptaron al espacio disponible y al funcionamiento del mecanismo.

El sensor de luz se utiliza como un método de detención manual y no como un sistema de posicionamiento automático del telón.
