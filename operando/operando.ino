#include <NonBlockingRtttl.h>

#define Buzzer 9

//Melodías en format RTTTL
const char * stranger = "StrangerThings:d=4,o=5,b=170:8c4,8p,8c4,8g,8b,8p,8c4,8p,8c4,8g,8e,8p,8c4,8p,8c4,8g,8b,8p,8c4,8p,8c4,8g,8e,8p,8c4,8p,8c4,8g,8b,8p,8c4,8p,8c4,8g,8e,8p,8c4,8p,8c4,8g,8b,8p,8c4,8p,8c4,8g,8e,8p,8p,8e4,8e,8g,8b,8p,8c4,8p,8c4,8g,8e,8p";
const char * halloween = "Halloween:d=4,o=5,b=180:8d6,8g,8g,8d6,8g,8g,8d6,8g,8d#6,8g,8d6,8g,8g,8d6,8g,8g,8d6,8g,8d#6,8g,8c#6,8f#,8f#,8c#6,8f#,8f#,8c#6,8f#,8d6,8f#,8c#6,8f#,8f#,8c#6,8f#,8f#,8c#6,8f#,8d6,8f#";

int LED = 6;
int Touch = 7;
int RESET = 10;

//Led RGB
int pinRojo = 4;
int pinVerde = 3;
int pinAzul = 5;

const int necessary_delay = 20; //milliseconds
bool isTouching = false;
unsigned long countStart;
int kill = 0;

void loopJuego() {
  unsigned long m = millis();

  digitalWrite(LED, isTouching);
  digitalWrite(Buzzer, isTouching);

  if (digitalRead(Touch) == HIGH) {
    if (isTouching) {
      countStart = m;
      return;
    }
    if (m - countStart >= necessary_delay) {
      countStart = m;
      kill++;
      cambiarColor(kill);
      Serial.println(kill);
      isTouching = true;
      return;
    }
  } else if (digitalRead(Touch) == LOW) {
    if (!isTouching) {
      countStart = m;
      return;
    }
    if (m - countStart >= necessary_delay) {
      countStart = m;
      isTouching = false;
      return;
    }
  }


}

//Colores
void setColor(int red, int green, int blue) {
  analogWrite(pinRojo, red);
  analogWrite(pinVerde, green);
  analogWrite(pinAzul, blue);
}

void cambiarColor(int kill) {
  
  if (kill > 1 && kill < 3) {
    setColor(52, 205, 255); //azul
  }
  if (kill > 2 && kill < 5) {
    setColor(118, 173, 253); //azul
  }
  if (kill > 4 && kill < 7) {
    setColor(0, 9, 228); //azul
  }
  if (kill > 6 && kill < 8) {
setColor(35, 85, 211); //azul
  }
  if (kill > 7 && kill < 10) {
    setColor(253, 0, 87); //morado
  }
  if (kill > 8) {
    setColor(179, 0, 223); //morado
  }
  if (kill > 9) {
    setColor(255, 0, 0); //rojo
  }
}

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Touch, INPUT);
  pinMode(RESET, INPUT);
  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);

  setColor(128, 128, 0); //Verde

  Serial.begin(115200);
  Serial.println();
}


void loop() {
  if (!rtttl::isPlaying()) {
    rtttl::begin(Buzzer, halloween);

    if (kill > 9) {
      rtttl::stop();
      rtttl::begin(Buzzer, stranger); //cambio de melodía
    }
  } else {
    rtttl::play();
  }

  loopJuego();
  
  //Si presionan RESET
  if(digitalRead(RESET) == HIGH){
    Serial.println("RESET");
    if(rtttl::isPlaying()){
      rtttl::stop();
      rtttl::begin(Buzzer, halloween); //cambio de melodía
      setColor(128, 128, 0); //Verde
      kill=0;
      delay(1000);
    }
  }  
}