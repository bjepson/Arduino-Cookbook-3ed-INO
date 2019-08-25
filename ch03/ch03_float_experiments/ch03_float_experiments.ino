void divide_test(float a, float b, long c, long d) {
    Serial.println(a/b, 10);
    Serial.print(c / d);
    Serial.print(".");
    Serial.println(((c % d) * 100) / d);

}

void setup() {
    Serial.begin(9600);
    Serial.println(36.3/3, 10);
    float a = 36.3;
    float b = 3; 
    Serial.println(a/b, 10);
    divide_test(36.3, 3, 363, 30);
    divide_test(5, 9, 50, 90);


    
    int int_part = 363/30; // result: 12
    int remainder = 363 % 30; // result: 3
    int fractional_part = remainder * 100 / 30;
    Serial.print(int_part); Serial.print("."); Serial.println(fractional_part);
    
}

void loop() {
  // put your main code here, to run repeatedly:

}
