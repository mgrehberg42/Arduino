int motorPin = 3;

void setup()
{
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  Serial.println("Grove - MOSFET Test Demo!");
}

void loop()
{
  digitalWrite(motorPin, HIGH);
  //analogWrite(motorPin, 255);
  delay(1000);
  digitalWrite(motorPin, LOW);
  //analogWrite(motorPin, 0);
  delay(1000);
}
