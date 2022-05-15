/*MANUAL MODE: This program is meant to control a light sytem by manual mode.
 * We use the same schematic for all the programs.
 * We control the CO. 

 */



 
/*Include library*/ 
#include <LiquidCrystal.h> //Include LCD library

/*Assign the variable*/ 
int PV; //Storable value which will be the LDR value
int CO; //Control Output Control
int ScreenNumber; //Storable value which will be the screen value

/*INPUT/Button settings*/ 
const int PushB1 = 8;   //Set the pin 8 for push button 1
const int PushB2 = 9;   //Set the pin 9 for push button 2
const int PushB3 = 13;  //Set the pin 13 for push button 3

int LastState1;         //Set a memory for the push button 1 code
int LastState2;         //Set a memory for the push button 2 code
int LastState3;         //Set a memory for the push button 3 code

int CurrentState1;      //Set a memory for the push button 1 code
int CurrentState2;      //Set a memory for the push button 2 code
int CurrentState3;      //Set a memory for the push button 3 code

/*OUTPUT settings*/ 
int LED = 10;   //Set the LED output pin to 10
int LDR = A0;   //Set the LDR analog input to A0

/*LCD settings*/ 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16,2);
pinMode(PushB1, INPUT_PULLUP); //Assign Push 1 to an input
pinMode(PushB2, INPUT_PULLUP); //Assign Push 2 to an input
pinMode(PushB3, INPUT_PULLUP); //Assign Push 3 to an input
pinMode(LED, OUTPUT);          //Assign LED to an output
}

void loop() {
  // put your main code here, to run repeatedly:



PV = analogRead(LDR); //Read the value sensed by the LDR and store it into PV
analogWrite(LED, CO); //Write the Control Output into the LED

/*CAP*/
// Cap are done to block the value going over 255 and under 0
if (CO>255){ 
  CO = 255;
  
}
if (CO<0){
   CO = 0;
}


/*PUSH BUTTON UP SETTINGS*/ 
// If the push button 1 is trigger, the CO will appear on the screen and we can control it by adding 25.
LastState1 = CurrentState1;
CurrentState1 = digitalRead(PushB1);
 if (LastState1 == 1 && CurrentState1 == 0){
   if(ScreenNumber == 1){
    CO = CO + 25;
   }
   
 }

/*PUSH BUTTON DOWN SETTINGS*/ 
// If the push button 2 is trigger, the CO will appear on the screen and we can control it  by removing 25.
LastState2 = CurrentState2;
CurrentState2 = digitalRead(PushB2);
 if (LastState2 == 1 && CurrentState2 == 0){
   if(ScreenNumber == 1){
    CO = CO - 25;
   }
   
 }
 

/*PUSH BUTTON CHANGE PAGE SETTINGS*/ 
 //When the push button 3 is trigger, the screen will change
LastState3 = CurrentState3;
CurrentState3 = digitalRead(PushB3);
 if (LastState3 == 1 && CurrentState3 == 0){
  ScreenNumber = ScreenNumber + 1;
  if(ScreenNumber > 1){
    ScreenNumber = 0;
  }
 }

  switch(ScreenNumber){
    case 0: //The first screen is to show the PV
  lcd.setCursor(0, 1);
  lcd.print("PV = ");
  lcd.print(PV);
  lcd.print(" ");
    break;
    case 1: //The scond screen is to show the CO and control it pu and down
    lcd.setCursor(0, 1);
  lcd.print("CO = ");
  lcd.print(CO);
  lcd.print("    ");
  default:
  break;
  }

}
