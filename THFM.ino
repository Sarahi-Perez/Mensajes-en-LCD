/*
 * Programa que muestra la hora, la temperatura, la fecha e imprime algun mensaje que el usuario manda desde una interfaz realizada en java, 
 * en una pantalla LCD y segun la temperatura registrada, se enciende un led ( si es calor y mucho calor se enciende el led naranja, si es agradable se encianede el led verde,
 * si es frio y mucho frio se enciende el led azul), y cada determinado tiempo, cambia del mensaje al mostrar la hora y fecha y despues cambia a la temperatura. 
 * El texto se mueve a la izquierda y regresa a la derecha. 
*/
// Incluímos la libreria externa para poder utilizarla
#include <LiquidCrystal.h> // Entre los símbolos <> buscará en la carpeta de librerías configurada
#include <Wire.h>
#include "RTClib.h"

// Definimos las constantes
#define COLS 16 // Columnas del LCD
#define ROWS 2 // Filas del LCD
#define VELOCIDAD 300 // Velocidad a la que se mueve el texto
#define ARRAYTXT 5 // Número de textos a escribir

// Lo primero is inicializar la librería indicando los pins de la interfaz
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
RTC_DS1307 RTC; //variable inicializada para el RTC (el reloj)

// Variable de Texto, para almacenar los caracteres que reciba del puerto serial
String mensaje = "";

//Botones para intercambio de lo que se puede mostrar, esto es opcional
int btnFecha = 6;
int btnTemp = 7;

//Variables globales para la temperatura
float tempC; // Variable para almacenar el valor obtenido del sensor (0 a 1023)
int pinLM35 = 0; // Variable del pin de entrada del sensor (A0)
int indice; //Posicion del array de textos

//Leds para la muestra de la temperatura, dependiendo el grado de temperatura es el led que enciende
int ledNaranja = 10; //Muestra si hace calor
int ledVerde = 9; // Muestra si es agradable
int ledAzul = 8; // MUestra si hace frio

void setup() 
{
  // Configuración monitor serie
  Serial.begin(9600);

  // Configuramos las filas y las columnas del LCD en este caso 16 columnas y 2 filas
  lcd.begin(COLS, ROWS);

  //Inicializacion de los botones
  pinMode(btnFecha,INPUT);
  pinMode(btnTemp,INPUT);

  //Inicializacion de los leds
  pinMode(ledNaranja, OUTPUT);//Inicializa el pin 10 para el led naranja
  pinMode(ledVerde, OUTPUT);//Inicializa el pin 9 para el led verde
  pinMode(ledAzul, OUTPUT);//Inicializa el pin 8 para el led azul

  Wire.begin(); //configura el bus I2C estableciendo arduino como MASTER
  RTC.begin(); //configura el RTC
  if (! RTC.isrunning()) // se verifica si el modulo rtc esta en funcionamiento, de lo contrario, se imprime: RTC is NOT running!
  {
    lcd.println("RTC is NOT running!");
    delay(10000);
  }
  RTC.adjust(DateTime(__DATE__, __TIME__)); //esta funcion establecera en el modulo la fecha de creación del archivo .hex generado al compilar el sketch.
 
}

void loop() 
{

  //Se lee si el boton esta siendo precionado o no, si esta precionado es 1, sino es 0
  int estadobtnFecha = digitalRead(btnFecha);
  int estadobtnTemp = digitalRead(btnTemp);
  
  // Obtenemos si hay algo en el puerto serial
  while(Serial.available() > 0)
  {
    //concatenamos en la variable mensaje todo lo que se lee del puerto serial y se hace un cambio por el simbolo (como es recibido de forma ASCII)
    mensaje = mensaje + Cambio(Serial.read()) ;
  }
  //Obtenemos el tamaño del mensaje
  int tam_texto = mensaje.length();

  //Validamos para que el tamaño del texto no sea muy grande
  if(tam_texto <= 16)
  {
      // Mostramos entrada texto por la izquierda
    for(int i=tam_texto; i>0 ; i--)
    {
      String texto = mensaje.substring(i-1);
  
      // Limpiamos pantalla
      lcd.clear();
  
      //Situamos el cursor
      lcd.setCursor(0, 0);
  
      // Escribimos el texto
      lcd.print(texto);
  
      // Esperamos
      delay(VELOCIDAD);
    }
  
    // Desplazamos el texto hacia la derecha
    for(int i=1; i<=16;i++)
    {
      // Limpiamos pantalla
      lcd.clear();
  
      //Situamos el cursor
      lcd.setCursor(i, 0);
  
      // Escribimos el texto
      lcd.print(mensaje);
  
      // Esperamos
      delay(VELOCIDAD);
    }
  
    // Desplazamos el texto hacia la izquierda en la segunda fila
    for(int i=16;i>=1;i--)
    {
      // Limpiamos pantalla
      lcd.clear();
  
      //Situamos el cursor
      lcd.setCursor(i, 1);
  
      // Escribimos el texto
      lcd.print(mensaje);
  
      // Esperamos
      delay(VELOCIDAD);
    }
  
    // Mostramos salida del texto por la izquierda
    for(int i=1; i<=tam_texto ; i++)
    {
      String texto = mensaje.substring(i-1);
  
      // Limpiamos pantalla
      lcd.clear();
  
      //Situamos el cursor
      lcd.setCursor(0, 1);
  
      // Escribimos el texto
      lcd.print(texto);
  
      // Esperamos
      delay(VELOCIDAD);
    }
  }
  else    
  {
    mensaje = "Mensaje muy largo"; //Mensaje de error si es muy largo el mensaje
    lcd.print(mensaje);
 }

//Verifica si el boton esta siendo precionado
  if(estadobtnFecha == 1)
  {
    //limpia la pantalla
    lcd.clear();
    fechaHora(); //manda llamar al metodo que se debe ejecutar
    delay(1000); // la duracion de la ejecucion
  }

  //Verifica si el boton esta siendo precionado
  if(estadobtnTemp == 1)
  {
    lcd.clear(); //limpia la pantalla
    temperatura(); //manda llmar al metodo que se debe ejecutar
  }

  mensaje = ""; // se limpia la variable
}

