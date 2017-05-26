// librerias usadas
#include <Servo.h>
Servo miServo;
Servo miServo1;
Servo miServo2;
Servo miServo3;

// Conexiones a motor puente h l298n
int ai1 = 9;
int ai2 = 10;
int bi1 = 11;
int bi2 = 12;

// Inicio de anuglos servos
int angulo=20; // derecha
int angulo1=45; //pinza
int angulo2=50; // izquierda
int angulo3=90; // base
char state = 0; // Variable lectrura serial

// partitura de Cancion Star Wars
#define  c3    7634
#define  d3    6803
#define  e3    6061
#define  f3    5714
#define  g3    5102
#define  a3    4545
#define  b3    4049
#define  c4    3816    // 261 Hz
#define  d4    3401    // 294 Hz
#define  e4    3030    // 329 Hz
#define  f4    2865    // 349 Hz
#define  g4    2551    // 392 Hz
#define  a4    2272    // 440 Hz
#define  a4s   2146
#define  b4    2028    // 493 Hz
#define  c5    1912    // 523 Hz
#define  d5    1706
#define  d5s   1608
#define  e5    1517    // 659 Hz
#define  f5    1433    // 698 Hz
#define  g5    1276
#define  a5    1136
#define  a5s   1073
#define  b5    1012
#define  c6    955
#define  R     0      // Define a special note, ‘R’, to represent a rest
// Melody 1: Star Wars Imperial March
int melody1[] = {  a4, R,  a4, R,  a4, R,  f4, R, c5, R,  a4, R,  f4, R, c5, R, a4, R,  e5, R,  e5, R,  e5, R,  f5, R, c5, R,  g5, R,  f5, R,  c5, R, a4, R};
int beats1[]  = {  50, 20, 50, 20, 50, 20, 40, 5, 20, 5,  60, 10, 40, 5, 20, 5, 60, 80, 50, 20, 50, 20, 50, 20, 40, 5, 20, 5,  60, 10, 40, 5,  20, 5, 60, 40};
// Melody 2: Star Wars Theme
int melody2[] = {  f4,  f4, f4,  a4s,   f5,  d5s,  d5,  c5, a5s, f5, d5s,  d5,  c5, a5s, f5, d5s, d5, d5s,   c5};
int beats2[]  = {  21,  21, 21,  128,  128,   21,  21,  21, 128, 64,  21,  21,  21, 128, 64,  21, 21,  21, 128 };
int MAX_COUNT = sizeof(melody1) / 2;
long tempo = 10000;
int pause = 1000;
int rest_count = 50;
int toneM = 0;
int beat = 0;
long duration  = 0;
int potVal = 0;
int speakerOut = 11;
int led = 6;

//variables para sensor gas
int count1,count;
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

// led rgb
int redPin = 10;
int greenPin = 9;
int bluePin = 8;
int redPin1 = 3;
int greenPin1 = 4;
int bluePin1 = 5;
// Conexion bluettoth
#include <SoftwareSerial.h>
SoftwareSerial blue(0,1);
// /_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
 // /_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
 //           VOID SETUP
 //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
 // /_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
void setup() {
   pinMode(53,OUTPUT);
       pinMode(52,OUTPUT);
       pinMode(51,OUTPUT);
       pinMode(50,OUTPUT);
       pinMode(49,OUTPUT);
       pinMode(48,OUTPUT);
       pinMode(47,OUTPUT);
       pinMode(46,OUTPUT);
  Serial.begin(9600);
  pinMode(ai1,OUTPUT);
  pinMode(ai2,OUTPUT);
  pinMode(bi1,OUTPUT);
  pinMode(bi2,OUTPUT);
  miServo.attach(4);
  miServo1.attach(5);
  miServo2.attach(6);
  miServo3.attach(7);
  Serial.begin(9600);
  pinMode(speakerOut, OUTPUT);
  pinMode(led, OUTPUT);
    blue.begin(9600);
  blue.println("Conectado");
   pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
     pinMode(redPin1, OUTPUT);
  pinMode(greenPin1, OUTPUT);
  pinMode(bluePin1, OUTPUT);  
  
Gas();
}
 
 // /_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
 //           VOID LOOP
 //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
 

