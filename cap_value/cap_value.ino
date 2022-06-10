/*Arduino测量电容值
 * 
 */
#define NO_MEASSUREMENTS 3 
#define analog_pin     A0
#define capacitor_pin  7
 
//#define resistor_value   989000.0F // the value on the resistor in Ohms
 #define resistor_value   989000.0F // the value on the resistor in Ohms
unsigned long start_time = 0;
unsigned long accumulated_time = 0;
 
void setup() {
  pinMode(capacitor_pin, OUTPUT);
 
  Serial.begin(115200);
}
 
void loop() {
 
  accumulated_time = 0;
 
  for(uint8_t i = 0; i < NO_MEASSUREMENTS; i++){
 
    // Make sure the capacitor is dicharged
    digitalWrite(capacitor_pin, LOW);
    while(analogRead(analog_pin) > 0){}
    
    // set chargePin HIGH and capacitor charging an
    digitalWrite(capacitor_pin, HIGH);
    start_time = micros();
  
    // 647 is 63.2% of 1023, which corresponds to full-scale voltage
    while(analogRead(analog_pin) <= 647){}  
    accumulated_time += (micros() - start_time);  
  }  
 
  float result_time = ((float) accumulated_time) / NO_MEASSUREMENTS;
 
  float micro_F = ( result_time / resistor_value) * 1000;
 
  Serial.print((long)result_time);
  Serial.print(" us before tau / ");
  
  print_float(micro_F, 2);
  Serial.println(" uF");
}
 
 
// from Peter H. Anderson, Baltimore, MD
void print_float(float f, int num_digits)
{
  int pows_of_ten[4] = {1, 10, 100, 1000};
  int multiplier, whole, fract, d, n;
  
  multiplier = pows_of_ten[num_digits];
  
  if (f < 0.0){
    f = -f;
    Serial.print("-");
  }
  
  whole = (int) f;
  fract = (int) (multiplier * (f - (float)whole));
  
  Serial.print(whole);
  Serial.print(",");
 
  // print each digit with no leading zero suppression
  for (n=num_digits-1; n>=0; n--){
   d = fract / pows_of_ten[n];
   Serial.print(d);
   fract = fract % pows_of_ten[n];
  }
}
 
