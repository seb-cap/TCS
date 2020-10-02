#include <SoftwareSerial.h>

class Axis {
  public:

  Axis(int PositivePin, int NegativePin) {
    _posPin = PositivePin;
    _negPin = NegativePin;
    _lastCommandTime = 0;
    _state = 0;

    pinMode(_posPin, OUTPUT);
    pinMode(_negPin, OUTPUT);
  }

  boolean MovePositive() {
    if (_state != 'N') {
      digitalWrite(_posPin, LOW);
      _state = 'P';
      _lastCommandTime = millis();
      return true; //returns true if it moved positively
    }
    return false; //return false if it did not move positively
  }

  boolean MoveNegative() {
    if (_state != 'P') {
      digitalWrite(_negPin, LOW);
      _state = 'N';
      _lastCommandTime = millis();
      return true; //return true if it moved negatively
    }
    return false; //return false if it did not move negatively
  }

  void Stop() {
    if (millis() - _lastCommandTime > 200) {
      digitalWrite(_posPin, HIGH);
      digitalWrite(_negPin, HIGH);
      _state = 0;
    }
  }
  private:
    char _state;
    double _posPin;
    double _negPin;
    unsigned long _lastCommandTime;
};

Axis N_S_Axis(2,3);
Axis E_W_Axis(4,5);

const int NorthPin = 9;
const int SouthPin = 10;
const int EastPin = 11;
const int WestPin = 12;

void setup() {  
  // make the pushbutton's pin an input:
  pinMode(NorthPin, INPUT_PULLUP);//North
  pinMode(SouthPin, INPUT_PULLUP);//South
  pinMode(EastPin, INPUT_PULLUP);//East
  pinMode(WestPin, INPUT_PULLUP);//West
  Serial.begin(9600);
  Serial.println("Paddle Sender is ready!");}

void loop() {
  // read the sensor:
  
  if (digitalRead(NorthPin)==0)
  {
        if(N_S_Axis.MovePositive()){
        Serial.print("N");}
  }else { 
    N_S_Axis.Stop();
  }
  
  if (digitalRead(SouthPin)==0)
  {
        if(N_S_Axis.MoveNegative()){
        Serial.print("S");}
  }else { 
    N_S_Axis.Stop();
  }
  
  if (digitalRead(EastPin)==0)
  {
        if(E_W_Axis.MovePositive()){
        Serial.print("E");}
  }else { 
    E_W_Axis.Stop();
  }
  
  if (digitalRead(WestPin)==0)
  {
        if(E_W_Axis.MoveNegative()){
        Serial.print("W");}
  }  else { 
    E_W_Axis.Stop();
  }
    
// turn all the LEDs off:
//    for (int thisPin = 8; thisPin < 12; thisPin++) {
//      digitalWrite(thisPin, LOW);
//    }

}

