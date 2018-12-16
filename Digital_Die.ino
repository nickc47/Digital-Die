#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <Time.h>

#define OLED_ADDR 0x3C
#define CLICKTHRESHHOLD 40

Adafruit_SSD1306 display(-1);
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

const int buttonPin1 = 3; 
const int buttonPin3 = 1;
const int buttonPin4 = 4;

int messageCounter = 0;
int sleepTimer = 0;
int sleepCounter = 0;
int buttonState1 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int menuCounter = 1;
int diceCounter = 1;
int sidesCounter = 1;
int sceneCounter = 1;
int beetleCounter = 0;
int testCounter = 0;
int diceArray = 5;
int diePicker = 0;
int die[7] = {6,6,6,6,6};
int diceOnDice=1;
int checkers = analogRead(A0)+analogRead(A1)+analogRead(A2)+analogRead(A3)+analogRead(A4);
float chockers = checkers*3.14159;



void setup() 
{  
  lis.begin(0x18);
  lis.setRange(LIS3DH_RANGE_16_G);
  lis.setClick(1, CLICKTHRESHHOLD);
  delay(100);

  randomSeed(chockers);
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin1, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();
}

void loop() 
{
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState1 = digitalRead(buttonPin1);

  sleepMode();

  homeMenu();
  diceRoll();
  scrollRight();
  scrollLeft();
  
  diceMenu();
  macroDND();
  selectDice();
  selectDiceUp();
  selectDiceDown();
  
  sidesMenu();
  selectSides();
  selectSidesUp();
  selectSidesDown();
  pickSides();

  backToHome();
}

//This is the home menu display
void homeMenu()
{
  if(sceneCounter==1&&sleepCounter==0)
  {
    diceOnDice=1;
    display.setTextColor(WHITE);
    display.setTextSize(1);
    
    display.setCursor(0,0);
    
    //display.print(chockers); 
    
    
    display.setCursor(10,53);
    display.print("Roll");
    display.setCursor(54,53);
    display.print("New");
    display.setCursor(93,53);
    display.print("Poly");
    display.display();
  }
}

//draws 5 dice and fills random number 1-6
void diceRoll()
{
  if(buttonState1 == HIGH&&menuCounter==1&&sceneCounter==1)
  {
    clearScreen();
    display.setTextSize(4);
    display.setCursor(20,20);
    display.print("ROLL");
    display.display();
    delay(500);
    int test = 0;
    while(test==0)
    {
      uint8_t click = lis.getClick();
      if(click!=0)test++;
    } 
    
    display.setTextSize(1);
    clearScreen();

    int xH=20;
    int yH=34;
    int xC=18;
    int yC=31;
    for(int i=0;i<diceArray;i++)
    {
      delay(500);
      int dice = random(1,die[i]+1);
      drawHex(xH,yH);
      if(dice<10)  display.setCursor(xC,yC);
      if(dice>9&&dice<100)
      {
        xC=xC-3;
        display.setCursor(xC,yC);
      }
      if(dice>99)
      {
        xC=xC-6;
        display.setCursor(xC,yC);
      }
      display.print(dice);
      display.display();

      if(dice>9&&dice<100)xC=xC+3;
      if(dice>100)xC=xC+6;            
      if(i%2)
      {
        xH=xH+15;
        yH=yH+14;
        xC=xC+15;
        yC=yC+14;
      }
      else
      {
        xH=xH+15;
        yH=yH-14;
        xC=xC+15;
        yC=yC-14;        
      }
    }
  }
}
void macroDND()
{
  if(buttonState1 == HIGH&&menuCounter==3&&sceneCounter==1)
  {
    int echo=0;

    display.fillRect(0,0,128,64,BLACK);
    display.setTextSize(4);
    display.setCursor(20,20);
    display.print("ROLL");
    display.display();
    delay(500);
    
    while(echo==0)
    {
      uint8_t click = lis.getClick();
      if(click!=0)echo++;
    }   

    display.setTextSize(1);
    clearScreen();
    int xH=20;
    int yH=34;
    int xC=18;
    int yC=31;
    int j=5;
    int rN=0;
    for(int i=2;i<9;i++)
    {
      rN = random(1,j);
      delay(500);
      drawHex(xH,yH);
      if(rN<10)  display.setCursor(xC,yC);
      if(rN>9&&rN<100)
      {
        xC=xC-3;
        display.setCursor(xC,yC);
      }
      if(rN>99)
      {
        xC=xC-6;
        display.setCursor(xC,yC);
      }
      display.print(rN);
      display.display();

      if(rN>9&&rN<100)xC=xC+3;
      if(i==2)  j=j+2;
      if(i==3)  j=j+2;     
      if(i==4)  j=j+2;     
      if(i==5)  j=j+2;     
      if(i==6)  j=j+8;      
      if(i==7)  j=j+80;            
      if(i%2)
      {
        xH=xH+15;
        yH=yH+14;
        xC=xC+15;
        yC=yC+14;
      }
      else
      {
        xH=xH+15;
        yH=yH-14;
        xC=xC+15;
        yC=yC-14;        
      }
    }  
  }
}
//Scroll through menu RIGHT
void scrollRight()
{
  if(buttonState4 == HIGH&&sceneCounter==1)
  {
    menuCounter++;
    delay(50);
  }
  if(menuCounter==1&&sceneCounter==1)
  {
    display.drawRect(0,50,42,13,WHITE);
    display.drawRect(42,50,42,13,BLACK);
    display.drawRect(84,50,42,13,BLACK);
    display.display();
  }
  else if(menuCounter==2&&sceneCounter==1)
  {
    display.drawRect(0,50,42,13,BLACK);
    display.drawRect(42,50,42,13,WHITE);
    display.drawRect(84,50,42,13,BLACK);
    display.display();
  }
  else if(menuCounter==3&&sceneCounter==1)
  {
    display.drawRect(0,50,42,13,BLACK);
    display.drawRect(42,50,42,13,BLACK);
    display.drawRect(84,50,42,13,WHITE);
    display.display();
  }
  else if(menuCounter>3&&sceneCounter==1)menuCounter = 1;
}

