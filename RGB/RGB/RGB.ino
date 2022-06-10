const int redPin = 6; //Initialize RED Color pin
const int greenPin = 5;//Initialize GREEN Color pin
const int bluePin = 3;//Initialize BLUE Color pin

void setup()
{
  pinMode(redPin, OUTPUT);//Define RED Color pin as output
  pinMode(greenPin, OUTPUT);//Define GREEN Color pin as output
  pinMode(bluePin, OUTPUT);//Define BLUE Color pin as output
}

// Fuction to handle multiple colors
void primaryColors(int redValue, int greenValue, int blueValue)
{
  digitalWrite(redPin, redValue);
  digitalWrite(greenPin, greenValue);
  digitalWrite(bluePin, blueValue);
}

void loop()
{
  delay(1000);
  primaryColors(1, 0, 0); // Red
  delay(2000);
  primaryColors(0, 1, 0); // Green
  delay(2000);
  primaryColors(0, 0, 1); // Blue
  delay(2000);
  primaryColors(1, 1, 0); // Yellow
  delay(2000);
  primaryColors(1, 0, 1); // Magenta
  delay(2000);
  primaryColors(0, 1, 1); // Cyan
  delay(2000);
  primaryColors(1, 1, 1); // White
  delay(2000);
}
