# EMF DETECTOR
Este proyecto se basa en un Detector de Campo Electromagnetico utilizando un ATTINY85 en el proceso

## Contenido
Este proyecto contiene El codigo en C, el codigo de prueba inicial en ARDUINO, el Proteus con el cual probamos el proyecto, y el PCB creado.

## Como Utilizar 
Para poder correr y probar el codigo:
*Primero se debe descargar: Proteus, Atmel Studio.
* Despues descargar este Branch. 
* Luego se debe entrar al programa en proteus
* Y confirmar que el Archivo.hex esta intalado en el ATTINY85
como esto:
![Proteus](https://github.com/uLatinaPma-Mechatronics/Circuitos-4/tree/master/term-projects/EMF%20DETECTOR/pasos.png)
![hex](https://github.com/uLatinaPma-Mechatronics/Circuitos-4/tree/master/term-projects/EMF%20DETECTOR/hex.png)


## Preview
![Preview](https://github.com/uLatinaPma-Mechatronics/Circuitos-4/tree/master/term-projects/EMF%20DETECTOR/preview.png)

### Notas
El codigo esta Comentado linea por linea para el entendimiento practico.
Al estar mayor al 20% de campo cambia a luz amarilla significando que se esta entrando a un rango de campo intermedio y al pasar del 66% de la lectura cambia la luz a roja significando que es un campo mas fuerte.


ESQUEMATICO Y PCB 
Hechos con el Programa EasyEda Adjuntados como PDF  
El pcb esta compuesto por un attiny 85 un buzzer, battery port, un Led RGB, un switch y la antena.

Se divide en dos capas la capa(Rojo) lleva todo el cableado que se encuentra en la parte superior de la placa la capa (azul) lleva el cableado que va debajo de los componentes para no interferir con la parte superios y que no genere ningun corto
![PCB](https://github.com/uLatinaPma-Mechatronics/Circuitos-4/tree/master/term-projects/EMF%20DETECTOR/PCB.jpeg)
