#include <NonBlockingRtttl.h>

#define Buzzer 9

//Melodías en format RTTTL
//https://en.wikipedia.org/wiki/Ring_Tone_Transfer_Language
const char * stranger = "StrangerThings:d=4,o=5,b=170:8c4,8p,8c4,8g,8b,8p,8c4,8p,8c4,8g,8e,8p,8c4,8p,8c4,8g,8b,8p,8c4,8p,8c4,8g,8e,8p,8c4,8p,8c4,8g,8b,8p,8c4,8p,8c4,8g,8e,8p,8c4,8p,8c4,8g,8b,8p,8c4,8p,8c4,8g,8e,8p,8p,8e4,8e,8g,8b,8p,8c4,8p,8c4,8g,8e,8p";
const char * halloween = "Halloween:d=4,o=5,b=180:8d6,8g,8g,8d6,8g,8g,8d6,8g,8d#6,8g,8d6,8g,8g,8d6,8g,8g,8d6,8g,8d#6,8g,8c#6,8f#,8f#,8c#6,8f#,8f#,8c#6,8f#,8d6,8f#,8c#6,8f#,8f#,8c#6,8f#,8f#,8c#6,8f#,8d6,8f#";

int LED = 6;
int Touch = 7;

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
      kill++; //once!
      Serial.println(kill);
      cambiarColor(kill);
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
    setColor(23, 161, 165);
  }
  if (kill > 2 && kill < 4) {
    setColor(255, 1, 206);
  }
  if (kill > 3 && kill < 7) {
    setColor(243, 171, 17);
  }
  if (kill > 6 && kill < 8) {
    setColor(243, 89, 17);
  }
  if (kill > 7 && kill < 10) {
    setColor(243, 37, 17);
  }
  if (kill > 8) {
    setColor(255, 22, 0);
  }
  if (kill > 9) {
    setColor(255, 0, 0);
  }
}

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Touch, INPUT);
  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);

  setColor(128, 128, 0); //RGB

  Serial.begin(115200);
  Serial.println();
}
//Naranaja -> rojo 
//186, 243, 17
//243, 229, 17
//243, 171, 17
//243, 89, 17
//243, 37, 17
//255, 22, 0

void loop() {
  if (!rtttl::isPlaying()) {
    rtttl::begin(Buzzer, halloween);

    if (kill > 9) {
      rtttl::stop();
      rtttl::begin(Buzzer, stranger);
    }
  } else {
    rtttl::play();
  }

  loopJuego();
}
