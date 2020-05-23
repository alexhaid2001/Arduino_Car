//Alexander Haid,9.5.2020, Roboter_Auto_ferngesteuert, es soll das Programm aus Roboterauto_Gesamt kopiert und mittels Remote Fernbedienung und IR-Receiver mit Fernsteuerung erweitert werden.
//Libraries
#include "IRremote.h"

//RGB_Led's
  //Variablen für die jeweilige Farbe
  int LED_RED = 11;
  int LED_GREEN = 10;
  int LED_BLUE = 9;

  //Variablen für die Analogwerte der Farben
  int r_val = 0;
  int g_val = 255;
  int b_val =255;

  //delay für RGB-Led
  int del = 10;
  
//Motorenansteuerung
  // ML = beide Anschlüsse Motor Links
  // ML = beide Anschlüsse Motor Rechts

  int ML_Vorwaerts = 3;
  int ML_Rueckwaerts = 7;
  int MR_Vorwaerts = 2;
  int MR_Rueckwaerts = 4;

  //delay für Lenken
  int rl = 2000;
  
//Ultraschallsensor

  //Variablen festgelegt für Sensor
  int trig = 8;      //sendet Ultraschallwelle aus
  int echo = 12;     // empfängt Ultraschallwelle wieder
  int M2_Rueckwaerts = 2;
  int M1_Rueckwaerts = 4;

  int dauer = 0;      //Variable für Dauer, die die Welle für hin und zurück braucht
  int entfernung = 0; // Variable für Entfernung, Dauer umgerechnet

//Variable für recieiver-pin
int receiver = 5;

//Resultate werden decodiert
IRrecv irrecv(receiver);    
decode_results results;      


void setup() {
pinMode(LED_RED, OUTPUT);
pinMode(LED_GREEN, OUTPUT);
pinMode(LED_BLUE, OUTPUT);

pinMode(ML_Vorwaerts, OUTPUT);
pinMode(ML_Rueckwaerts, OUTPUT);
pinMode(MR_Vorwaerts, OUTPUT);
pinMode(MR_Rueckwaerts, OUTPUT);

pinMode(trig, OUTPUT);
pinMode(echo, INPUT);
 
irrecv.enableIRIn();
Serial.begin(9600);

}

void rgb() {                            //UP für RGB_Led's

  
  //Übergang Rot auf Grün usw...  
  while(r_val!=255)
  {
    analogWrite(LED_RED,r_val);    //Werte werden von den Zählvariablen an den Pin übergeben
    analogWrite(LED_GREEN,g_val);

    r_val++;                           //hier wird u an Rot verringert und bei Grün erhöht...
    g_val--;

    delay(del);
    
  }

  while(g_val!=255)
  {
    analogWrite(LED_GREEN,g_val);
    analogWrite(LED_BLUE,b_val);

    g_val++;
    b_val--;

    delay(del);
    
  }

   while(b_val!=255)
  {
    analogWrite(LED_BLUE,b_val);
    analogWrite(LED_RED,r_val);

    b_val++;
    r_val--;

    delay(del);
    
  }
}


//UP für die jede Richtung des Autos
void vorwaerts(){
   digitalWrite(ML_Vorwaerts, HIGH);
   digitalWrite(ML_Rueckwaerts, LOW);
   digitalWrite(MR_Vorwaerts, HIGH);
   digitalWrite(MR_Rueckwaerts, LOW);
}


void links(){
   digitalWrite(ML_Vorwaerts, LOW);
   digitalWrite(ML_Rueckwaerts, HIGH);
   digitalWrite(MR_Vorwaerts, HIGH);
   digitalWrite(MR_Rueckwaerts, LOW);
}

void rechts(){
   digitalWrite(ML_Vorwaerts, HIGH);
   digitalWrite(ML_Rueckwaerts, LOW);
   digitalWrite(MR_Vorwaerts, LOW);
   digitalWrite(MR_Rueckwaerts, HIGH);
}

void rueckwaerts(){
  digitalWrite(ML_Vorwaerts, LOW);
  digitalWrite(ML_Rueckwaerts, HIGH);
  digitalWrite(MR_Vorwaerts, LOW);
  digitalWrite(MR_Rueckwaerts, HIGH);
}

void pause(){
  digitalWrite(ML_Vorwaerts, LOW);
  digitalWrite(ML_Rueckwaerts, LOW);
  digitalWrite(MR_Vorwaerts, LOW);
  digitalWrite(MR_Rueckwaerts, LOW);
}


//UP für Ultraschallsensor
void sensor() {             

  
 digitalWrite(trig, LOW);       //stellt sicher, dass trig auf LOW ist
 digitalWrite(trig, HIGH);      //Wellen periodisch ausgesendet
 delayMicroseconds(1000);
 digitalWrite(trig, LOW);

 dauer = pulseIn(echo, HIGH);    //dauer wird am Echo-Eingang auf Variable dauer gespeichert
 entfernung = (dauer/2)/28.5;    //Umrechungsfaktor auf Entfernung
 delay(500);
 return(entfernung);

}




void translate(){
  switch(results.value)
   {
    case 0xFF629D: Serial.println("VOL+");
                   vorwaerts();
                   break;
    case 0xFFA857: Serial.println("VOL-");
                   rueckwaerts();
                   break; 
    case 0xFF02FD: Serial.println("PAUSE"); 
                   pause();
                   break;
    case 0xFFC23D: Serial.println("FAST FORWARD");
                   rechts();
                   break;
    case 0xFF22DD: Serial.println("FAST BACK");
                   links();
                   break;
    case 0xFF30CF: Serial.println("1");    
                   rgb();
                   break;        
  
   }                    
}




void loop() {
 
 while(entfernung>=15)
  {
    if (irrecv.decode(&results))
    {
      translate();
      irrecv.resume(); 
    }
  }
  
}
