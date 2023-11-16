
#include <LiquidCrystal_I2C.h>

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define melodyPin 8
#define pushbutton 10


//funcion de sensor
int lectHum = 0;
int porcHum = 0;

uint8_t getSoilmoisture()
{
  
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  delay(100);
  porcHum =  map(analogRead(A0), 0, 1023, 100, 0);
  lectHum =  porcHum * 10.23;
  digitalWrite(A2,LOW);
  Serial.print("Lectura Sensor: ");
  Serial.print(lectHum);
  Serial.print(".   Porcentaje de humedad: ");
  Serial.print(porcHum);
  Serial.println("%  ");
  
  //return(lectHum);
}

//funcion LED RGB
int ledVerde = 3;
int ledAzul = 5;
int ledRojo = 6;
void ledIndicator(uint8_t data) {

  if (data >= 90 && data <= 100) {
    //Serial.println("verde");
    // Verde
    digitalWrite(ledVerde,HIGH);
    digitalWrite(ledAzul,LOW);
    digitalWrite(ledRojo,LOW);
  } 
  else if (data >= 75 && data < 90) {
    //Serial.println("azul");
    // Azul
    digitalWrite(ledAzul,HIGH);
    digitalWrite(ledRojo,LOW);
    digitalWrite(ledVerde,LOW);
  } 
  else if (data >= 50 && data < 75) {
    //Serial.println("blanco");
    // Blanco
    digitalWrite(ledRojo,HIGH);
    digitalWrite(ledVerde,HIGH);
    digitalWrite(ledAzul,HIGH);
  } 
  else if (data >= 25 && data < 50) {
    //Serial.println("amarillo");
    // Amarillo
    digitalWrite(ledRojo,HIGH);
    digitalWrite(ledVerde,HIGH);
    digitalWrite(ledAzul,LOW);
  } 
  else if(data >= 0 && data < 25) {
    //Serial.println("rojo");
    // Rojo
    digitalWrite(ledRojo,HIGH);
    digitalWrite(ledVerde,LOW);
    digitalWrite(ledAzul,LOW);
  }
  else if(data == 150){
    //Serial.println("violetaAutomatico");
   //Pushbutton violeta 
    digitalWrite(ledRojo,HIGH);
    digitalWrite(ledVerde,LOW);
    digitalWrite(ledAzul,HIGH);
  }
}
  
byte gota [8]={
  0b00000,
  0b00100,
  0b01110,
  0b11111,
  0b11111,
  0b01110,
  0b00000,
  0b00000
};

byte relampago [8]={
  0b11111,
  0b11110,
  0b11100,
  0b11111,
  0b01111,
  0b01110,
  0b01100,
  0b01000
};

// funcion para escribir humedad en el LCD
LiquidCrystal_I2C lcd(39,16,2); 

void showValue ( int data)
{
  
  lcd.clear();
  
  //porcentje de humedad
  lcd.setCursor(2,0);
  lcd.print("Humedad: ");
  lcd.setCursor(11,0);
  lcd.write(0);
  lcd.setCursor(12,0);
  lcd.print(data);
  lcd.setCursor(15,0);
  lcd.print("%");
  
  //valor analogico
  lcd.setCursor(11,1);
  lcd.write(1);
  lcd.setCursor(12,1);
  lcd.print(lectHum);
  
}

// funcion para verificar porcentaje de humedad
bool checkHumidity ( uint8_t data )
{
  if( data > 85 ) // mayor a 85 = adecuado = false
  {
    return false;
  }
  else return true; // menor a 85 = necesita agua = true
}

//funcion para activar motor
int motorPin = 2;
void drainWater ( bool humidityFlag )
{
  if(humidityFlag == true){
    digitalWrite(motorPin,HIGH);
  }else digitalWrite(motorPin,LOW);
}

