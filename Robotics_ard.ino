/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.

  A good test for this is to try it with a GPS receiver that sends out
  NMEA 0183 sentences.

  NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or
  other ATmega32U4 based boards.

  created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/SerialEvent
*/

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
//Errorcodes
// bit 7 : pin index out of range
// bit 6 : value out of range

//Return values
// bit 1: request process done
// bit 0: pin state

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(1000);
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);

  pinMode(13,OUTPUT);

}

void loop() {
  digitalWrite(13,HIGH);
  const String noError ="00000000";
  if (stringComplete) {
    bool stringAccepted = true;
    uint8_t pin = static_cast<uint8_t>(inputString[0] - '0');
    bool write = (inputString[1] == '1');
    String retStr = noError;
    if (pin < 0 || pin > 13) {
      retStr[0] = '1';

    }
    if (inputString[2] != '0' && inputString[2] != '1') {
      retStr[1] = '1';
    }
    if (retStr != noError) {
      inputString = "";
      stringComplete = false;
      stringAccepted = false;
    }
    if (write && stringAccepted) {
      if (inputString[2] == '1') {
        digitalWrite(pin,HIGH);
      }
      else {
        digitalWrite(pin,LOW);
      }
      retStr[6] = '1';
      retStr[7] = inputString[2];
    }
    else if (stringAccepted) {
      retStr[7] = digitalRead(pin) == HIGH ? '1' : '0';
      retStr[6] = '1';
    }
    Serial.println(retStr);
    inputString = "";
    stringComplete = false;
   
  }


  delay(500);
}


/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
//    digitalWrite(12, HIGH);
//    delay(500);
//    digitalWrite(12, LOW);
  }
}





/*const int LEDPin = 2;
void setup() {
  pinMode(LEDPin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
   int data = Serial.read();
   if (true) {
    digitalWrite(LEDPin, HIGH);
   }
   else {
    digitalWrite(LEDPin, LOW);
   }

  //digitalWrite(LEDPin,HIGH);
  //delay(1000);
  //digitalWrite(LEDPin,LOW);
  //delay(1000);
}*/
