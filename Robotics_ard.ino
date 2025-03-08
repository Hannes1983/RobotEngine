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
String digOn1 = "dig1On\n";
String digOn2 = "dig2On\n";
String digOn3 = "dig3On\n";
String digOn4 = "dig4On\n";
String digOff1 = "dig1Off\n";
String digOff2 = "dig2Off\n";
String digOff3 = "dig3Off\n";
String digOff4 = "dig4Off\n";

String read5 = "read5";
String read6 = "read6";
String read7 = "read7";
String read8 = "read8";


void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(1000);
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);

  pinMode(13,OUTPUT);

//
//  digitalWrite(13, HIGH);
//  delay(5000);
//  digitalWrite(13, LOW);
}

void loop() {
  digitalWrite(13,HIGH);
  bool string_accepted = false;
  if (stringComplete) {
    if (inputString == digOn1) {
      digitalWrite(1,HIGH);
      string_accepted = true;
    }
    if (inputString == digOff1) {
      digitalWrite(1,LOW);
       string_accepted = true;
    }
    if (inputString == digOn2) {
      digitalWrite(2,HIGH);
      string_accepted = true;
    }
    if (inputString == digOff2) {
      digitalWrite(2,LOW);
      string_accepted = true;
    }
    if (inputString == digOn3) {
      digitalWrite(3,HIGH);
      string_accepted = true;
    }
    if (inputString == digOff3) {
      digitalWrite(3,LOW);
      string_accepted = true;
    }
    if (inputString == digOn4) {
      digitalWrite(4,HIGH);
      string_accepted = true;
    }
    if (inputString == digOff4) {
      digitalWrite(4,LOW);
      string_accepted = true;
    }
    
    if (inputString == read5) {
       if (digitalRead(5) == HIGH) {
          Serial.println("1");
       }
       else {
          Serial.println("0");
       }
       string_accepted = true;
    }
    if (inputString == read6) {
       if (digitalRead(6) == HIGH) {
          Serial.println("1");
       }
       else {
          Serial.println("0");
       }
       string_accepted = true;
    }
    if (inputString == read7) {
       if (digitalRead(7) == HIGH) {
          Serial.println("1");
       }
       else {
          Serial.println("0");
       }
       string_accepted = true;
    }
    if (inputString == read8) {
       if (digitalRead(8) == HIGH) {
          Serial.println("1");
       }
       else {
          Serial.println("0");
       }
       string_accepted = true;
    }

    // clear the string:
    inputString = "";
    stringComplete = false;
    if (string_accepted) {
      Serial.println("OK");
    }
    else {
      Serial.println("SK");
    }
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
