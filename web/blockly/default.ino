int in1;

int in2;

void setup()
{
  pinMode(5, OUTPUT);
}


void loop()
{
  in1 = analogRead(A0);
  in2 = analogRead(A3);
  if (in1 >= 1000 && in2 >= 1000) {
    digitalWrite(5,HIGH);

  } else {
    digitalWrite(5,LOW);

  }

}
