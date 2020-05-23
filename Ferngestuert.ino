//Alexander Haid,9.5.2020,Fernsteurung, Das Roboter Auto soll ferngesteuert fahren

//Libraries
#include "IRremote.h"
//Variablen
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


int receiver = 6;

IRrecv irrecv(receiver);     
decode_results results;   

int ML_Vorwaerts = 3;
int ML_Rueckwaerts = 7;
int MR_Vorwaerts = 2;
int MR_Rueckwaerts = 4;

   



void setup() {
 pinMode(ML_Vorwaerts, OUTPUT);
 pinMode(ML_Rueckwaerts, OUTPUT);
 pinMode(MR_Vorwaerts, OUTPUT);
 pinMode(MR_Rueckwaerts, OUTPUT);
 irrecv.enableIRIn(); 
}

void vorwaerts(){
   digitalWrite(ML_Vorwaerts, HIGH);
   digitalWrite(ML_Rueckwaerts, LOW);
   digitalWrite(MR_Vorwaerts, HIGH);
   digitalWrite(MR_Rueckwaerts, LOW);
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
   delay(500);
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

void translate(){
  switch(results.value)

  {
    case 0xFF629D: vorwaerts();
                   break;
    case 0xFFA857: rueckwaerts();
                   break; 
    case 0xFF02FD: pause();
                   break;
    case 0xFFC23D: rechts();
                   break;
    case 0xFF22DD: links();
                   break;     
    case 0xFF30CF: rgb();
                   break;   
  }
}



void loop() {
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translate(); 
    irrecv.resume(); // receive the next value
  }  

}