//Scroll through menu LEFT
void scrollLeft()
{
  if(buttonState3 == HIGH&&sceneCounter==1)
  {
    menuCounter--;
    delay(50);
  }
  if(menuCounter==1&&sceneCounter==1)
  {
    display.drawRect(0,50,42,13,WHITE);
    display.drawRect(42,50,42,13,BLACK);
    display.drawRect(84,50,42,13,BLACK);
    display.display();
  }
  else if(menuCounter==2&&sceneCounter==1)
  {
    display.drawRect(0,50,42,13,BLACK);
    display.drawRect(42,50,42,13,WHITE);
    display.drawRect(84,50,42,13,BLACK);
    display.display();
  }
  else if(menuCounter==3&&sceneCounter==1)
  {
    display.drawRect(0,50,42,13,BLACK);
    display.drawRect(42,50,42,13,BLACK);
    display.drawRect(84,50,42,13,WHITE);
    display.display();
  }
  else if(menuCounter<1&&sceneCounter==1)menuCounter = 3;
}

void diceMenu()
{
  if(buttonState1==HIGH && menuCounter==2)
  {
    beetleCounter=0;
    menuCounter++;
    sceneCounter++;
    diceCounter=1;
    for(int i=0;i<7;i++)
    {
      die[0]=0;
    }
    clearScreen();
  }
}

void selectDice()
{
  if(sceneCounter==2)
  {
    display.setTextSize(1);
    display.setCursor(25,5);
    display.print("How many Dice?");
    display.fillTriangle(59,25,64,20,69,25,WHITE);
    display.fillTriangle(59,41,64,46,69,41,WHITE);
    display.setCursor(62,30);
    display.print(diceCounter);
    display.setCursor(47,53);
    display.print("Select");
    display.drawRect(40,50,50,13,WHITE);
    display.display();
  }
}

void selectDiceUp()
{
  if(buttonState4==HIGH&&sceneCounter==2&&diceCounter<7)
  {
    beetleCounter++;
    diceCounter++;
    delay(100);
    display.fillRect(50,26,50,14,BLACK);
    display.setCursor(62,30);
    display.print(diceCounter);
    display.display();
  }
  if(diceCounter>6&&sceneCounter==2)
  {
    diceCounter=7;
    display.setCursor(70,30);
    display.print("MAX");
    display.display();
  }
}

void selectDiceDown()
{
  if(buttonState3==HIGH&&sceneCounter==2&&diceCounter>1)
  {
    beetleCounter++;
    diceCounter--;
    delay(100);
    display.fillRect(50,26,50,14,BLACK);
    display.setCursor(62,30);
    display.print(diceCounter);
    display.display();
  }
  if(diceCounter<2&&sceneCounter==2)
  {
    diceCounter=1;
    display.setCursor(70,30);
    display.print("MIN");
    display.display();
  }
}