//Metodo para hacer el cambio a los simbolos, dependiendo el numero que reciba
  char Cambio(int entrada)
  {
    char salida=' ';
  switch(entrada){
    case 32: 
      salida=' '; 
      break; 
    case 33: 
      salida='!'; 
      break; 
    case 34: 
      salida='"'; 
      break; 
    case 35: 
      salida='#'; 
      break; 
    case 36: 
      salida='$'; 
      break; 
    case 37: 
      salida='%'; 
      break; 
    case 38: 
      salida='&'; 
      break; 
    case 39: 
      salida=' '; 
      break; 
    case 40: 
      salida='('; 
      break; 
    case 41: 
      salida=')'; 
      break; 
    case 42: 
      salida='*'; 
      break; 
    case 43: 
      salida='+'; 
      break; 
    case 44: 
      salida=','; 
      break; 
    case 45: 
      salida='-'; 
      break; 
    case 46: 
      salida='.'; 
      break; 
    case 47: 
      salida='/'; 
      break; 
    case 48: 
      salida='0'; 
      break; 
    case 49: 
      salida='1'; 
      break; 
    case 50: 
      salida='2'; 
      break; 
    case 51: 
      salida='3'; 
      break; 
    case 52: 
      salida='4'; 
      break; 
    case 53: 
      salida='5'; 
      break; 
    case 54: 
      salida='6'; 
      break; 
    case 55: 
      salida='7'; 
      break; 
    case 56: 
      salida='8'; 
      break; 
    case 57: 
      salida='9'; 
      break; 
    case 58: 
      salida=':'; 
      break; 
    case 59: 
      salida=';'; 
      break; 
    case 60: 
      salida='<'; 
      break; 
    case 61: 
      salida='='; 
      break; 
    case 62: 
      salida='>'; 
      break; 
    case 63: 
      salida='?'; 
      break; 
    case 64: 
      salida='@'; 
      break; 
    case 65: 
      salida='A'; 
      break; 
    case 66: 
      salida='B'; 
      break; 
    case 67: 
      salida='C'; 
      break; 
    case 68: 
      salida='D'; 
      break; 
    case 69: 
      salida='E'; 
      break; 
    case 70: 
      salida='F'; 
      break; 
    case 71: 
      salida='G'; 
      break; 
    case 72: 
      salida='H'; 
      break; 
    case 73: 
      salida='I'; 
      break; 
    case 74: 
      salida='J'; 
      break; 
    case 75: 
      salida='K'; 
      break; 
    case 76: 
      salida='L'; 
      break; 
    case 77: 
      salida='M'; 
      break; 
    case 78: 
      salida='N'; 
      break; 
    case 79: 
      salida='O'; 
      break; 
    case 80: 
      salida='P'; 
      break; 
    case 81: 
      salida='Q'; 
      break; 
    case 82: 
      salida='R'; 
      break; 
    case 83: 
      salida='S'; 
      break; 
    case 84: 
      salida='T'; 
      break; 
    case 85: 
      salida='U'; 
      break; 
    case 86: 
      salida='V'; 
      break; 
    case 87: 
      salida='W'; 
      break; 
    case 88: 
      salida='X'; 
      break; 
    case 89: 
      salida='Y'; 
      break; 
    case 90: 
      salida='Z'; 
      break; 
    case 91: 
      salida='['; 
      break; 
    case 92: 
      salida=' '; 
      break; 
    case 93: 
      salida=']'; 
      break; 
    case 94: 
      salida='^'; 
      break; 
    case 95: 
      salida='_'; 
      break; 
    case 96: 
      salida='`'; 
      break; 
    case 97: 
      salida='a'; 
      break; 
    case 98: 
      salida='b'; 
      break; 
    case 99: 
      salida='c'; 
      break; 
    case 100: 
      salida='d'; 
      break; 
    case 101: 
      salida='e'; 
      break; 
    case 102: 
      salida='f'; 
      break; 
    case 103: 
      salida='g'; 
      break; 
    case 104: 
      salida='h'; 
      break; 
    case 105: 
      salida='i'; 
      break; 
    case 106: 
      salida='j'; 
      break; 
    case 107: 
      salida='k'; 
      break; 
    case 108: 
      salida='l'; 
      break; 
    case 109: 
      salida='m'; 
      break; 
    case 110: 
      salida='n'; 
      break; 
    case 111: 
      salida='o'; 
      break; 
    case 112: 
      salida='p'; 
      break; 
    case 113: 
      salida='q'; 
      break; 
    case 114: 
      salida='r'; 
      break; 
    case 115: 
      salida='s'; 
      break; 
    case 116: 
      salida='t'; 
      break; 
    case 117: 
      salida='u'; 
      break; 
    case 118: 
      salida='v'; 
      break; 
    case 119: 
      salida='w'; 
      break; 
    case 120: 
      salida='x'; 
      break; 
    case 121: 
      salida='y'; 
      break; 
    case 122: 
      salida='z'; 
      break; 
    case 123: 
      salida='{'; 
      break; 
    case 124: 
      salida='|'; 
      break; 
    case 125: 
      salida='}'; 
      break; 
    case 126: 
      salida='~'; 
      break; 
  }
  return salida;
}

