
const int LEDPin = 2;
void setup() {
  pinMode(LEDPin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
   int data = Serial.read();
   if (data == 'A') {
    digitalWrite(LEDPin, HIGH);
   }
   else {
    digitalWrite(LEDPin, LOW);
   }

  //digitalWrite(LEDPin,HIGH);
  //delay(1000);
  //digitalWrite(LEDPin,LOW);
  //delay(1000);
}
