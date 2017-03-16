//We always have to include the library
#include "LedControlMS.h"

//declaració de variables
int estat_actual[8][8];
int nou_estat[8][8];
int sx=8;
int sy=8;
float densitat=1;
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,1);

/* we always wait a bit between updates of the display */

unsigned long delaytime=0;

void setup() {


  Serial.begin(9600);
  randomSeed(analogRead(0));
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);

// Generació d'una matriu amb tres leds alineats
  for (int c=0;c<8;c++){
      for(int f=0;f<8;f++){
    estat_actual[c][f]=0;
    }
  }
 estat_actual[4][2]=1;
 estat_actual[4][3]=1;
 estat_actual[4][4]=1;
 estat_actual[3][3]=1;
 estat_actual[3][5]=1;
 estat_actual[5][5]=1;


/* Generació d'una matriu inicial aleatoria de densitat variable*/

/*for (int i = 0; i < sx * sy * densitat; i++) { 

   estat_actual[(int)random(sx)][(int)random(sy)] = 1; 

  }
 */  
    for (int c=0;c<8;c++){
      for(int f=0;f<8;f++){
  //Serial.print("estat actual");
  //Serial.print(c);
  //Serial.print(f);
  //Serial.print(estat_actual[c][f]);
  //Serial.println("\t");
    }
  }
for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
      //delay(delaytime);
      lc.setLed(0,row,col,estat_actual[row][col]);
      delay(delaytime);
      /*
      for(int i=0;i<col;i++) {
        lc.setLed(0,row,col,false);
        delay(delaytime);
        lc.setLed(0,row,col,estat_actual[row][col]);
        delay(delaytime); 
      }*/
    }
  }
}








void single() {
  for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
      delay(delaytime);
      lc.setLed(0,row,col,nou_estat[row][col]);
      delay(delaytime);
      /*
      for(int i=0;i<col;i++) {
        lc.setLed(0,row,col,false);
        delay(delaytime);
        lc.setLed(0,row,col,estat_actual[row][col]);
        delay(delaytime); 
      }*/
    }
  }
}

void loop() { 
 
    
  
  
  int veins [8][8];
 
 
 for(int x=0;x<8;x++){
  for(int y=0;y<8;y++){
    
 veins[x][y]=estat_actual[(x + 1) % sx][y] +  estat_actual[x][(y + 1) % sy] + 

         estat_actual[(x + sx - 1) % sx][y] + estat_actual[x][(y + sy - 1) % sy] + 

         estat_actual[(x + 1) % sx][(y + 1) % sy] + estat_actual[(x + sx - 1) % sx][(y + 1) % sy] + 

         estat_actual[(x + sx - 1) % sx][(y + sy - 1) % sy] + 

         estat_actual[(x + 1) % sx][(y + sy - 1) % sy]; 
//Serial.print("veins");
//Serial.print(x);
//Serial.print(y);
//Serial.print(veins[x][y]);
//Serial.println("\t");
Serial.print("veins:  ");
Serial.println(veins[2][3]);
Serial.print("estat:  ");
Serial.println(estat_actual[2][3]);

  delay(delaytime);
  }
 }
 

  
 /*Generar nou estat*/
 
  for(int x=0;x<8;x++){
  for(int y=0;y<8;y++){
    if(estat_actual[x][y]==0 && veins[x][y]==3){
      nou_estat[x][y]=1;}

    if(estat_actual[x][y]==1 && (veins<2 ||veins>3)){
        nou_estat[x][y]=0;}

    if(estat_actual[x][y]==1 && veins[x][y]==2){
      nou_estat[x][y]=1;}

    if(estat_actual[x][y]==1 && veins[x][y]==3){
      nou_estat[x][y]=1;}
      }
    }
    
  single();
  //renovació matriu
 
 for(int x=0;x<8;x++){
  for(int y=0;y<8;y++){
    estat_actual[x][y]=nou_estat[x][y];
      }
      }
}