void loop() {
  // Gas;
  Gas;
 //si el modulo a manda dato, guardarlo en estado.
  if(Serial.available() > 0){
       state = Serial.read();
  } // esta parte del código es para solo 1 Carácter o Unidad. 
 switch (state)
 {
    case '0':
       detener();
       Serial.print("reversa");
   break;
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .   
   case '1':
      adelante();
      Serial.print("adelante");
   break;
 // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
   case '2':
       reversa();
       Serial.print("reversa");
   break;
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .   
   case '3':
      izquierda();
      Serial.print("izquierda");
   break;
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .   
   case '4':
        derecha();
        Serial.print("derecha");
   break;
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// pinza
   case '5':
   bp1();      
        Serial.print("bp1+");
   break;
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    case '6':
    bp2();     
        Serial.print("p1-");
   break;
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
 // brazo dere
   case '7':
   bder1();     
        Serial.print("bd1");
   break;
 // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
  case '8':
  bder2();      
        Serial.print("bd1");
   break;
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
//brazo izquieda   
   case 'a':
   diz1();      
        Serial.print("bd1");
   break;
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .   
   case 'b':
   diz2();      
        Serial.print("bd1");
   break;
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// base brazo
   case 'c':
   base1();      
        Serial.print("bd1");
   break;
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
case 'd':
   base2();      
        Serial.print("bd1");
   break;
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
case 'x':
  music();     
        Serial.print("bd1");
   break;
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
  case 'o':
    setColor(80, 0, 80);  // Blanco
        Serial.print("bd1");
   break;
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
case 'p':
    
   setColor(255, 255, 0);  // Azul
        Serial.print("bd1");
   break;
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
   default:
        
     Serial.println("NO VAL");
   break;
 // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
   
 }
   angulo=constrain(angulo,0,180);//restringimos el valor de 0 a 180
   angulo1=constrain(angulo1,0,180);//restringimos el valor de 0 a 180
   angulo2=constrain(angulo2,0,180);//restringimos el valor de 0 a 180
  angulo3=constrain(angulo3,0,180);//restringimos el valor de 0 a 180

   miServo.write(angulo);  
  miServo1.write(angulo1);  
  miServo2.write(angulo2);  
  miServo3.write(angulo3);  
  //Serial.print("Angulo:");Serial.println(angulo );
  delay(100);


}
 // /_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
 //           MOTORES DIRRECCION
 //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void adelante(){
  digitalWrite(ai1,LOW);
  digitalWrite(ai2,HIGH);
  digitalWrite(bi1,LOW);
  digitalWrite(bi2,HIGH);

}
 
void derecha(){
  digitalWrite(ai1,LOW);
  digitalWrite(ai2,HIGH);
  digitalWrite(bi1,HIGH);
  digitalWrite(bi2,LOW);
}
 
void izquierda(){
  digitalWrite(ai1,HIGH);
  digitalWrite(ai2,LOW);
  digitalWrite(bi1,LOW);
  digitalWrite(bi2,HIGH);
}
 
void reversa(){
    digitalWrite(ai1,HIGH);
  digitalWrite(ai2,LOW);
  digitalWrite(bi1,HIGH);
  digitalWrite(bi2,LOW);
}
void detener(){
  digitalWrite(ai1,LOW);
  digitalWrite(ai2,LOW);
  digitalWrite(bi1,LOW);
  digitalWrite(bi2,LOW);
}

// /_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
 //           playtone
 //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void playTone() {

long elapsed_time = 0;
if (toneM > 0) {

          digitalWrite(led,HIGH);

while (elapsed_time < duration) {
digitalWrite(speakerOut,HIGH);
delayMicroseconds(toneM / 2);
digitalWrite(speakerOut, LOW);
delayMicroseconds(toneM / 2);
elapsed_time += (toneM);

       }

digitalWrite(led,LOW);

}
else {
for (int j = 0; j < rest_count; j++) {
delayMicroseconds(duration);
}

}

}
 // /_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
 //           Sonido
 //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/



 
void music()
{
        // Melody1
    for (int i=0; i<MAX_COUNT; i++) {
    toneM = melody1[i];
    beat = beats1[i];
    duration = beat * tempo;
    playTone();
    delayMicroseconds(pause);
    }
    // Melody2
    MAX_COUNT = sizeof(melody2) / 2;
    for (int i = 0; i < MAX_COUNT; i++) {
    toneM = melody2[i];
    beat = beats2[i];
    duration = beat * tempo;
    playTone();
    delayMicroseconds(pause);
}
}
 // /_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
 //           Mov brazo
 //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
 // brazo derecho
 void bder1(){
    angulo+=10;//incrementamos 10
 }
  void bder2(){   
    angulo-=10;//decrementamos 10
  }
 // _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
 //brazo pinza
 void bp1(){
    angulo1+=30;//incrementamos 10
 }
  void bp2(){
   angulo1-=30;//decrementamos 10
  }   
     // _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//brazo izquierdo     
 void diz1(){
    angulo2+=10;//incrementamos 10
 }    
 void diz2(){
    angulo2-=10;//decrementamos 10
 }
    // _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
// brazo base    
 void base1(){
    angulo3+=10;//incrementamos 10
 }
 void base2(){
  angulo3-=10;//decrementamos 10
 }

  // /_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
 //           Sensor gas
 //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void Gas()
{
  
  count1++;
  sensorValue = analogRead(analogInPin);            
  outputValue = map(sensorValue, 0, 1023, 0, 180);          
 //------------------------------------------------------------------------------------------------------
 if(count1==5)
  {
    count1=0;  
   // Serial.print("\t output = ");      
   // Serial.println(outputValue);
   }
  count++;
  delay(2);
  if(outputValue>=0 && outputValue<=19){
    blue.println("Normal");
    //Serial.println("Normal");
    }
  if(outputValue>=20 && outputValue<=40){
       blue.println("Cautela");
    //Serial.println("Cautela");
    }
  if(outputValue>=41 && outputValue<=60){
    blue.println("Alerta");
   // Serial.println("Alerta");
   }
     if(outputValue>=61){
    blue.println("Emergencia");
    //Serial.println("Emergencia");
    }
   
}


  // /_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
 //           Colores
 //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue); 
  analogWrite(redPin1, red);
  analogWrite(greenPin1, green);
  analogWrite(bluePin1, blue);   
}