//funcion de elegir canción
int melodySize;
int *melody;
void playSong(uint8_t song) {
  if (song == 1) {
    // Melodía alegre
    int happyMelody[] = {
      NOTE_C5, NOTE_D5, NOTE_E5, NOTE_G5,
      NOTE_E5, NOTE_D5, NOTE_E5, NOTE_G5,
      NOTE_G5, NOTE_A5, NOTE_G5,
      NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5
    };
    
    melodySize = sizeof(happyMelody) / sizeof(int);
    melody = happyMelody;
    
  } else if (song == 2) {
    // Melodía de What's App
    int melodyWhatsapp[] = {
      NOTE_E5, NOTE_D5, NOTE_E5, NOTE_D5,
      NOTE_E5, NOTE_D5, NOTE_B4, NOTE_C5,
      NOTE_E5, NOTE_D5, NOTE_E5, NOTE_D5,
      NOTE_E5, NOTE_D5, NOTE_B4, NOTE_C5,
    };
    melodySize = sizeof(melodyWhatsapp) / sizeof(int);
    melody = melodyWhatsapp;
    //Serial.print(melodySize);
  } 

  for (int thisNote = 0; thisNote < melodySize; thisNote++) {
    //Serial.print("nota");
    int noteDuration = 250;  // Duración predeterminada
    tone(melodyPin, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(melodyPin);
  }
}

void setup()
{
  //Pushbutton
  pinMode(pushbutton, INPUT_PULLUP); //Para usar resistencia interna de arduino
  
  // entradas y salidas de sensor
  pinMode(A0, INPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
  // Configuramos los pines de los LEDs como salidas
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  
  //transmision serial
  Serial.begin(9600);
  
  //inicializar el LCD
  lcd.init();
  lcd.clear();         
  lcd.backlight();
  //crear caracteres
  lcd.createChar(0,gota);
  lcd.createChar(1,relampago);
  
  //salida de seañal al motor
  pinMode(motorPin,OUTPUT);
  //analogWrite(motorPin,0);
  
  //Serial.println("poniendo boton a 0");
  //digitalWrite(pushbutton,0); //button inicilizado en LOW = no modo automatico
}

// bool modoAutomatico = false; //para el sistema con button

int valorBotonAntes = HIGH; // es igual a 1 cuando no está presionado a causa del pullup
int valorBotonAhora;
int rutina = 0;
bool botonPresionado = false;

void loop()
{
  Serial.println("vuelta... ");
  getSoilmoisture(); //leer sensor
  showValue(porcHum); //Muestra la humedad
  valorBotonAhora = digitalRead(pushbutton);
  //Serial.println(valorBotonAhora);
  delay(1000); // tiempo para el botón
  
  // si esta activa entra
  if (valorBotonAhora != valorBotonAntes) { //cambió en el button

    if(valorBotonAhora == LOW && botonPresionado == false){ // LOW = a presionado y false = a no presionado, hasta este momento 

      botonPresionado = true; //cambiar el estado del boton a true = a presionado

      rutina = 1 - rutina; // alternar rutina con 0 y 1

      Serial.print("Cambiar a Rutina a: ");
      Serial.println(rutina);

    }

  }
  else if (valorBotonAhora == HIGH) {
                                  // si el botonAhora es alto despues de presionar significa que es igual a valorAntes
        botonPresionado = false;  // cambiamos el boleano del boton presionado porque ya no esta presionado en el momento
                                  // el valor de botonAhora cambia a LOW cada que lo presionamos y entonces entra al primer if
      }

  if(rutina == 1){ // rutina de modo automatico

    Serial.println("modo Automatico");

    showValue(porcHum);

    if (checkHumidity(porcHum)) { // <85 = true = ocupa agua = entra     

      drainWater(true); // Activar la bomba de agua
      ledIndicator(150); // Encender el LED en morado
      playSong(1); // Tocar la melodía 1

    } else{

      rutina = 0;
    }

  }else { 
    // rutina de modo normal = sin bomba
    
    Serial.println("modo Normal");
    
    drainWater(false); //desactivar la bomba de agua
    showValue(porcHum);
    ledIndicator(porcHum); // Encender el LED de acuerdo a la humedad
    playSong(2); // Tocar la melodía 2
    
  }

  delay(1000);
  Serial.println(" ");
  
}