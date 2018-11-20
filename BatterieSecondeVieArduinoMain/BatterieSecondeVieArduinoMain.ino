#include <Adafruit_NeoPixel.h>

#define MID_USINE_PIN 3 //pin de l'arduino pour les led du milleu à l'usine
#define MID_USINE_COUNT 25 //nombre de led pour le strip du milleu à l'usine

#define MID_ER_PIN 5
#define MID_ER_COUNT 21

#define MID_BATTERIE_PIN 6
#define MID_BATTERIE_COUNT 15

#define MID_MAISON_PIN 9
#define MID_MAION_COUNT 9

#define MID_VOITURE_PIN 10
#define MID_VOITURE_COUNT 9

#define ASCENSEUR_PIN 11
#define ASCENSEUR_COUNT 7

#define ASCENSEURBIS_PIN 12
#define ASCENSEURBIS_COUNT 7

#define LED_PIN 4
#define MOTOR_PIN 7

Adafruit_NeoPixel stripUsine = Adafruit_NeoPixel(MID_USINE_COUNT, MID_USINE_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripER = Adafruit_NeoPixel(MID_ER_COUNT, MID_ER_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripBatterie = Adafruit_NeoPixel(MID_BATTERIE_COUNT, MID_BATTERIE_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripMaison = Adafruit_NeoPixel(MID_MAION_COUNT, MID_MAISON_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripVoiture = Adafruit_NeoPixel(MID_VOITURE_COUNT, MID_VOITURE_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripAscenseur = Adafruit_NeoPixel(ASCENSEUR_COUNT, ASCENSEUR_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripAscenseurBis = Adafruit_NeoPixel(ASCENSEURBIS_COUNT, ASCENSEURBIS_PIN, NEO_GRB + NEO_KHZ800);



//Colors definition
int GREEN[3] = {0, 255, 25};
int CYAN[3] = {0, 255, 255};

//Speed definition
int normalSpeed = 100; //100
int ascenseurSpeed = 3;
int lagSpeed = 20;

int ascenseurLevel = 0; //last level = 6;
bool ascenseurUp = true;
bool ascenseurDown = false;
bool offFirstFloor = false;

String msg = "";
bool newStringComplete = false;
String tmpMessage;

int motorSpeed = 100; //From 0(0V) to 255(5V)

void setup() 
{
  stripUsine.begin();
  stripER.begin();
  stripBatterie.begin();
  stripMaison.begin();
  stripVoiture.begin();
  stripAscenseur.begin();
  stripAscenseurBis.begin();
  
  stripUsine.show();
  stripER.show();
  stripBatterie.show();
  stripMaison.show();
  stripVoiture.show();
  stripAscenseur.show();
  stripAscenseurBis.show();

  pinMode(LED_PIN, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() 
{
  stripUsine.setBrightness(100);
  stripER.setBrightness(100);
  stripBatterie.setBrightness(100);
  stripMaison.setBrightness(100);
  stripVoiture.setBrightness(100);
  stripAscenseur.setBrightness(100);
  stripAscenseurBis.setBrightness(100);

  if(msg.equals("peakShavingSansBatterie") || msg.equals("1"))
  {
    peakShavingSansBatterie();
  }
  else if(msg.equals("peakShavingAvecBatterie") || msg.equals("2"))
  {
    peakShavingAvecBatterie();
  }
  else if(msg.equals("autoConsommationDejourAvecBatterie") || msg.equals("3"))
  {
    autoConsommationDejourAvecBatterie();
  }
  else if(msg.equals("autoConsommationDeNuitAvecBatterie") || msg.equals("4"))
  {
    autoConsommationDeNuitAvecBatterie();
  }
  else if(msg.equals("autoConsommationDeNuitSansBatterie") || msg.equals("5"))
  {
    autoConsommationDeNuitSansBatterie();
  }
  else if(msg.equals("ilotAvecBatterie") || msg.equals("6"))
  {
    ilotAvecBatterie();
  }
  else if(msg.equals("ilotSansBatterie") || msg.equals("7"))
  {
    ilotSansBatterie();
  }
  else if(msg.equals("timeShiftingHeuresCreusesAvecBatterie") || msg.equals("8"))
  {
    timeShiftingHeuresCreusesAvecBatterie();
  }
  else if(msg.equals("timeShiftingHeuresCreusesSansBatterie") || msg.equals("9"))
  {
    timeShiftingHeuresCreusesSansBatterie();
  }
  else if(msg.equals("timeShiftingHeuresPleinesAvecBatterie") || msg.equals("10"))
  {
    timeShiftingHeuresPleinesAvecBatterie();
  }
  else if(msg.equals("timeShiftingHeuresPleinesSansBatterie") || msg.equals("11"))
  {
    timeShiftingHeuresPleinesSansBatterie();
  }
  else if(msg.equals("off"))
  {
    off();
  }
  else
  {
    off();
  }
}

void peakShavingSansBatterie() //Sénario 1 numéro 1
{
  int reverseNum = 49;
  for(int i = 0; i < 49; i++)
  {
    stripUsine.setPixelColor(reverseNum - 24, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.show(); 
    
    //eteinsUsine
    if(i > 9)
    {
      stripUsine.setPixelColor(reverseNum - 14, 0,0, 0);
      stripUsine.show(); 
    }

    //allume le mid
    if(i > 25 && i < 30)
    {
      stripBatterie.setPixelColor(i-26, CYAN[0], CYAN[1], CYAN[2]);
      stripBatterie.show();
    }

    //eteins le mid
    if(i > 34)
    {
      stripBatterie.setPixelColor(i-35, 0, 0, 0);
      stripBatterie.show();
    }

    //allumer maison
    if(i > 29)
    {
      stripMaison.setPixelColor(i-30, CYAN[0], CYAN[1], CYAN[2]);
      stripMaison.show();
      stripVoiture.setPixelColor(i-30, CYAN[0], CYAN[1], CYAN[2]);
      stripVoiture.show();
    }

    //eteins maison et voiture
    if(i > 39)
    {
      stripMaison.setPixelColor(i-40, 0, 0, 0);
      stripMaison.show();
      stripVoiture.setPixelColor(i-40, 0, 0, 0);
      stripVoiture.show();
    }

    ascenseur(i, 38);
    
    reverseNum--;
    delay(normalSpeed);
  }

  //delay(normalSpeed);
}

void peakShavingAvecBatterie() //Scénario 1 numéro 2
{
  digitalWrite(LED_PIN, HIGH);
  batterieTopLedOn();
  int reverseNum = 49;
  for(int i = 0; i < 48; i++)
  {
      stripUsine.setBrightness(5);
      stripUsine.setPixelColor(reverseNum - 25, CYAN[0], CYAN[1], CYAN[2]);
      stripUsine.show(); 

    //eteins le strip usine
      if(i > 1)
      {
        stripUsine.setPixelColor(reverseNum - 22, 0, 0, 0);
        stripUsine.show();
      }
  
  //allume le mid
  if(i > 24 && i < 29)
  {
    //stripBatterie.setBrightness(10);
    stripBatterie.setPixelColor(i - 25, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.show();
  }

 //eteins le mid
 if(i > 26 && i < 30)
 {
    stripBatterie.setPixelColor(i - 27, 0, 0, 0);
    stripBatterie.show();
 }
  
  //down la batterie en même temps que l'usine
  if(i > 15 && i < 27)
  {
    //stripBatterie.setBrightness(100);
    stripBatterie.setPixelColor(reverseNum - 19, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.show();
  }
    
  //eteins la batterie
  if(i > 29)
  {
    stripBatterie.setPixelColor(reverseNum - 5, 0, 0, 0);
    stripBatterie.show();
  }
    
  //illumine voiture et maison
  if(i > 29)
    {
      stripMaison.setPixelColor(i-30, CYAN[0], CYAN[1], CYAN[2]);
      stripMaison.show();
    
      stripVoiture.setPixelColor(i-30, CYAN[0], CYAN[1], CYAN[2]);
      stripVoiture.show();
    }
    
  //eteins voiture et maison
  if(i > 38)
    {
      stripMaison.setPixelColor(i-39, 0, 0, 0);
      stripMaison.show();

      stripVoiture.setPixelColor(i-39, 0, 0, 0);
      stripVoiture.show();
    }

    ascenseur(i, 37);
  batterieTopLedOn();
  reverseNum--;
  delay(normalSpeed);
  }

 delay(normalSpeed);
 digitalWrite(LED_PIN, LOW);
 batterieTopLedOff();
}

void autoConsommationDejourAvecBatterie() //Scénario 2 numéro 3
{
  digitalWrite(LED_PIN, HIGH);
  int reverseNum = 50;
  analogWrite(MOTOR_PIN, motorSpeed);
  for(int i = 0; i < 50; i++)
  {
    stripUsine.setBrightness(5);
    stripUsine.setPixelColor(reverseNum - 26, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.show(); 

    stripER.setPixelColor(reverseNum - 26, CYAN[0], CYAN[1], CYAN[2]);
    stripER.show(); 

    //eteins er
    if(i > 9)
    {
      stripER.setPixelColor(reverseNum - 16, 0,0, 0);
      stripER.show(); 
    }

    //eteinsUsine
    if(i > 2)
    {
      stripUsine.setPixelColor(reverseNum - 23, 0,0, 0);
      stripUsine.show(); 
    }

    //allume le mid
    if(i > 25 && i < 30)
    {
      stripBatterie.setPixelColor(i-26, CYAN[0], CYAN[1], CYAN[2]);
      stripBatterie.show();
    }

    //eteins le mid
    if(i > 27 && i < 31)
    {
      stripBatterie.setPixelColor(i - 28, 0, 0, 0);
      stripBatterie.show();
    }

    //batterie en vert
    if(i > 29)
    {
      stripBatterie.setPixelColor(i-26, GREEN[0], GREEN[1], GREEN[2]);
      stripBatterie.show();
    }

    //allumer maison
    if(i > 29)
    {
      stripMaison.setPixelColor(i-30, CYAN[0], CYAN[1], CYAN[2]);
      stripMaison.show();
    }
    
    //allumer voiture
    if(i > 29)
    {
      stripVoiture.setPixelColor(i-30, CYAN[0], CYAN[1], CYAN[2]);
      stripVoiture.show();
    }

    //eteins maison
    if(i > 39)
    {
      stripMaison.setPixelColor(i-40, 0, 0, 0);
      stripMaison.show();
    }

    //eteins voiture
    if(i > 39)
    {
      stripVoiture.setPixelColor(i-40, 0, 0, 0);
      stripVoiture.show();
    }

    ascenseur(i, 38);
    
    reverseNum--;
    delay(normalSpeed);
  }
  delay(normalSpeed);
  analogWrite(MOTOR_PIN, 0);
  digitalWrite(LED_PIN, LOW);
}

void autoConsommationDeNuitAvecBatterie() //Scénaro 2 numéro 4
{
  digitalWrite(LED_PIN, HIGH);
  batterieTopLedOn();
  int reverseNum = 48;
  for(int i = 0; i < 48; i++)
  {
    batterieTopLedOn();
    stripUsine.setBrightness(5);
    stripUsine.setPixelColor(reverseNum - 24, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.show(); 

    //eteinsUsine
    if(i > 2)
    {
      stripUsine.setPixelColor(reverseNum - 21, 0,0, 0);
      stripUsine.show(); 
    }

    //allume le mid
    if(i > 25 && i < 30)
    {
      //stripBatterie.setBrightness(5);
      stripBatterie.setPixelColor(i - 26, CYAN[0], CYAN[1], CYAN[2]);
      stripBatterie.show();
    }

    //eteins le mid
    if(i > 27 && i < 31)
    {
      stripBatterie.setPixelColor(i - 28, 0, 0, 0);
      stripBatterie.show();
    }

    //down batterie
    if(i > 16 && i < 29)
    {
      //stripBatterie.setBrightness(100);
      stripBatterie.setPixelColor(reverseNum - 17, CYAN[0], CYAN[1], CYAN[2]);
      stripBatterie.show();
    }

    //eteins batterie
    if(i > 26)
    {
      stripBatterie.setPixelColor(reverseNum - 7, 0, 0, 0);
      stripBatterie.show();
    }

    //allumer maison
    if(i > 28)
    {
      stripMaison.setPixelColor(i - 30, CYAN[0], CYAN[1], CYAN[2]);
      stripMaison.show();
    }

    //allumer voiture
    if(i > 28)
    {
      stripVoiture.setPixelColor(i - 30, CYAN[0], CYAN[1], CYAN[2]);
      stripVoiture.show();
    }

    //eteins maison
    if(i > 37)
    {
      stripMaison.setPixelColor(i - 39, 0, 0, 0);
      stripMaison.show();
    }

    //eteins voiture
    if(i > 37)
    {
      stripVoiture.setPixelColor(i - 39, 0, 0, 0);
      stripVoiture.show();
    }

    ascenseur(i, 36);
    batterieTopLedOn();
    reverseNum--;
    delay(normalSpeed);
  }

  delay(normalSpeed);
  digitalWrite(LED_PIN, LOW);
  batterieTopLedOff();
}

void autoConsommationDeNuitSansBatterie() //Scénario 2 numéro 5
{
  int reverseNum = 48;
  for(int i = 0; i < 48; i++)
  {
    stripUsine.setPixelColor(reverseNum - 24, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.show(); 

    //eteinsUsine
    if(i > 9)
    {
      stripUsine.setPixelColor(reverseNum - 14, 0,0, 0);
      stripUsine.show(); 
    }

    //allume le mid
    if(i > 25 && i < 30)
    {
      stripBatterie.setPixelColor(i - 26, CYAN[0], CYAN[1], CYAN[2]);
      stripBatterie.show();
    }

    //eteins le mid
    if(i > 34)
    {
      stripBatterie.setPixelColor(i-35, 0, 0, 0);
      stripBatterie.show();
    }

    //allumer maison
    if(i > 28)
    {
      stripMaison.setPixelColor(i - 30, CYAN[0], CYAN[1], CYAN[2]);
      stripMaison.show();
    }

    //allumer voiture
    if(i > 28)
    {
      stripVoiture.setPixelColor(i - 30, CYAN[0], CYAN[1], CYAN[2]);
      stripVoiture.show();
    }

    //eteins maison
    if(i > 37)
    {
      stripMaison.setPixelColor(i - 39, 0, 0, 0);
      stripMaison.show();
    }

    //eteins voiture
    if(i > 37)
    {
      stripVoiture.setPixelColor(i - 39, 0, 0, 0);
      stripVoiture.show();
    }

    ascenseur(i, 36);

    reverseNum--;
    delay(normalSpeed);
  }

  delay(normalSpeed);
}

void ilotAvecBatterie() //Scénario 3 numéro 6
{
  digitalWrite(LED_PIN, HIGH);
  analogWrite(MOTOR_PIN, motorSpeed);
  batterieTopLedOn();
  int reverseNum = 44;
  for(int i = 0; i < 44; i++)
  {
    batterieTopLedOn();
    //allume er avec lag
    if((i % 2) == 0)
    {
      stripER.setPixelColor(reverseNum - 26, CYAN[0], CYAN[1], CYAN[2]);
      stripER.show(); 
    }

    //eteins er
    if(i > 5)
    {
      stripER.setPixelColor(reverseNum - 15, 0,0, 0);
      stripER.show(); 
    }

    //allume le mid
    if(i > 21 && i < 26 && (i % 2) == 0)
    {
      stripBatterie.setPixelColor(i - 22, CYAN[0], CYAN[1], CYAN[2]);
      stripBatterie.show();
    }

    //eteins le mid
    if(i > 30 && i < 34)
    {
      stripBatterie.setPixelColor(i - 31, 0, 0, 0);
      stripBatterie.show();
    }

    //down batterie
    if(i > 12 && i < 25)
    {
      stripBatterie.setPixelColor(reverseNum - 17, CYAN[0], CYAN[1], CYAN[2]);
      stripBatterie.show();
    }

    //eteins batterie
    if(i > 24)
    {
      stripBatterie.setPixelColor(reverseNum - 5, 0, 0, 0);
      stripBatterie.show();
    }

    //allumer maison et voiture
    if(i > 24)
    {
      stripMaison.setPixelColor(i - 25, CYAN[0], CYAN[1], CYAN[2]);
      stripMaison.show();
      stripVoiture.setPixelColor(i - 25, CYAN[0], CYAN[1], CYAN[2]);
      stripVoiture.show();
    }

    //eteins maison
    if(i > 34)
    {
      stripMaison.setPixelColor(i - 35, 0, 0, 0);
      stripMaison.show();
      stripVoiture.setPixelColor(i - 35, 0, 0, 0);
      stripVoiture.show();
    }

    ascenseur(i, 33);
    batterieTopLedOn();
    reverseNum--;
    delay(normalSpeed);
  }

  delay(normalSpeed);
  digitalWrite(LED_PIN, LOW);
  analogWrite(MOTOR_PIN, 0);
  batterieTopLedOff();
}


void ilotSansBatterie() //Scénario 3 numéro 7
{
  int reverseNum = 44;
  analogWrite(MOTOR_PIN, motorSpeed);
  for(int i = 0; i < 44; i++)
  {
    //allume er avec lag
    if((i % 2) == 0)
    {
      stripER.setPixelColor(reverseNum - 26, CYAN[0], CYAN[1], CYAN[2]);
      stripER.show(); 
    }

    //eteins er
    if(i > 5)
    {
      stripER.setPixelColor(reverseNum - 15, 0,0, 0);
      stripER.show(); 
    }

    //allume le mid
    if(i > 21 && i < 26 && (i % 2) == 0)
    {
      stripBatterie.setPixelColor(i - 22, CYAN[0], CYAN[1], CYAN[2]);
      stripBatterie.show();
    }

    //eteins le mid
    if(i > 30 && i < 34)
    {
      stripBatterie.setPixelColor(i - 31, 0, 0, 0);
      stripBatterie.show();
    }
    
    //allumer maison et voiture
    if(i > 24 && (i % 2) == 0)
    {
      stripMaison.setPixelColor(i - 25, CYAN[0], CYAN[1], CYAN[2]);
      stripMaison.show();
      stripVoiture.setPixelColor(i - 25, CYAN[0], CYAN[1], CYAN[2]);
      stripVoiture.show();
    }

    //eteins maison
    if(i > 34)
    {
      stripMaison.setPixelColor(i - 35, 0, 0, 0);
      stripMaison.show();
      stripVoiture.setPixelColor(i - 35, 0, 0, 0);
      stripVoiture.show();
    }
    
    reverseNum--;
    delay(normalSpeed);
  }

  analogWrite(MOTOR_PIN, 0);
  delay(normalSpeed);
}

void timeShiftingHeuresCreusesAvecBatterie() //Scénario 4 numéro 8
{
  digitalWrite(LED_PIN, HIGH);
  int reverseNum = 50;
  for(int i = 0; i < 50; i++)
  {
    stripUsine.setPixelColor(reverseNum - 26, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.show(); 
    
    //eteinsUsine
    if(i > 9)
    {
      stripUsine.setPixelColor(reverseNum - 16, 0,0, 0);
      stripUsine.show(); 
    }

    //allume le mid
    if(i > 25)
    {
      stripBatterie.setPixelColor(i-26, CYAN[0], CYAN[1], CYAN[2]);
      stripBatterie.show();
    }

    //eteins le mid
    if(i > 34)
    {
      stripBatterie.setPixelColor(i-35, 0, 0, 0);
      stripBatterie.show();
    }

    //batterie en vert
    if(i > 29)
    {
      stripBatterie.setPixelColor(i-26, GREEN[0], GREEN[1], GREEN[2]);
      stripBatterie.show();
    }

    //allumer maison
    if(i > 29)
    {
      stripMaison.setPixelColor(i-30, CYAN[0], CYAN[1], CYAN[2]);
      stripMaison.show();
    }
    
    //allumer voiture
    if(i > 29)
    {
      stripVoiture.setPixelColor(i-30, CYAN[0], CYAN[1], CYAN[2]);
      stripVoiture.show();
    }

    //eteins maison
    if(i > 39)
    {
      stripMaison.setPixelColor(i-40, 0, 0, 0);
      stripMaison.show();
    }

    //eteins voiture
    if(i > 39)
    {
      stripVoiture.setPixelColor(i-40, 0, 0, 0);
      stripVoiture.show();
    }

    ascenseur(i, 38);
    
    reverseNum--;
    delay(normalSpeed);
  }

  delay(normalSpeed);
  digitalWrite(LED_PIN, LOW);
}

void timeShiftingHeuresCreusesSansBatterie() //Scénario 4 numéro 9
{
  int reverseNum = 49;
  for(int i = 0; i < 49; i++)
  {
    stripUsine.setPixelColor(reverseNum - 24, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.show(); 
    
    //eteinsUsine
    if(i > 9)
    {
      stripUsine.setPixelColor(reverseNum - 14, 0,0, 0);
      stripUsine.show(); 
    }

    //allume le mid
    if(i > 25 && i < 30)
    {
      stripBatterie.setPixelColor(i-26, CYAN[0], CYAN[1], CYAN[2]);
      stripBatterie.show();
    }

    //eteins le mid
    if(i > 34)
    {
      stripBatterie.setPixelColor(i-35, 0, 0, 0);
      stripBatterie.show();
    }

    //allumer maison
    if(i > 29)
    {
      stripMaison.setPixelColor(i-30, CYAN[0], CYAN[1], CYAN[2]);
      stripMaison.show();
      stripVoiture.setPixelColor(i-30, CYAN[0], CYAN[1], CYAN[2]);
      stripVoiture.show();
    }

    //eteins maison et voiture
    if(i > 39)
    {
      stripMaison.setPixelColor(i-40, 0, 0, 0);
      stripMaison.show();
      stripVoiture.setPixelColor(i-40, 0, 0, 0);
      stripVoiture.show();
    }
    ascenseur(i, 38);
    
    reverseNum--;
    delay(normalSpeed);
  }

  delay(normalSpeed);
}

void timeShiftingHeuresPleinesAvecBatterie() //Scénario 4 numéro 10
{
  digitalWrite(LED_PIN, HIGH);
  batterieTopLedOn();
  int reverseNum = 49;
  for(int i = 0; i < 48; i++)
  {
      batterieTopLedOn();
      stripUsine.setBrightness(5);
      stripUsine.setPixelColor(reverseNum - 25, CYAN[0], CYAN[1], CYAN[2]);
      stripUsine.show(); 

    //eteins le strip usine
      if(i > 1)
      {
        stripUsine.setPixelColor(reverseNum - 22, 0, 0, 0);
        stripUsine.show();
      }
  
  //allume le mid
  if(i > 24 && i < 29)
  {
    //stripBatterie.setBrightness(10);
    stripBatterie.setPixelColor(i - 25, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.show();
  }

 //eteins le mid
 if(i > 26 && i < 30)
 {
    stripBatterie.setPixelColor(i - 29, 0, 0, 0);
    stripBatterie.show();
 }
  
  //down la batterie en même temps que l'usine
  if(i > 15 && i < 27)
  {
    //stripBatterie.setBrightness(100);
    stripBatterie.setPixelColor(reverseNum - 19, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.show();
  }
    
  //eteins la batterie
  if(i > 29)
  {
    stripBatterie.setPixelColor(reverseNum - 5, 0, 0, 0);
    stripBatterie.show();
  }
    
  //illumine voiture et maison
  if(i > 29)
    {
      stripMaison.setPixelColor(i-30, CYAN[0], CYAN[1], CYAN[2]);
      stripMaison.show();
    
      stripVoiture.setPixelColor(i-30, CYAN[0], CYAN[1], CYAN[2]);
      stripVoiture.show();
    }
    
  //eteins voiture et maison
  if(i > 38)
    {
      stripMaison.setPixelColor(i-39, 0, 0, 0);
      stripMaison.show();

      stripVoiture.setPixelColor(i-39, 0, 0, 0);
      stripVoiture.show();
    }

  ascenseur(i, 37);
  batterieTopLedOn();
  reverseNum--;
  delay(normalSpeed);
  }
 delay(normalSpeed);
 batterieTopLedOff();
 digitalWrite(LED_PIN, LOW);
}

void timeShiftingHeuresPleinesSansBatterie() //Scénario 4 numéro 11
{
  int reverseNum = 49;
  for(int i = 0; i < 49; i++)
  {
    stripUsine.setPixelColor(reverseNum - 24, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.show(); 
    
    //eteinsUsine
    if(i > 9)
    {
      stripUsine.setPixelColor(reverseNum - 14, 0,0, 0);
      stripUsine.show(); 
    }

    //allume le mid
    if(i > 25 && i < 30)
    {
      stripBatterie.setPixelColor(i-26, CYAN[0], CYAN[1], CYAN[2]);
      stripBatterie.show();
    }

    //eteins le mid
    if(i > 34)
    {
      stripBatterie.setPixelColor(i-35, 0, 0, 0);
      stripBatterie.show();
    }

    //allumer maison
    if(i > 29)
    {
      stripMaison.setPixelColor(i-30, CYAN[0], CYAN[1], CYAN[2]);
      stripMaison.show();
      stripVoiture.setPixelColor(i-30, CYAN[0], CYAN[1], CYAN[2]);
      stripVoiture.show();
    }

    //eteins maison et voiture
    if(i > 39)
    {
      stripMaison.setPixelColor(i-40, 0, 0, 0);
      stripMaison.show();
      stripVoiture.setPixelColor(i-40, 0, 0, 0);
      stripVoiture.show();
    }

    ascenseur(i, 38);
    
    reverseNum--;
    delay(normalSpeed);
  }

  delay(normalSpeed);
}

void ascenseur(int i, int startValue)
{
    if(ascenseurLevel == 0)
    {
      ascenseurUp = true;

      if(ascenseurDown && ((i % 5) == 0))
      {
        stripAscenseur.setPixelColor(0, CYAN[0], CYAN[1], CYAN[2]);
        stripAscenseur.setPixelColor(1, 0, 0, 0);
        stripAscenseur.show(); 

        stripAscenseurBis.setPixelColor(0, CYAN[0], CYAN[1], CYAN[2]);
        stripAscenseurBis.setPixelColor(1, 0, 0, 0);
        stripAscenseurBis.show(); 
        
        ascenseurDown = false;
        offFirstFloor = true;
      }
      else if(offFirstFloor && ((i % 5) == 0))
      {
        stripAscenseur.setPixelColor(0, 0, 0, 0);
        stripAscenseur.show(); 

        stripAscenseurBis.setPixelColor(0, 0, 0, 0);
        stripAscenseurBis.show(); 
        
        offFirstFloor = false;
      }
    }
    else if(ascenseurLevel == 6)
    {
      ascenseurUp = false;
    }
    
    //up
    if(ascenseurUp && (i > startValue || ascenseurLevel > 0) && ((i % 5) == 0))
    {
      stripAscenseur.setPixelColor(ascenseurLevel + 1, 0, 0, 0);
      stripAscenseur.setPixelColor(ascenseurLevel, CYAN[0], CYAN[1], CYAN[2]);
      stripAscenseur.setPixelColor(ascenseurLevel - 1, 0, 0, 0);
      stripAscenseur.show(); 

      stripAscenseurBis.setPixelColor(ascenseurLevel + 1, 0, 0, 0);
      stripAscenseurBis.setPixelColor(ascenseurLevel, CYAN[0], CYAN[1], CYAN[2]);
      stripAscenseurBis.setPixelColor(ascenseurLevel - 1, 0, 0, 0);
      stripAscenseurBis.show(); 
      
      ascenseurLevel++;
    }
    
    //down
    if(!ascenseurUp && ((i % 5) == 0))
    {
      stripAscenseur.setPixelColor(ascenseurLevel - 1, 0, 0, 0);
      stripAscenseur.setPixelColor(ascenseurLevel, CYAN[0], CYAN[1], CYAN[2]);
      stripAscenseur.setPixelColor(ascenseurLevel + 1, 0, 0, 0);
      stripAscenseur.show();

      stripAscenseurBis.setPixelColor(ascenseurLevel - 1, 0, 0, 0);
      stripAscenseurBis.setPixelColor(ascenseurLevel, CYAN[0], CYAN[1], CYAN[2]);
      stripAscenseurBis.setPixelColor(ascenseurLevel + 1, 0, 0, 0);
      stripAscenseurBis.show();
      
      ascenseurLevel--;
      ascenseurDown = true;
    }
}

void offAscenseur()
{
  ascenseurLevel = 0; //last level = 6;
  ascenseurUp = true;
  ascenseurDown = false;
  offFirstFloor = false;
  
  for(int i = 0; i < 7; i++)
  {
    stripAscenseur.setPixelColor(i, 0, 0, 0);
    stripAscenseur.show();

    stripAscenseurBis.setPixelColor(i, 0, 0, 0);
    stripAscenseurBis.show();
  }
}

/*Misc*/

void chenillardUp(Adafruit_NeoPixel strip, int nbLed, int temps, int color[3])
{
  for(int i = 0; i < nbLed; i++)
  { 
    strip.setPixelColor(i, color[0], color[1], color[2]);
    strip.setPixelColor(i+1, color[0], color[1], color[2]);
    strip.setPixelColor(i+2, color[0], color[1], color[2]);
    strip.setPixelColor(i+3, color[0], color[1], color[2]);
    strip.setPixelColor(i+4, color[0], color[1], color[2]);
    strip.show();

    delay(temps);
    
    strip.setPixelColor(i, 0, 0, 0);
    strip.setPixelColor(i+1, 0, 0, 0);
    strip.setPixelColor(i+2, 0, 0, 0);
    strip.setPixelColor(i+3, 0, 0, 0);
    strip.setPixelColor(i+4, 0, 0, 0);
    strip.show();
  }
}

void batterieTopLedOff()
{
    stripBatterie.setPixelColor(11, 0, 0, 0);
    stripBatterie.setPixelColor(12, 0, 0, 0);
    stripBatterie.setPixelColor(13, 0, 0, 0);
    stripBatterie.setPixelColor(14, 0, 0, 0);
    stripBatterie.setPixelColor(15, 0, 0, 0);
    stripBatterie.show();
}

void batterieTopLedOn()
{
    stripBatterie.setPixelColor(11, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.setPixelColor(12, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.setPixelColor(13, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.setPixelColor(14, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.setPixelColor(15, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.show();
}

void chenillardDown(Adafruit_NeoPixel strip, int nbLed, int temps, int color[3])
{
  for(int i = nbLed; i > 0; i--)
  {
    strip.setPixelColor(i, color[0], color[1], color[2]);
    strip.setPixelColor(i-1, color[0], color[1], color[2]);
    strip.setPixelColor(i-2, color[0], color[1], color[2]);
    strip.setPixelColor(i-3, color[0], color[1], color[2]);
    strip.setPixelColor(i-4, color[0], color[1], color[2]);
    strip.show();
    
    strip.setPixelColor(i, 0, 0, 0);
    strip.setPixelColor(i-1, 0, 0, 0);
    strip.setPixelColor(i-2, 0, 0, 0);
    strip.setPixelColor(i-3, 0, 0, 0);
    strip.setPixelColor(i-4, 0, 0, 0);
    strip.show();
    
    delay(temps);  
  }
}

void allChenillard()
{
  //up
  for(int i = 0; i < 25; i++)
  {
    stripUsine.setPixelColor(i, 0, 255, 25);
    stripUsine.setPixelColor(i+1, 0, 255, 25);
    stripUsine.setPixelColor(i+2, 0, 255, 25);
    stripUsine.setPixelColor(i+3, 0, 255, 25);
    stripUsine.show();

    stripER.setPixelColor(i, 0, 255, 255);
    stripER.setPixelColor(i+1, 0, 255, 255);
    stripER.setPixelColor(i+2, 0, 255, 255);
    stripER.setPixelColor(i+3, 0, 255, 255);
    stripER.show();

    stripBatterie.setPixelColor(i, 0, 255, 255);
    stripBatterie.setPixelColor(i+1, 0, 255, 255);
    stripBatterie.setPixelColor(i+2, 0, 255, 255);
    stripBatterie.setPixelColor(i+3, 0, 255, 255);
    stripBatterie.show();

    stripMaison.setPixelColor(i, 0, 255, 255);
    stripMaison.setPixelColor(i+1, 0, 255, 255);
    stripMaison.setPixelColor(i+2, 0, 255, 255);
    stripMaison.setPixelColor(i+3, 0, 255, 255);
    stripMaison.show();

    stripVoiture.setPixelColor(i, 0, 255, 255);
    stripVoiture.setPixelColor(i+1, 0, 255, 255);
    stripVoiture.setPixelColor(i+2, 0, 255, 255);
    stripVoiture.setPixelColor(i+3, 0, 255, 255);
    stripVoiture.show();
    
    delay(50);

    stripUsine.setPixelColor(i, 0, 0, 0);
    stripUsine.setPixelColor(i+1, 0, 0, 0);
    stripUsine.setPixelColor(i+2, 0, 0, 0);
    stripUsine.setPixelColor(i+3, 0, 0, 0);
    stripUsine.show();

    stripER.setPixelColor(i, 0, 0, 0);
    stripER.setPixelColor(i+1, 0, 0, 0);
    stripER.setPixelColor(i+2, 0, 0, 0);
    stripER.setPixelColor(i+3, 0, 0, 0);
    stripER.show();

    stripBatterie.setPixelColor(i, 0, 0, 0);
    stripBatterie.setPixelColor(i+1, 0, 0, 0);
    stripBatterie.setPixelColor(i+2, 0, 0, 0);
    stripBatterie.setPixelColor(i+3, 0, 0, 0);
    stripBatterie.show();

    stripMaison.setPixelColor(i, 0, 0, 0);
    stripMaison.setPixelColor(i+1, 0, 0, 0);
    stripMaison.setPixelColor(i+2, 0, 0, 0);
    stripMaison.setPixelColor(i+3, 0, 0, 0);
    stripMaison.show();

    stripVoiture.setPixelColor(i, 0, 0, 0);
    stripVoiture.setPixelColor(i+1, 0, 0, 0);
    stripVoiture.setPixelColor(i+2, 0, 0, 0);
    stripVoiture.setPixelColor(i+3, 0, 0, 0);
    stripVoiture.show();
  }
}

void off()
{
  offAscenseur();
  analogWrite(MOTOR_PIN, 0);
  digitalWrite(LED_PIN, LOW);
  
  for(int i = 0; i < 25; i++)
  {
    stripUsine.setPixelColor(i, 0, 0, 0);
    stripUsine.show();

    stripER.setPixelColor(i, 0, 0, 0);
    stripER.show();

    stripBatterie.setPixelColor(i, 0, 0, 0);
    stripBatterie.show();

    stripMaison.setPixelColor(i, 0, 0, 0);
    stripMaison.show();

    stripVoiture.setPixelColor(i, 0, 0, 0);
    stripVoiture.show();

    stripAscenseur.setPixelColor(i, 0, 0, 0);
    stripAscenseur.show();

    stripAscenseurBis.setPixelColor(i, 0, 0, 0);
    stripAscenseurBis.show();
  }
}

void serialEvent() 
{
  while (Serial.available()) 
  {
    char inChar = (char)Serial.read();
    
    if (inChar == '0')
    {
      msg = tmpMessage;
      tmpMessage = "";
      off();
      //Serial.println(msg);
    }
    else
    {
      tmpMessage += inChar;
    }
  }
}
