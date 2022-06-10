//Initializing LED Pin
int led_pin = 6;

void setup() {
  //Declaring LED pin as output
  pinMode(led_pin, OUTPUT);
}

void loop()
{
  digitalWrite(led_pin, HIGH);
  delayMicroseconds(100); // Approximately 10% duty cycle @ 1KHz
  digitalWrite(led_pin, LOW);
  delayMicroseconds(1000 - 100);
}
