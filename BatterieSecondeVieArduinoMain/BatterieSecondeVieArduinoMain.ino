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
#define ASCENSEUR_COUNT 10

#define LED_PIN 4

Adafruit_NeoPixel stripUsine = Adafruit_NeoPixel(MID_USINE_COUNT, MID_USINE_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripER = Adafruit_NeoPixel(MID_ER_COUNT, MID_ER_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripBatterie = Adafruit_NeoPixel(MID_BATTERIE_COUNT, MID_BATTERIE_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripMaison = Adafruit_NeoPixel(MID_MAION_COUNT, MID_MAISON_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripVoiture = Adafruit_NeoPixel(MID_VOITURE_COUNT, MID_VOITURE_PIN, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel stripAscenseur = Adafruit_NeoPixel(ASCENSEUR_COUNT, ASCENSEUR_PIN, NEO_GRB + NEO_KHZ800);


//Colors definition
int GREEN[3] = {0, 255, 25};
int CYAN[3] = {0, 255, 255};

//Speed definition
int normalSpeed = 50;
int ascenseurSpeed = 20;
int lagSpeed = 20;

String msg = "";
bool newStringComplete = false;
String tmpMessage;

void setup() 
{
  stripUsine.begin();
  stripER.begin();
  stripBatterie.begin();
  stripMaison.begin();
  stripVoiture.begin();
  //stripAscenseur.begin();
  
  stripUsine.show();
  stripER.show();
  stripBatterie.show();
  stripMaison.show();
  stripVoiture.show();
  //stripAscenseur.show();

  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() 
{
  stripUsine.setBrightness(100);
  stripER.setBrightness(100);
  stripBatterie.setBrightness(100);
  stripMaison.setBrightness(100);
  stripVoiture.setBrightness(100);

  if(msg.equals("peakShavingSansBatterie"))
  {
    peakShavingSansBatterie();
  }
  else if(msg.equals("peakShavingAvecBatterie"))
  {
    peakShavingAvecBatterie();
  }
  else if(msg.equals("autoConsommationDejourAvecBatterie"))
  {
    autoConsommationDejourAvecBatterie();
  }
  else if(msg.equals("autoConsommationDeNuitAvecBatterie"))
  {
    autoConsommationDeNuitAvecBatterie();
  }
  else if(msg.equals("autoConsommationDeNuitSansBatterie"))
  {
    autoConsommationDeNuitSansBatterie();
  }
  else if(msg.equals("ilotAvecBatterie"))
  {
    ilotAvecBatterie();
  }
  else if(msg.equals("ilotSansBatterie"))
  {
    ilotSansBatterie();
  }
  else if(msg.equals("timeShiftingHeuresCreusesAvecBatterie"))
  {
    timeShiftingHeuresCreusesAvecBatterie();
  }
  else if(msg.equals("timeShiftingHeuresCreusesSansBatterie"))
  {
    timeShiftingHeuresCreusesSansBatterie();
  }
  else if(msg.equals("timeShiftingHeuresPleinesAvecBatterie"))
  {
    timeShiftingHeuresPleinesAvecBatterie();
  }
  else if(msg.equals("peakShavingAvecBatterie"))
  {
    timeShiftingHeuresPleinesSansBatterie();
  }
}

void peakShavingSansBatterie() //Sénario 1 numéro 1
{
  //usine
  int reverseNum = 39;
  for(int i = 0; i < 49; i++)
  {
    stripUsine.setPixelColor(reverseNum - 14, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.show(); 

    stripUsine.setPixelColor(reverseNum, 0, 0, 0);
    stripUsine.show();

    if(i > 25 && i < 30)
    {
      stripBatterie.setPixelColor(i - 26, CYAN[0], CYAN[1], CYAN[2]);
      stripBatterie.show();
    }

    if(i > 34)
    {
      stripBatterie.setPixelColor(i - 35, 0, 0, 0);
      stripBatterie.show();
    }

    if(i > 29)
    {
      stripMaison.setPixelColor(i-30, CYAN[0], CYAN[1], CYAN[2]);
  	  stripMaison.show();
  	
  	  stripVoiture.setPixelColor(i-30, CYAN[0], CYAN[1], CYAN[2]);
      stripVoiture.show();
    }

    if(i > 38)
    {
      stripMaison.setPixelColor(i-39, 0, 0, 0);
      stripMaison.show();

      stripVoiture.setPixelColor(i-39, 0, 0, 0);
      stripVoiture.show();
    }
    
	delay(normalSpeed); 
	reverseNum--;
  }
  
  delay(normalSpeed);
}

void peakShavingAvecBatterie() //Scénario 1 numéro 2
{
  digitalWrite(LED_PIN, HIGH);
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
	if(i > 25 && i < 29)
	{
		//stripBatterie.setBrightness(10);
		stripBatterie.setPixelColor(i - 25, CYAN[0], CYAN[1], CYAN[2]);
		stripBatterie.show();
	}

 //eteins le mid
 if(i > 37)
 {
    stripBatterie.setPixelColor(i - 37, 0, 0, 0);
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

  reverseNum--;
  delay(normalSpeed);
	}
 digitalWrite(LED_PIN, LOW);
}

void autoConsommationDejourAvecBatterie() //Scénario 2 numéro 3
{
  //down ER
  downEREtUsineLent();

  delay(normalSpeed);

  //up midle batterie
  upMidleBattery();

  delay(normalSpeed);

  //up home, car and battery (in green)
  upHomeAndCarAndBatteryGreen();

  delay(normalSpeed);
}

void autoConsommationDeNuitAvecBatterie() //Scénaro 2 numéro 4
{
	downBatterieEtUsineLent();
	/*
  //battery almost down
  for(int i = 14; i > 4; i--)
  {
    stripBatterie.setPixelColor(i, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.setPixelColor(i-1, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.setPixelColor(i-2, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.setPixelColor(i-3, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.show();

    delay(normalSpeed);
    
    stripBatterie.setPixelColor(i, 0, 0, 0);
    stripBatterie.setPixelColor(i-1, 0, 0, 0);
    stripBatterie.setPixelColor(i-2, 0, 0, 0);
    stripBatterie.setPixelColor(i-3, 0, 0, 0);
    stripBatterie.show();
  }
  */

  delay(normalSpeed);

  //up home
  upHome();

  delay(normalSpeed);
}

void autoConsommationDeNuitSansBatterie() //Scénario 2 numéro 5
{
  //down usine
  downUsineAndMid();

  delay(normalSpeed);

  //up midle batterie
  upMidleBattery();

  delay(normalSpeed);

  //up home
  upHome();

  delay(normalSpeed);
}

void ilotAvecBatterie() //Scénario 3 numéro 6
{
	downBatterie();
	
	delay(normalSpeed);
	
	upHomeAndCar();
	
	delay(normalSpeed);
	
	downERLag();
	
	delay(normalSpeed);
}

void ilotSansBatterie() //Scénario 3 numéro 7
{
	//down ER with lag
	downERLag();
	
	delay(normalSpeed);
	
	//up to home and car with lag
	for(int i = 0; i < MID_MAION_COUNT; i++)
	{
		stripMaison.setPixelColor(i, CYAN[0], CYAN[1], CYAN[2]);
		stripMaison.setPixelColor(i+1, CYAN[0], CYAN[1], CYAN[2]);
		stripMaison.setPixelColor(i+2, CYAN[0], CYAN[1], CYAN[2]);
		stripMaison.setPixelColor(i+3, CYAN[0], CYAN[1], CYAN[2]);
		stripMaison.show();

		stripVoiture.setPixelColor(i, CYAN[0], CYAN[1], CYAN[2]);
		stripVoiture.setPixelColor(i+1, CYAN[0], CYAN[1], CYAN[2]);
		stripVoiture.setPixelColor(i+2, CYAN[0], CYAN[1], CYAN[2]);
		stripVoiture.setPixelColor(i+3, CYAN[0], CYAN[1], CYAN[2]);
		stripVoiture.show();

		delay(normalSpeed - lagSpeed);

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
		
		delay(lagSpeed);
	}
	
	delay(normalSpeed);
}

void timeShiftingHeuresCreusesAvecBatterie() //Scénario 4 numéro 8
{
	downUsineAndMid();
	
	delay(normalSpeed);
	
	upMidleBattery();
	
	delay(normalSpeed);
	
	//up home, car and battery (in green)
	upHomeAndCarAndBatteryGreen();
	
	delay(normalSpeed);
}

void timeShiftingHeuresCreusesSansBatterie() //Scénario 4 numéro 9
{
	downUsineAndMid();
	
	delay(normalSpeed);
	
	upMidleBattery();
	
	delay(normalSpeed);
	
	upHomeAndCar();
	
	delay(normalSpeed);
}

void timeShiftingHeuresPleinesAvecBatterie() //Scénario 4 numéro 10
{
	//downBatterie();
	downBatterieEtUsineLent();
	
	delay(normalSpeed);
	
	upHomeAndCar();
	
	delay(normalSpeed);
}

void timeShiftingHeuresPleinesSansBatterie() //Scénario 4 numéro 11
{
	downUsineAndMid();
	
	delay(normalSpeed);
	
	upMidleBattery();
	
	delay(normalSpeed);
	
	upHomeAndCar();
	
	delay(normalSpeed);
}

/*Control method*/

void downUsineAndMid()
{
  for(int i = MID_USINE_COUNT; i > 0; i--)
  {
    stripUsine.setPixelColor(i, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.setPixelColor(i+1, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.setPixelColor(i+2, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.setPixelColor(i+3, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.setPixelColor(i+4, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.setPixelColor(i+5, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.setPixelColor(i+6, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.setPixelColor(i+7, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.setPixelColor(i+8, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.show();

    delay(normalSpeed);  

    if(i != 1)
    {
      stripUsine.setPixelColor(i, 0, 0, 0);
      stripUsine.setPixelColor(i+1, 0, 0, 0);
      stripUsine.setPixelColor(i+2, 0, 0, 0);
      stripUsine.setPixelColor(i+3, 0, 0, 0);
      stripUsine.setPixelColor(i+4, 0, 0, 0);
      stripUsine.setPixelColor(i+5, 0, 0, 0);
      stripUsine.setPixelColor(i+6, 0, 0, 0);
      stripUsine.setPixelColor(i+7, 0, 0, 0);
      stripUsine.setPixelColor(i+8, 0, 0, 0);
      stripUsine.show();
    }
  }
  
  delay(normalSpeed);

  int j = 9;
  
  for(int i = 0; i < 3; i++)
  { 
	  stripUsine.setPixelColor(j, 0, 0, 0);
    stripUsine.show();
    stripBatterie.setPixelColor(i, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.setPixelColor(i-1, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.setPixelColor(i-2, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.show();

    delay(normalSpeed);
    
    stripBatterie.setPixelColor(i, 0, 0, 0);
    stripBatterie.setPixelColor(i-1, 0, 0, 0);
    stripBatterie.setPixelColor(i-2, 0, 0, 0);
    stripBatterie.show();

    j--;
  }
}

void downER()
{
  for(int i = MID_ER_COUNT; i > 0; i--)
  {
    stripER.setPixelColor(i, CYAN[0], CYAN[1], CYAN[2]);
    stripER.setPixelColor(i-1, CYAN[0], CYAN[1], CYAN[2]);
    stripER.setPixelColor(i-2, CYAN[0], CYAN[1], CYAN[2]);
    stripER.setPixelColor(i-3, CYAN[0], CYAN[1], CYAN[2]);
    stripER.show();

    delay(normalSpeed);  
    
    stripER.setPixelColor(i, 0, 0, 0);
    stripER.setPixelColor(i-1, 0, 0, 0);
    stripER.setPixelColor(i-2, 0, 0, 0);
    stripER.setPixelColor(i-3, 0, 0, 0);
    stripER.show();
  }
}

void upHome()
{
  for(int i = 0; i < MID_MAION_COUNT; i++)
  {
    stripMaison.setPixelColor(i, CYAN[0], CYAN[1], CYAN[2]);
    stripMaison.setPixelColor(i+1, CYAN[0], CYAN[1], CYAN[2]);
    stripMaison.setPixelColor(i+2, CYAN[0], CYAN[1], CYAN[2]);
    stripMaison.setPixelColor(i+3, CYAN[0], CYAN[1], CYAN[2]);
    stripMaison.show();

    delay(normalSpeed);

    stripMaison.setPixelColor(i, 0, 0, 0);
    stripMaison.setPixelColor(i+1, 0, 0, 0);
    stripMaison.setPixelColor(i+2, 0, 0, 0);
    stripMaison.setPixelColor(i+3, 0, 0, 0);
    stripMaison.show();
  }
}

void upMidleBattery()
{
  for(int i = 0; i < 3; i++)
  { 
    stripBatterie.setPixelColor(i, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.setPixelColor(i+1, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.setPixelColor(i+2, CYAN[0], CYAN[1], CYAN[2]);
    //stripBatterie.setPixelColor(i+3, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.show();

    delay(normalSpeed);
    
    stripBatterie.setPixelColor(i, 0, 0, 0);
    stripBatterie.setPixelColor(i+1, 0, 0, 0);
    stripBatterie.setPixelColor(i+2, 0, 0, 0);
    //stripBatterie.setPixelColor(i+3, 0, 0, 0);
    stripBatterie.show();
  }
}

void upHomeAndCar()
{
  for(int i = 0; i < MID_MAION_COUNT; i++)
  {
    stripMaison.setPixelColor(i, CYAN[0], CYAN[1], CYAN[2]);
    stripMaison.setPixelColor(i+1, CYAN[0], CYAN[1], CYAN[2]);
    stripMaison.setPixelColor(i+2, CYAN[0], CYAN[1], CYAN[2]);
    stripMaison.setPixelColor(i+3, CYAN[0], CYAN[1], CYAN[2]);
    stripMaison.show();

    stripVoiture.setPixelColor(i, CYAN[0], CYAN[1], CYAN[2]);
    stripVoiture.setPixelColor(i+1, CYAN[0], CYAN[1], CYAN[2]);
    stripVoiture.setPixelColor(i+2, CYAN[0], CYAN[1], CYAN[2]);
    stripVoiture.setPixelColor(i+3, CYAN[0], CYAN[1], CYAN[2]);
    stripVoiture.show();

    delay(normalSpeed);

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

void upHomeAndCarAndBatteryGreen()
{
	for(int i = 4; i < MID_BATTERIE_COUNT; i++)
  {
    stripMaison.setPixelColor(i-4, CYAN[0], CYAN[1], CYAN[2]);
    stripMaison.setPixelColor(i-3, CYAN[0], CYAN[1], CYAN[2]);
    stripMaison.setPixelColor(i-2, CYAN[0], CYAN[1], CYAN[2]);
    stripMaison.setPixelColor(i-1, CYAN[0], CYAN[1], CYAN[2]);
    stripMaison.show();

    stripVoiture.setPixelColor(i-4, CYAN[0], CYAN[1], CYAN[2]);
    stripVoiture.setPixelColor(i-3, CYAN[0], CYAN[1], CYAN[2]);
    stripVoiture.setPixelColor(i-2, CYAN[0], CYAN[1], CYAN[2]);
    stripVoiture.setPixelColor(i-1, CYAN[0], CYAN[1], CYAN[2]);
    stripVoiture.show();
    
    stripBatterie.setPixelColor(i, GREEN[0], GREEN[1], GREEN[2]);
    stripBatterie.setPixelColor(i+1, GREEN[0], GREEN[1], GREEN[2]);
    stripBatterie.setPixelColor(i+2, GREEN[0], GREEN[1], GREEN[2]);
    stripBatterie.setPixelColor(i+3, GREEN[0], GREEN[1], GREEN[2]);
    stripBatterie.show();

    delay(normalSpeed);

    stripMaison.setPixelColor(i-4, 0, 0, 0);
    stripMaison.setPixelColor(i-3, 0, 0, 0);
    stripMaison.setPixelColor(i-2, 0, 0, 0);
    stripMaison.setPixelColor(i-1, 0, 0, 0);
    stripMaison.show();

    stripVoiture.setPixelColor(i-4, 0, 0, 0);
    stripVoiture.setPixelColor(i-3, 0, 0, 0);
    stripVoiture.setPixelColor(i-2, 0, 0, 0);
    stripVoiture.setPixelColor(i-1, 0, 0, 0);
    stripVoiture.show();

    stripBatterie.setPixelColor(i, 0, 0, 0);
    stripBatterie.setPixelColor(i+1, 0, 0, 0);
    stripBatterie.setPixelColor(i+2, 0, 0, 0);
    stripBatterie.setPixelColor(i+3, 0, 0, 0);
    stripBatterie.show();
  }
}

void downBatterie()
{
	for(int i = 14; i > 4; i--)
  {
    stripBatterie.setPixelColor(i, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.setPixelColor(i-1, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.setPixelColor(i-2, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.setPixelColor(i-3, CYAN[0], CYAN[1], CYAN[2]);
    stripBatterie.show();

    delay(normalSpeed);
    
    stripBatterie.setPixelColor(i, 0, 0, 0);
    stripBatterie.setPixelColor(i-1, 0, 0, 0);
    stripBatterie.setPixelColor(i-2, 0, 0, 0);
    stripBatterie.setPixelColor(i-3, 0, 0, 0);
    stripBatterie.show();
  }
}

void downBatterieEtUsineLent()
{
	//for(int i = 14; i > 4; i--)
	for(int i = MID_USINE_COUNT; i > 0; i--)
  {
	  if(i > 4)
	  {
		stripBatterie.setPixelColor(i, CYAN[0], CYAN[1], CYAN[2]);
		stripBatterie.setPixelColor(i-1, CYAN[0], CYAN[1], CYAN[2]);
		stripBatterie.setPixelColor(i-2, CYAN[0], CYAN[1], CYAN[2]);
		stripBatterie.setPixelColor(i-3, CYAN[0], CYAN[1], CYAN[2]);
		stripBatterie.show();
	  }
    
	
	stripUsine.setBrightness(10);
	stripUsine.setPixelColor(i, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.setPixelColor(i-1, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.setPixelColor(i-2, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.setPixelColor(i-3, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.show();

    delay(normalSpeed);
    
    stripBatterie.setPixelColor(i, 0, 0, 0);
    stripBatterie.setPixelColor(i-1, 0, 0, 0);
    stripBatterie.setPixelColor(i-2, 0, 0, 0);
    stripBatterie.setPixelColor(i-3, 0, 0, 0);
    stripBatterie.show();
	
	stripUsine.setPixelColor(i, 0, 0, 0);
    stripUsine.setPixelColor(i-1, 0, 0, 0);
    stripUsine.setPixelColor(i-2, 0, 0, 0);
    stripUsine.setPixelColor(i-3, 0, 0, 0);
    stripUsine.show();
  }
}

void downERLag()
{
		for(int i = MID_ER_COUNT; i > 0; i--)
	{
		stripER.setPixelColor(i, CYAN[0], CYAN[1], CYAN[2]);
		stripER.setPixelColor(i-1, CYAN[0], CYAN[1], CYAN[2]);
		stripER.setPixelColor(i-2, CYAN[0], CYAN[1], CYAN[2]);
		stripER.setPixelColor(i-3, CYAN[0], CYAN[1], CYAN[2]);
		stripER.show();

		delay(normalSpeed - lagSpeed);  

		stripER.setPixelColor(i, 0, 0, 0);
		stripER.setPixelColor(i-1, 0, 0, 0);
		stripER.setPixelColor(i-2, 0, 0, 0);
		stripER.setPixelColor(i-3, 0, 0, 0);
		stripER.show();
		
		delay(lagSpeed);
	}
	
	delay(normalSpeed);
	
	//midle
	for(int i = 0; i < 3; i++)
	{ 
		stripBatterie.setPixelColor(i, CYAN[0], CYAN[1], CYAN[2]);
		stripBatterie.setPixelColor(i+1, CYAN[0], CYAN[1], CYAN[2]);
		stripBatterie.setPixelColor(i+2, CYAN[0], CYAN[1], CYAN[2]);
		//stripBatterie.setPixelColor(i+3, CYAN[0], CYAN[1], CYAN[2]);
		stripBatterie.show();

		delay(normalSpeed - lagSpeed);

		stripBatterie.setPixelColor(i, 0, 0, 0);
		stripBatterie.setPixelColor(i+1, 0, 0, 0);
		stripBatterie.setPixelColor(i+2, 0, 0, 0);
		//stripBatterie.setPixelColor(i+3, 0, 0, 0);
		stripBatterie.show();
		
		delay(lagSpeed);
	}
}

void downEREtUsineLent()
{
	for(int i = MID_USINE_COUNT; i > 0; i--)
  {
	stripUsine.setBrightness(5);
	  
    stripUsine.setPixelColor(i, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.setPixelColor(i-1, CYAN[0], CYAN[1], CYAN[2]);
    //stripUsine.setPixelColor(i-2, CYAN[0], CYAN[1], CYAN[2]);
    //stripUsine.setPixelColor(i-3, CYAN[0], CYAN[1], CYAN[2]);
    stripUsine.show();
	
	stripER.setPixelColor(i, CYAN[0], CYAN[1], CYAN[2]);
    stripER.setPixelColor(i-1, CYAN[0], CYAN[1], CYAN[2]);
    //stripER.setPixelColor(i-2, CYAN[0], CYAN[1], CYAN[2]);
    //stripER.setPixelColor(i-3, CYAN[0], CYAN[1], CYAN[2]);
    stripER.show();

    delay(normalSpeed);  
    
    stripUsine.setPixelColor(i, 0, 0, 0);
    stripUsine.setPixelColor(i-1, 0, 0, 0);
    stripUsine.setPixelColor(i-2, 0, 0, 0);
    stripUsine.setPixelColor(i-3, 0, 0, 0);
    stripUsine.show();
	
	stripER.setPixelColor(i, 0, 0, 0);
    stripER.setPixelColor(i-1, 0, 0, 0);
    stripER.setPixelColor(i-2, 0, 0, 0);
    stripER.setPixelColor(i-3, 0, 0, 0);
    stripER.show();
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

void serialEvent() 
{
  while (Serial.available()) 
  {
    char inChar = (char)Serial.read();
    
    if (inChar == '\n')
    {
      msg = tmpMessage;
      tmpMessage = "";
      //Serial.println(msg);
    }
    else
    {
      tmpMessage += inChar;
    }
  }
}

