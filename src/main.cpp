#include <Arduino.h>

#define LED_0_9 2
#define LED_10_19 3
#define LED_20_29 4
#define BUZZER 5
#define ECHO_ULTRA 6
#define TRIG_ULTRA 7

void iniciarLeds(){
   pinMode(LED_20_29, OUTPUT);
   pinMode(LED_10_19, OUTPUT);
   pinMode(LED_0_9, OUTPUT);
}

void iniciarUltrassom(){
   pinMode(TRIG_ULTRA, OUTPUT);
   pinMode(ECHO_ULTRA, INPUT);
}

void iniciarBuzzer(){
   pinMode(BUZZER, OUTPUT);
}

void emitirPulsoUltrassonico(){
  digitalWrite(TRIG_ULTRA, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_ULTRA, LOW);
}

double recuperarDistanciaEmCm(){
   int duration = pulseIn(ECHO_ULTRA, HIGH);
   return duration * 0.034 / 2;
}


void emitirAvisoLongaDistancia(){
   digitalWrite(LED_20_29, HIGH);
   tone(BUZZER, 600, 10);
   delay(450);
}


void emitirAvisoMediaDistancia(){
   digitalWrite(LED_20_29, HIGH);
   digitalWrite(LED_10_19, HIGH);
   tone(BUZZER, 600, 10);
   delay(300);
}

void emitirAvisoCurtaDistancia(){
   digitalWrite(LED_20_29, HIGH);
   digitalWrite(LED_10_19, HIGH);
   digitalWrite(LED_0_9, HIGH);
   tone(BUZZER, 600, 10);
   delay(180);
}

void apagarLeds(){
   digitalWrite(LED_20_29, LOW);
   digitalWrite(LED_10_19, LOW);
   digitalWrite(LED_0_9, LOW);
}

void setup () {
   Serial.begin(115200);
   iniciarLeds();
   iniciarUltrassom();
   iniciarBuzzer();
}

void loop () { 
   emitirPulsoUltrassonico(); 
   double distanciaCM = recuperarDistanciaEmCm();
   Serial.println(distanciaCM);

   apagarLeds();

   if(distanciaCM < 30 && distanciaCM >= 20){
      emitirAvisoLongaDistancia();
   }

   if(distanciaCM < 20 && distanciaCM >= 10){
      emitirAvisoMediaDistancia();
   }

   if(distanciaCM < 10 && distanciaCM >= 0){
      emitirAvisoCurtaDistancia();
   }
}
