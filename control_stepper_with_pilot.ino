#include <IRremote.h>

#define Step 7 
#define Dir 6 
#define irPin 5

int engineRotationSpeed = 5;   // Speed of the rotation (smaller means faster rotation)
int engineRotationDirection= 0 ;  // Rotation direction (0 or 1)

IRrecv irrecv(irPin);
decode_results results;

bool isActive = false;

void runEngine()
{
  if(isActive==true)
  {
    digitalWrite(Dir,engineRotationDirection);
    digitalWrite(Step,LOW);
    digitalWrite(Step,HIGH);
    delay(engineRotationSpeed);
    digitalWrite(Step,LOW );
    delay(engineRotationSpeed);
  }
  else
  {
    digitalWrite(Step,LOW );
  }
}

void setup()
{
  pinMode(Step,OUTPUT);
  pinMode(Dir,OUTPUT);

  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop()
{
    if (irrecv.decode(&results)) 
    {
     /*
      Serial.print("0x");
      Serial.println(results.value, HEX);
      delay(250);
     */ 
      switch(results.value)
      {
        case 0xFF30CF:
          if(isActive==true)
            isActive = false;
          else
            isActive = true;
          break;

        case 0xFFA857:
          if(engineRotationSpeed >=2)
            engineRotationSpeed--;
          break;

        case 0xFFE01F:
          if(engineRotationSpeed <=9)
            engineRotationSpeed++;
          break;

        case 0xFF906F:
          if(engineRotationDirection == 0) engineRotationDirection = 1;
          else engineRotationDirection = 0;   
      }     
      irrecv.resume(); // it's taking next value of ir signal
    }   
    runEngine();
}
