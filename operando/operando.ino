#include <NonBlockingRtttl.h>
#define Buzzer 9

const char * stranger = "StrangerThings:d=4,o=5,b=170:8c4,8p,8c4,8g,8b,8p,8c4,8p,8c4,8g,8e,8p,8c4,8p,8c4,8g,8b,8p,8c4,8p,8c4,8g,8e,8p,8c4,8p,8c4,8g,8b,8p,8c4,8p,8c4,8g,8e,8p,8c4,8p,8c4,8g,8b,8p,8c4,8p,8c4,8g,8e,8p,8p,8e4,8e,8g,8b,8p,8c4,8p,8c4,8g,8e,8p";
const char * halloween = "Halloween:d=4,o=5,b=180:8d6,8g,8g,8d6,8g,8g,8d6,8g,8d#6,8g,8d6,8g,8g,8d6,8g,8g,8d6,8g,8d#6,8g,8c#6,8f#,8f#,8c#6,8f#,8f#,8c#6,8f#,8d6,8f#,8c#6,8f#,8f#,8c#6,8f#,8f#,8c#6,8f#,8d6,8f#";
int LED = 6;
int Touch = 7;
int intentos = 0;

//Led RGB
int Rojo = 4;
int Verde = 3;
int Azul = 5;
//Se almacenan los valores relativos a la intensidad de cada color
//(las candelas de cada color).
int mcdRojo = 300;
int mcdVerde = 1000;
int mcdAzul = 400;
//Se realiza una relación entre las candelas de los distintos
//colores.
int GradoRojo = (mcdRojo / mcdVerde);
int GradoVerde = (mcdVerde / mcdVerde);
int GradoAzul = (mcdAzul / mcdVerde);

const int necessary_delay = 10; //in milliseconds
bool isTouching = false; //Note how it is declared outside the loop
unsigned long countStart;
int kill = 0;

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

//Colores
void EstablecerColor(int R, int G, int B) 
{
  //Se utiliza la expresión X/GradoX para multiplicar el valor de la
  //salida PWM por un número que consiga una intensidad de luz
  //equiparable entre todos los colores.
  //Se debe tener en cuenta que la salida máxima es 255, por tanto,
  //la compensación entre los colores se pierde si la relación
  //X/GradoX genera un valor superior a 255.
  analogWrite(Rojo, (R / GradoRojo));
  analogWrite(Verde, (G / GradoVerde));
  analogWrite(Azul, (B / GradoAzul));

}


void setup() 
{
  pinMode(LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Touch, INPUT);
  pinMode(Rojo, OUTPUT);
  pinMode(Verde, OUTPUT);
  pinMode(Azul, OUTPUT);
  
  EstablecerColor(0, 200, 0); //RGB
  
  Serial.begin(115200);
  Serial.println();  
}

void loop() {
  if ( !rtttl::isPlaying() )
  {
    rtttl::begin(Buzzer, halloween);
    if(kill > 3)
    {
      rtttl::stop();
      rtttl::begin(Buzzer, stranger);
      EstablecerColor(200, 0, 0); //RGB
      
    }    
  }
  else
  {
    rtttl::play();
  }


  loop_touching();
}

 
