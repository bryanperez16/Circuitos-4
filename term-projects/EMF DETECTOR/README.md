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
![](EMF DETECTOR/pasos.png)
![](EMF DETECTOR/hex.png)


## Preview
![](https://github.com/AnelBultron/Circuitos-4/tree/patch-1/term-projects/EMF%20DETECTOR/preview.png)

### Notas
El codigo esta Comentado linea por linea para el entendimiento practico.
Al estar mayor al 20% de campo cambia a luz amarilla significando que se esta entrando a un rango de campo intermedio y al pasar del 66% de la lectura cambia la luz a roja significando que es un campo mas fuerte.


ESQUEMATICO Y PCB 
Hechos con el Programa EasyEda Adjuntados como PDF  
![](EMF DETECTOR/PCB.jpeg)
