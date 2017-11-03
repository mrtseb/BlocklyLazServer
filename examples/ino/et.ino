int in1;
int in2;

void setup() {
  pinMode(A0, INPUT);
  pinMode(A3, INPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  in1 = (int)(digitalRead(A0));
  in2 = (int)(digitalRead(A3));
  if (in1 == 1 && in2 == 1) {
    digitalWrite(5,HIGH);
  } else {
    digitalWrite(5,LOW);
  }

}
