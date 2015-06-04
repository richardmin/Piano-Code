#include "sounds.h"
//Port Inputs
#define Key1  16
#define Key2  17
#define Key3  18
#define Key4  19
#define Key5  20
#define Key6  21
#define Key7  22
#define Key8  23

#define Key1Base 55
#define Key2Base 55
#define Key3Base 55
#define Key4Base 55
#define Key5Base 55 
#define Key6Base 60
#define Key7Base 55
#define Key8Base 55

#define Key1Low 25
#define Key2Low 35
#define Key3Low 33
#define Key4Low 30
#define Key5Low 38
#define Key6Low 40
#define Key7Low 30
#define Key8Low 25


int currentNote = -1;
int KeyPressed[] = {-1, -1, -1, -1,
                    -1, -1, -1, -1};
int arrayFilled = 0;

//Powers the Port Inputs
#define Power 4

//Speaker Port Number
#define AudioDriver 5



void setup()
{
  
  Serial.begin(9600);
  
  //setup Key's to receive input
  pinMode(Key1, INPUT);
  pinMode(Key2, INPUT);
  pinMode(Key3, INPUT);
  pinMode(Key4, INPUT);
  pinMode(Key5, INPUT);
  pinMode(Key6, INPUT);
  pinMode(Key7, INPUT);
  pinMode(Key8, INPUT);
  
  //set drivers
  pinMode(Power, OUTPUT);
  
              
  digitalWrite(Power, HIGH);

}

void printReads()
{
  
  Serial.print("1: ");
  Serial.print(analogRead(Key1));
  Serial.print(" 2: ");
  Serial.print(analogRead(Key2));
  Serial.print(" 3: ");
  Serial.print(analogRead(Key3));
  Serial.print(" 4: ");
  Serial.print(analogRead(Key4));
  Serial.print(" 5: ");
  Serial.print(analogRead(Key5));
  Serial.print(" 6: ");
  Serial.print(analogRead(Key6));
  Serial.print(" 7: ");
  Serial.print(analogRead(Key7));
  Serial.print(" 8: ");
  Serial.println(analogRead(Key8));
}

void printArrayValues()
{
  for(int i = 0; i < 8; i++)
  {
    Serial.print(i);
    Serial.print(": ");
    Serial.print(KeyPressed[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
}


void loop()
{
  delay(50);
  printReads();
  if (analogRead(Key1) < Key1Low)
  {
    addToArray(Key1);
  }
  if(analogRead(Key2) < Key2Low)
  {
    addToArray(Key2);
  }
  if (analogRead(Key3) < Key3Low)
  {
    addToArray(Key3);
  }
  if(analogRead(Key4) < Key4Low)
  {
        addToArray(Key4);
  }
  if (analogRead(Key5) < Key5Low)
  {
//        addToArray(Key5);
  }
  if(analogRead(Key6) < Key6Low)
  {
        addToArray(Key6);
  }
  if (analogRead(Key7) < Key7Low)
  {
        addToArray(Key7);
  }
  if(analogRead(Key8) < Key8Low)
  {
        addToArray(Key8);
  }
  if(analogRead(Key1) > Key1Base)
  {
    removeFromArray(Key1);
  }
  if(analogRead(Key2) > Key2Base)
  {
        removeFromArray(Key2);
  }
  if(analogRead(Key3) > Key3Base)
  {
        removeFromArray(Key3);
  }
  if(analogRead(Key4) > Key4Base)
  {
        removeFromArray(Key4);
  }
  if(analogRead(Key5) > Key5Base)
  {
        removeFromArray(Key5);
  }
  if(analogRead(Key6) > Key6Base)
  {
        removeFromArray(Key6);
  }
  if(analogRead(Key7) > Key7Base)
  {
        removeFromArray(Key7);
  }
  if(analogRead(Key8) > Key8Base)
  {
        removeFromArray(Key8);
  }
  
  playHighestNote();


}

void playHighestNote()
{
  if(KeyPressed[0] != currentNote)
  {
    Serial.print("Current Note Changed to: ");
    Serial.println(KeyPressed[0]);
    currentNote = KeyPressed[0];
    if(currentNote == -1)
    {
      UnpressKey();
    }
    else
    {
      Serial.print("Attempting to Play: ");
      Serial.println(getFrequency(currentNote));
      setCurrentSound(currentNote);
    }
  }
  
}

void addToArray(int keyNum)
{
   if(arrayFilled == 8)
   {
     return;
   }
   for(int i = 0; i < 8; i++)
   {
     if(KeyPressed[i] == keyNum)
     {
       return;
     }
   }
   
   for(int i = 6; i >= 0; i--)
   {
     KeyPressed[i+1] = KeyPressed[i];
   }
   Serial.print(keyNum);
   Serial.println(" was pressed!");
   KeyPressed[0] = keyNum;
  printArrayValues();
   arrayFilled++;
   
}

void removeFromArray(int keyNum)
{
  if(arrayFilled <= 0)
    return;
        
   int index = 9;
   
   for(int i = 0; i < 7; i++)
     if(KeyPressed[i] == keyNum)
       index = i;
   
   if(index == 9)
      return;
      
      
   for(; index < 7; index++)
     KeyPressed[index] = KeyPressed[index+1];
  
   KeyPressed[7] = -1;
   arrayFilled--;
}

int getFrequency(int note)
{
  Serial.print("note val: ");
  Serial.println(note);
  switch(note)
  {
    case Key1:
      return NOTE_C4;
    case Key2:
      return NOTE_D4;
    case Key3:
      return NOTE_E4;
    case Key4:
      return NOTE_F4;
    case Key5:
      return NOTE_G4;
    case Key6:
      return NOTE_A4;
    case Key7:
      return NOTE_B4;
    case Key8:
      return NOTE_C5;
  }
  return 0;
}

void setCurrentSound(int note)
{
  tone(AudioDriver, getFrequency(note));
}



void UnpressKey ()
{ 
  noTone(AudioDriver);
}

