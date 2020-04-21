# Brazo robotico (simulacion) - Poryecto final de Circuitos IV

_Para el proyecto final de Circuitos IV, se decidio hacer un brazo robotico con microcontrolador avr y programarlo con c puro, sin embargo, debido a causas fuera del control de muchos, solo se presenta la seimulación del funcionamiento de las partes mas basicas del mismo los cuales son los motores y el microcontrolador propiamente dicho._

En esta documentación se encuentra todo lo relacionado al proyecto, desde funcionamiento hasta el proceso de creación.

## ***Para ello empecemos con el circuito de simulacion...***

Al principio se habia dicho que este proyecto se iba a realizar con joysticks o potenciometros, pero se decicio al final hacer con pulsadores, de todas formas no esta de mas decir que los robots industriales, o al menos la mayoria funcionan o con botones fisicos o digitales o simplmente son "autónomos".

Para la simulación se utilizo el software de Proteus, donde se simulaba el codigo funcionando con los componentes utilizados. Hablando de materiales, los que se usaron son los siguientes:

* El Atmega16; luego hablaremos de el a detalle.
* 5 pulsadores.
* 5 resistenacias de 1k.
* 2 servo motores.
* un motor DC (para la garra).
* un driver L293D.
* un switch.
* fuente de alimentacion para el circuito.
* fuente de alimentacion externa para los motores.

No hay mucho que mencionar sobre la mayoria de los materiales ya que son muy comunes, de todas formas el circuito esta en este repositorio.