//metodo para que la temperatura se pueda visualizar y enciendan los leds
void temperatura()
{
  //un texto que se imprime segun la temperatura que marque
   String textos[ARRAYTXT] = {"Mucho Calor", "Calor", "Confort", "Frio", "Mucho Frio"};
   
  //Obtenemos datos del sensor
  // Con analogRead leemos el sensor, recuerda que es un valor de 0 a 1023
  tempC = analogRead(pinLM35);
  
  // Calculamos la temperatura con la fórmula
  tempC = (5.0 * tempC * 100.0)/1024.0; 

  //Mostramos texto en LCD
  // Lo primero es borrar toda la pantallas
  lcd.clear();

  // Escribimos un mensaje en el LCD, por defecto empieza en la fila 0 y columna 0
  lcd.print("Temp. "+String(tempC)+"C");

  //Instrucciones para determinar el rango de temperatura
  if (tempC > 30){
     indice = 0; //mensaje del arreglo a imprimir
     digitalWrite(ledNaranja,HIGH); //enciende el led naranja
     digitalWrite(ledVerde,LOW); //apaga el led verde
     digitalWrite(ledAzul,LOW); //apaga el led azul
  }else{
    if (tempC > 24){
        indice = 1; //mensaje del arreglo a imprimir
        digitalWrite(ledNaranja,HIGH); //enciende el led naranja
        digitalWrite(ledVerde,LOW); //apaga el led verde
        digitalWrite(ledAzul,LOW); //apaga el led azul
      }else{
        if (tempC > 18){
            indice = 2; //mensaje del arreglo a imprimir
            digitalWrite(ledNaranja,LOW); //apaga el led naranja
            digitalWrite(ledVerde,HIGH); //enciende el led verde
            digitalWrite(ledAzul,LOW); //apaga el led azul
          } else{
            if (tempC > 10){
                indice = 3; //mensaje del arreglo a imprimir
                digitalWrite(ledNaranja,LOW); //apaga el led naranja
                digitalWrite(ledVerde,LOW); //apaga el led verde
                digitalWrite(ledAzul,HIGH); //enciende el led azul
              } else{
                  indice = 4; //mensaje del arreglo a imprimir
                  digitalWrite(ledNaranja,LOW); //apaga el led naranja
                  digitalWrite(ledVerde,LOW); //apaga el led verde
                  digitalWrite(ledAzul,HIGH); //enciende el led azul
                }
            }
        }
    }

  //Escribimos en la fila de abajo
  lcd.setCursor(0,1);
      
  // Escribimos mensaje
  lcd.print(textos[indice]);
    
  // Esperamos un tiempo para repetir el loop
  delay(1000);
}

//metodo para mostrar la fecha y hora
void fechaHora()
{
  DateTime now = RTC.now(); //obtiene datos del modulo RTC
  lcd.clear(); //limpia la pantalla 
  lcd.setCursor(0,0); //el curso de la pantalla
  //checa el dia 
  if(now.day() < 10) 
  {
    lcd.print("0");
  }
  lcd.print(now.day(), DEC); //imprime dia
  lcd.print('/');
  //checa el mes
  if(now.month() < 10)
  {
    lcd.print("0");
  }
  lcd.print(now.month(), DEC); //imprime mes
  lcd.print('/');
  lcd.print(now.year(), DEC);  //imprime el año
  lcd.setCursor(0,1);
  //ceha la hora
  if(now.hour() < 10)
  {
    lcd.print("0");
  }
   lcd.print(now.hour(), DEC); //imprime hora
   lcd.print(':');
   //checa los minutos
   if(now.minute() < 10)
   {
     lcd.print("0");
   }
  lcd.print(now.minute(), DEC); //imprime minutos
  lcd.print(':');
  //checa los segundos
  if(now.second() < 10)
  {
    lcd.print("0");
  }
  lcd.print(now.second(), DEC); //imprime segundos
}
