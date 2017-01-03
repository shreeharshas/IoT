const int photoSensor = 0;                                      //Pin A0 - photo resistor input
const int softPotSensor = 1;                                    //Pin A1 - soft potentiometer input
const int LED = 9;                                              //Pin 9  - led output
const int buzzerPin = 10;                                       //Pin 10 - piezo buzzer
const int lightThreshold = 75, pressThreshold = 5;              //Minimum thresholds for inputs
int pressValue, lightValue;                                     //Inputs read into these values

void setup()
{
  Serial.begin(9600);                                           //set serial device
  pinMode(LED, OUTPUT);                                         //set outputs
  pinMode(buzzerPin, OUTPUT);
}

void loop()
{
  lightValue = analogRead(photoSensor);                         //Sense input light through photo resistor
  lightValue = map(lightValue, 0, 1023, 0, 255);                //mapping and constraining to avoid flickering in LED                
  lightValue = constrain(lightValue, 0, 255);  
  
  Serial.print("lightValue:");Serial.print(lightValue);
  pressValue = analogRead(softPotSensor);                       //Sense input press through soft potentiometer
  Serial.print(" pressValue:");Serial.print(pressValue);        //Debug to serial monitor
  Serial.print("\n");  
  
  if(pressValue > pressThreshold){                              //if soft pot is pressed
    if(lightValue < lightThreshold){                            //if there is no light
      analogWrite(LED, 255);                                    //turn on led
    }
    else{                                                       //if there is light
      analogWrite(LED, 0);                                      //turn off led
    }  
    tone(buzzerPin, 777, 5);                                   //switch on buzzer
  }
  else{                                                         //if soft pot is not pressed
      analogWrite(LED, 0);                                      //switch off led
  }
}