void sidesMenu()
{
  if(buttonState1==HIGH&&beetleCounter>0&&sceneCounter==2)
  {
    beetleCounter=0;
    diceArray = diceCounter;
    sceneCounter++;
    sidesCounter=1;
    clearScreen();
  }
}

void selectSides()
{
  if(sceneCounter==3)
  {
    display.setCursor(23,5);
    display.setTextSize(1);
    display.print("How many Sides?");
    display.fillTriangle(59,25,64,20,69,25,WHITE);
    display.fillTriangle(59,41,64,46,69,41,WHITE);
    display.setCursor(62,30);
    display.print(sidesCounter);
    display.setCursor(18,53);
    display.print("Select for die ");
    display.print(diceOnDice);
    display.drawRect(13,50,103,13,WHITE);
    diePicker=1;
  }
}

void selectSidesUp()
{
  if(buttonState4==HIGH&&sceneCounter==3&&sidesCounter<999)
  {
    sidesCounter++;
    delay(100);
    display.fillRect(50,26,50,14,BLACK);
    display.setCursor(62,30);
    display.print(sidesCounter);
    testCounter++;
    display.display();
  }
  if(sidesCounter>998&&sceneCounter==3)
  {
    sidesCounter=999;
    display.setCursor(80,30);
    display.print("MAX");
    display.display();
  }
}

void selectSidesDown()
{
  if(buttonState3==HIGH&&sceneCounter==3&&sidesCounter>1)
  {
    sidesCounter--;
    delay(100);
    display.fillRect(50,26,50,14,BLACK);
    display.setCursor(62,30);
    display.print(sidesCounter);
    testCounter++;
    display.display();
  }
  if(sidesCounter<2&&sceneCounter==3)
  {
    sidesCounter=1;
    display.setCursor(70,30);
    display.print("MIN");
    display.display();
  }
}

void pickSides()
{
  if(buttonState1==HIGH && sceneCounter==3 && diceOnDice<=diceArray && testCounter>0)
  {
    delay(500);
    if(diceOnDice==1)die[0]=sidesCounter;
    if(diceOnDice==2)die[1]=sidesCounter;
    if(diceOnDice==3)die[2]=sidesCounter;
    if(diceOnDice==4)die[3]=sidesCounter;
    if(diceOnDice==5)die[4]=sidesCounter;
    if(diceOnDice==6)die[5]=sidesCounter;
    if(diceOnDice==7)die[6]=sidesCounter;
    display.fillRect(50,26,50,14,BLACK);
    sidesCounter=1;
    diePicker++;
    if(diceOnDice<=diceArray)diceOnDice++;
    display.fillRect(101,51,15,10,BLACK);
    display.display();
    testCounter=0;
  }
  if(diceOnDice>diceArray&&sceneCounter==3)
  {
    sceneCounter = 1;
    menuCounter=1;
    clearScreen();
  }
}

void backToHome()
{
  if(buttonState3==HIGH&&buttonState4==HIGH)
  {
    sceneCounter = 1;
    menuCounter=1;
    clearScreen();
  }
}

void drawHex(int a, int b)
{
  int c = a-10;
  int d = a-5;
  int e = b-8.66;
  int f = a+5;
  int g = a+10;
  int h = b+8.66;
  
  display.drawLine(c,b,d,e,WHITE);
  display.drawLine(d,e,f,e,WHITE);
  display.drawLine(f,e,g,b,WHITE);
  display.drawLine(g,b,f,h,WHITE);
  display.drawLine(f,h,d,h,WHITE);
  display.drawLine(d,h,c,b,WHITE);
}

void sleepMode()
{ 
  if(buttonState1 == LOW&&buttonState3==LOW&&buttonState4==LOW&&sceneCounter==1)
  {
    sleepTimer++;
    if(sleepTimer>350)  //sleep mode set to 2 minutes
    {
      clearScreen();
      messageCounter++;
      if(messageCounter==1)
      {
        display.setCursor(1,32);
        display.setTextSize(2);
        display.print("SLEEP MODE");
        display.display();
        delay(5000);
      }
      sleepCounter++;
      menuCounter=0;
      clearScreen();
    }    
  }
  if(buttonState1 == HIGH||buttonState3==HIGH||buttonState4==HIGH)
  {
    sleepTimer=0;
    sleepCounter=0;
    messageCounter=0;
  }
}

void clearScreen()
{
  display.fillRect(0,0,128,64,BLACK);
  display.display();
}
