int ledPin = 13;

void setup(){
pinMode(ledPin, OUTPUT);
Serial.begin(115200);
Serial.println("Starting");
}

void loop(){
digitalWrite(ledPin, HIGH);
delay(1000);
digitalWrite(ledPin, LOW);
delay(500);
Serial.println("Running");
}