[AQUI LA IMAGEN DEL CIRCUITO](https://github.com/Bobertwest/Proyecto-final/blob/master/circuito.png)

## Funcionamiento

Tenemos el circuito, y sabemos lo que hace, bien; pero ¿como funciona realmente o como se opera?

El circuito tiene una serie de pulsadores, donde 4 estan destinados a controlar la posicion de los dos servomotores, dos para cada servo. Al iniciar el programa, los servos se posicionan en un punto especifico, llamemosle _"set 0"_. como se dijo, cada servo funciona con dos pulsadores donde al presionar uno, el servo aumentara su posicion de uno en uno hasta que este se deje de presionar, de igual manera con el otro pulsador, pero en sentido contrario.

para entender como pasa esto hay que entender bien como funciona el servo motor y el PWM.

Antes de entrar en el tema, también se uso un motor dc para la garra; este trabaja gracias a dos salidas del microcontrolador, pero la direccion es controlada por un dirver L293D; el cual esta conectado como se muestra en el diagrama del circuito; al presionar el pulsador encargado de abrir y cerrar la garra el motor gira en una direccion por un corto periodo de tiempo y al volverse a presionar, el motor girara por el mismo periodo de tiempo pero en sentido contrario; ya que la garra solo puede estar abierta o cerrada. en el pin de _ENABLE_ del driver se conecta un switch hasta el vcc, esto para abrir y cerrar el el camino de la fuente hasta el enable y asi habilitar o deshabilitar la garra; no es necesario y no afecta el funcionamiento pero si es un detalle que en algun momento puede ser útil, talvez como un metodo de seguridad.

Las resistencias se colocaron entre los pulsadores y la tierra ya que si solo que pusieran los pulsadores desde Vcc hasta el pin, cada vez que se pulsaran, ese dato se quedaria "grabado", de alguna forma, lo que signifiraria que se tendria que volver a iniciar el porgrama para que volviera a funcionar el pulsador.


## Servo motor y PWM

El servo motor es un componente que contiene basicamente un motor dc dentro, junto a una sere de engranajes; y se caracteriza por poder ser controlable en cuanto posicion se refiere. Para que esto sea posible, el PWM juega un papel importante. El servo tiene 3 pines, el de alimentacion (**+5V**), el de tierra y el de señal por donde entraran los pulsos o la señal PWM.

**Nota:** Los servo utilizados están clasificado para una rotación de 180 °, pero en realidad solo alcanzan 160 °.

**Estas son algunas caracteristicas de los servos**
* Voltaje: 4.8-6.0 voltios
* Par: 16.6 / 20.8 oz-in. (4.8 / 6.0V)
* Velocidad: 0.15 / 0.10 seg / 60 ° (4.8 / 6.0V)
* Rotación: ~ 160 °
* Rodamiento de bolas superior simple
* Engranajes de nylon
* Motor de ferrita de 3 polos
* Dimensiones: 31.8 x 11.7 x 29 mm
* Longitud del cable: 160 mm
* Peso: 9g

El PWM o por sus siglas en ingles (modulación por ancho de pulso) es el sistema mas utilizados para controlar los servos y se basa en modificar, como su nombre lo dice, el ancho de pulso en su estado alto para asi modificar la posicion del servo, ya que el ancho del pulso es proporcional de cierta forma a la posicion del servo. Para esto, en los microcontroladores se utilizan lo que es el timer para la generacion de la onda modulable.

Ahora, para antender que tiene que ver todo esto con la posicion del servo, hay que conocer un termino llamado "Ciclo de trabajo".

### Ciclo de trabajo

Sabiendo que el periodo es el inverso a la frecuencia, modificar el ancho del pulso es modificar el **"que tanto tiempo"** esta en alto la señal dentro del rango del periodo, en cuestiones de proporcionalidad. si definimos este tiempo en porcentajes; este porcentaje se le conoce como ciclo de trabajo. Si pulso esta en alto por la mitad del periodo, se dice entonces que el ciclo de trabajo es del 50%; la posicion del servo es proporcional al ciclo de trabajo.

* [TREN DE PULSOS PARA CONTROLAR AL SERVO](http://platea.pntic.mec.es/vgonzale/cyr_0204/ctrl_rob/robotica/sistema/images/motore18.jpg)
* [OTRAS POSIBILIDADES DEL PULSO DE CONTROL](http://platea.pntic.mec.es/vgonzale/cyr_0204/ctrl_rob/robotica/sistema/images/motore12.jpg)

# ATMEGA16

Para este proyecto se escogio el microcontrolador ATMega16, la razon fue principalmente por la cantidad de pines y la documentacion tanto en la pagina oficial y foros sobre el mismo.

### Algunos de los datos mas relevantes del micro, sacados de la documentacion: ###

* Memorias de programa y de datos no volátiles.
                - 16K bytes de FLASH autoprogramable en sistema.
                        Resistencia: 1.000 ciclos de escritura / borrado.
                - Sección de código añadida opcional con bits de bloqueo independientes.
                         Programación en sistema con el programa añadido On-Chip.
                         Operación de lectura durante la escritura.
                - 512 bytes de EEPROM.
                        Resistencia: 100.000 ciclos de escritura / borrado.
                - 1K bytes de SRAM interna.
                - Bloqueo (cerradura) programable para la seguridad del software.

* Características de los periféricos.
 	- Dos Timer/Contadores de 8 bits con prescaler separado y modo comparación.
  	- Un Timer/Contador de 16 bits con prescaler separado, modo comparación y
  	   modo de captura.
  	- Comparador analógico On-Chip.
   	- Timer watchdog programable con oscilador separado On-Chip.
  	- Interface serie SPI maestro/esclavo.
    	- USART serie programable.
        	- Contador en tiempo real con oscilador separado.
      	- ADC de 10 bit y 8 canales.
     	      8 canales de terminación simple
    	      7 canales diferenciales sólo en el encapsulado TQFP.
   	      2 canales diferenciales con ganancia programable a 1x, 10x o 200x.
  	- 4 canales de PWM.
   	- Interface serie de dos hilos orientada a byte.

* Características especiales del microcontrolador.
  	- Reset de Power-on y detección de Brown-out programable.
  	- Oscilador RC interno calibrado.
  	- Fuentes de interrupción externas e internas.
   	- 6 modos de descanso: Idle, reducción de ruido ADC, Power-save,
   	  Power-down, Standby y Standby extendido.

* Tensiones de funcionamiento.
  - 2.7 - 5.5V (ATmega16L).
  - 4.5 - 5.5V (ATmega16).
              
* Niveles de velocidad.
  - 8 MHz (ATmega16L).
  - 16 MHz (ATmega16).

La documentacion de este micro es bastante amplia, sin embargo en la parte del codigo hablaremos de los registro que se usaron y lo mas importante para el proyecto.

[DOCUMENTACION](http://ww1.microchip.com/downloads/en/devicedoc/doc2466.pdf)

# Codigo

Esta es una de las partes mas importantes, ya que sin ella, el micro simplemente no haria nada.

Primero que nada, para la programación, se utilizo el software ATmel Studio 7.0; el codigo fue escrito en C y configurado para funcionar en el ATMega16.

**Ahora explicaremos las partes del codigo...**

Para esto explicaremos las partes mas relevantes y el codigo completo hasta el final.

Despues de definir la frecuencia del CPU y las librerias que se van a utilizar, se especifican los modos de los pines.
```
  DDRA &=~ (1<<PA0);
  DDRA &=~ (1<<PA1);
  DDRA &=~ (1<<PA2);
  DDRA &=~ (1<<PA3);
  DDRA &=~ (1<<PA4);
```
Lo que se hizo fue definir los pines PA0 hasta el PA4 como entrada de esta manera, estos pines son a los que estan conectados los pulsadores.

  ```
  DDRD |= (1<<PD7);
  DDRD |= (1<<PD5);
  DDRB |= (1<<PB3);
  DDRD |= (1<<PD4);
```
Se igual manera que lo anterior, aqui lo que se hizo fue definir una serie de pines, pero esta vez como salida, si seguimos la documentacion del microcontrolador, nos daremos cuenta que estos pines son especiales para tener como salidad una señal PWM, y es esto lo que necesitamos.

Ateriormente se menciono que se tenia que usar un timer, este caso no es la exepcion. se uso el timer1 y se configuro lo siguiente.
```
  TCNT1 = 0;
```
Para configurar el timer1, con TCNT1 se establece el timer con un recuento en 0.
```
  ICR1 = 2499;
```
De igual manera se establece el recuento TOP para el temporizador 1 en el registro ICR1.
```
  TCCR1A = (1<<WGM11)|(1<<COM1A1);
  TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
  TCCR2 |= (0<<FOC2)|(1<<WGM20)|(1<<WGM21)|(0<<COM20)|(1<<COM21)|(1<<CS20)|(0<<CS21)|(1<<CS22);
```
Establecemos el modo Fast PWM

ahora, la forma en la que los servos se mueven es atravez de pasos, es decir, comenzamos en un valor y aumentamos o disminuimos de uno en uno; este es el trabajo de los pulsadores, de decir cuando aumentan o diminuyen. para est se necesitan do variables para cada servo.
```
uint8_t i = 150;
uint8_t j = 65;
```
De esta manera definimos las variables, estos valores traducidos a la posicion de los servos seria el _"set 0"_; aqui es donde; si presiono un pulsador el valor aumenta y si presiono el otro este disminuye; esto se logra de la siguiente manera.
```
OCR1A = i;
OCR2 = j;
while(PINA & (1<<PA0)){
  OCR1A = i;
	_delay_ms(50);
	i = i - 1;
}
while(PINA & (1<<PA1)){
	OCR1A = i;
	_delay_ms(50);
	i = i + 1;
 }
```
Lo que se hizo es establecer los valores de las variables a los que corresponden a las salidas de los dos servos, "OCR1A y OCR2"; mientras el pulsador esta en alto o presionado, la posicion del servo sera el valor asignado, se hace un delay minimo, y se aumente en uno l aposicion y este nuevo valor se le asigna a la posicion, lo que se traduce con la movilidad del servo, y de igual manera si se hace con el otro pulsador, pero disminuyendo.

La garra, es algo diferente; para hacer el efecto de que cambie de direccion cada vez que presiones el pulsador; necesitamos haber creado una variable de estado...
```
uint8_t ESTADO = true;
```
Le damos el valor de true, ya que lo puesto solo puede ser false.

Esta variable sera como un control del estado del pulsador, ya que si el estado true, al presionar el pulsador, el motor girara en una direccion y hara que el estado cambie a false. y si es false girara en el sentido contrario y el estado volvera a cambiar; asi...
```
if (PINA & (1<<PA4))
{
  if (ESTADO == true)
	{
	  PORTB |= (1<<PB3);
		_delay_ms(500);
		PORTB &=~ (1<<PB3);
		while (PINA & (1<<PA4))
		{
					
		}
		ESTADO = !ESTADO;
	}
	else{
		PORTD |= (1<<PD4);
		_delay_ms(500);
		PORTD &=~ (1<<PD4);
		while (PINA & (1<<PA4))
		{
					
		}
		ESTADO = !ESTADO;
		}
 }
```
De la manera que se muestra, pero pasa algo; se ve un while dentro de los if's; esto es porque los pulsadores al dejarlo presionado por mucho tiempo sin importar lo insignificativo que sea; hara que el motro cambie de direcion, lo que es un comportamiento no deseado. para eso son los whiles, lo que hacen es que al presionar el pulsador, se ejecuta el proceso de ir en una direccion y esperar hasta que el pulsador sea dejado de presionar para entonces cambiar el valor del estado.

### Codigo completo ###
```
#define F_CPU 8000000UL	 //frecuencia del CPU
//librerias necesarias	
#include <avr/io.h>		
#include <stdio.h>		
#include <util/delay.h>		



int main(void)
{
	uint8_t ESTADO = true;  //variable de estado para el pulsador de la garra
	//Entradas
	DDRA &=~ (1<<PA0);
	DDRA &=~ (1<<PA1);
	DDRA &=~ (1<<PA2);
	DDRA &=~ (1<<PA3);
	DDRA &=~ (1<<PA4);
	
	
	//Salidas
	DDRD |= (1<<PD7);
	DDRD |= (1<<PD5);
	DDRB |= (1<<PB3);
	DDRD |= (1<<PD4);
		
	TCNT1 = 0;		//timer1 count en 0
	ICR1 = 2499;	//El top value del timer1 en el registro ICR1

	//establecemos el fast PWM para el pin del servo 1
	TCCR1A = (1<<WGM11)|(1<<COM1A1);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
	//fast PWM para el pin del servo 2
	TCCR2 |= (0<<FOC2)|(1<<WGM20)|(1<<WGM21)|(0<<COM20)|(1<<COM21)|(1<<CS20)|(0<<CS21)|(1<<CS22);
	uint8_t i = 150;  //posicion por defecto del servo 1
	uint8_t j = 65;   //posicion por defecto del servo 2
	while(1)
	{
		
		if (PINA & (1<<PA4))		//pulsador de la garra presionado
		{
			if (ESTADO == true)		//si el estado es true
			{
				PORTB |= (1<<PB3);		//pin que sa al driver que hace girar el motor en una direcion
				_delay_ms(500);
				PORTB &=~ (1<<PB3);		//el otro pin que hace que el motor gire en sentido contrario apagado
				while (PINA & (1<<PA4))
				{
					//esperar a que se deje de presionar el pulsador
					
				}
				ESTADO = !ESTADO;		//cambiar el estado
			}
			//lo mismo pero en estado diferente de true
			else{
				PORTD |= (1<<PD4);
				_delay_ms(500);
				PORTD &=~ (1<<PD4);
				while (PINA & (1<<PA4))
				{
					
				}
				ESTADO = !ESTADO;
			}

		}
		OCR1A = i;		//valor de i asignado al pin del servo 1
		OCR2 = j;		//valor de j asignado al pin del servo 2
		
		//mientras el pulsador determinado esta presionado dismunuir el valor de la posicion
		while(PINA & (1<<PA0)){
			OCR1A = i;
			_delay_ms(50);
			i = i - 1;
		}
		//mientras el pulsador determinado este presionado, el valor de la posicion aumentara
		while(PINA & (1<<PA1)){
			OCR1A = i;
			_delay_ms(50);
			i = i + 1;
		}
		//igual pero para el otro servo
		while(PINA & (1<<PA2)){
			OCR2 = j;
			_delay_ms(50);
			j = j - 1;
		}
		while(PINA & (1<<PA3)){
			OCR2 = j;
			_delay_ms(50);
			j = j + 1;
		}
			
}
}

```
