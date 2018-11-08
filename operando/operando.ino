#include <NonBlockingRtttl.h>

#define Buzzer 9
const char * stranger = "StrangerThings:d=4,o=5,b=170:8c4,8p,8c4,8g,8b,8p,8c4,8p,8c4,8g,8e,8p,8c4,8p,8c4,8g,8b,8p,8c4,8p,8c4,8g,8e,8p,8c4,8p,8c4,8g,8b,8p,8c4,8p,8c4,8g,8e,8p,8c4,8p,8c4,8g,8b,8p,8c4,8p,8c4,8g,8e,8p,8p,8e4,8e,8g,8b,8p,8c4,8p,8c4,8g,8e,8p";
const char * halloween = "Halloween:d=4,o=5,b=180:8d6,8g,8g,8d6,8g,8g,8d6,8g,8d#6,8g,8d6,8g,8g,8d6,8g,8g,8d6,8g,8d#6,8g,8c#6,8f#,8f#,8c#6,8f#,8f#,8c#6,8f#,8d6,8f#,8c#6,8f#,8f#,8c#6,8f#,8f#,8c#6,8f#,8d6,8f#";
int LED = 6;
//int Buzzer = 9;
int Touch = 7;
int intentos = 0;

const int necessary_delay = 10; //in milliseconds
bool isTouching = false; //Note how it is declared outside the loop
unsigned long countStart;
int kill = 0;



void setup() {
  pinMode(LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Touch, INPUT);
  
  Serial.begin(115200);
  Serial.println();  
}
void loop_touching()
{
  unsigned long m = millis();

  digitalWrite(LED, isTouching);
  digitalWrite(Buzzer, isTouching);

  if (digitalRead(Touch) == HIGH)
  {
    if (isTouching) {
      countStart = m;
      return;
    }
    if (m - countStart >= necessary_delay)
    {
      countStart = m;
      kill++; //once!
      Serial.println(kill); 
      isTouching = true; 
      return;
    }
  }
  else if (digitalRead(Touch) == LOW) {
    if (!isTouching) {
      countStart = m;
      return;
    }
    if (m - countStart >= necessary_delay)
    {
      countStart = m;
      isTouching = false;
      return;
    }
  }
}


void loop() {
  if ( !rtttl::isPlaying() )
  {
    rtttl::begin(Buzzer, halloween);
    if(kill > 3)
    {
      rtttl::stop();
      rtttl::begin(Buzzer, stranger);
      
    }    
  }
  else
  {
    rtttl::play();
  }


  loop_touching();
}

 
