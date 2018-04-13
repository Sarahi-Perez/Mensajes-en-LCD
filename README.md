# Mensajes-en-LCD
Proyecto para mandar mensajes desde java a pantalla LCD con arduino.

Programa que muestra la hora, la temperatura, la fecha e imprime algun mensaje que el usuario manda desde una interfaz realizada en java, en una pantalla LCD y segun la temperatura registrada, se enciende un led ( si es calor y mucho calor se enciende el led naranja, si es agradable se encianede el led verde, si es frio y mucho frio se enciende el led azul), y cada determinado tiempo, cambia del mensaje al mostrar la hora y fecha y despues cambia a la temperatura. El texto se mueve a la izquierda y regresa a la derecha. Al enviarse el mensaje desde java, se limpia el JTextField(cuadro de texto) automaticamente, cuenta el numero de caracteres, no debe ser mayor a 32, de preferencia deben de ser mensajes menores o iguales a 16, al darle clic al boton de Fecha/Hora se muestra en la pantalla LCD la fecha y hora, y al darle clic al boton de temperatura, se muestra en la pantalla LCD la temperatura y un mensaje de si hace mucho calor, o calor o confort o frio o mucho frio segun sea la temperatura registrada y enciende los correspondientes leds.

MATERIALES:
- 3 leds
- 3 resistencias de 220 ohms
- 2 resistencias de 1 kilohms
- 2 botones
- 1 TinyRTC I2C
- Arduino UNO
- Pantalla LCD 16x2
- Potenciometro de 10 kilohms
- cables de conexion
- 1 LM25

SOFTWARE UTILIZADO:
- Java NetBeans
- Arduino
- Fritzing

NOTA: en la carpeta con el nombre "lcdprinter", se incluye las clases de java, una es el frame y el otro es el codigo. Y en la carpeta "Librerias" se incluyen las librerias a utilizar (solo coloca una en tu proyecto, la diferencia entre ambas es que la version 3 tiene mas componentes que la version 2.7)

![Esquema de la conexion con la pantalla LCD](https://github.com/Sarahi-Perez/Mensajes-en-LCD/blob/master/lcd_schem11.png "Esquema de la conexion con la pantalla LCD")

![Esquema del circuito](https://github.com/Sarahi-Perez/Mensajes-en-LCD/blob/master/circuito_esquem%C3%A1tico.jpg
 "Esquema del circuito")
 
 ![Interfaz en Java](https://github.com/Sarahi-Perez/Mensajes-en-LCD/blob/master/java.jpg "Interfaz en Java")
 
 ![Imagen del circuito](https://github.com/Sarahi-Perez/Mensajes-en-LCD/blob/master/30652856_1654206154661486_6413428192123551744_n.jpg)
 
 ![Imagen del circuito](https://github.com/Sarahi-Perez/Mensajes-en-LCD/blob/master/30657331_1654206121328156_1496173654520627200_n.jpg)
 
![Imagen del circuito](https://github.com/Sarahi-Perez/Mensajes-en-LCD/blob/master/30689308_1654206111328157_4690709984994918400_n.jpg)


![Imagen del circuito](https://github.com/Sarahi-Perez/Mensajes-en-LCD/blob/master/30697784_1654206104661491_2917003674179862528_n.jpg)
