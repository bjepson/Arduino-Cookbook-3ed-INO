/*
 * RelationalExpressions sketch
 * demonstrates comparing values
 */

int i = 1;  // some values to start with
int j = 2;

void setup() {
  Serial.begin(9600);
}

void loop(){

  if ('b' > 'a')
  {
    Serial.println("b > a");
  }
  if ('a' == 97)
  {
    Serial.println("a == 97");
  }

  String word1 = String("Hello");
  char word2[] = "World";
  if (word1.charAt(0) > 'G')
  { 
    Serial.println("word1[0] > G");
  }
  if (word2[0] >= 'W')
  {
    Serial.println("word2[0] >= W");
  }

  Serial.print("i = ");
  Serial.print(i);
  Serial.print(" and j = ");
  Serial.println(j);

  if(i < j)
    Serial.println(" i is less than j");
  if(i <= j)
    Serial.println(" i is less than or equal to j");
  if(i != j)
    Serial.println(" i is not equal to j");
  if(i == j)
    Serial.println(" i is equal to j");
  if(i >= j)
    Serial.println(" i is greater than or equal to j");
  if(i > j)
    Serial.println(" i is greater than j");

  Serial.println();
  i = i + 1;
  if(i > j + 1)
  {
    delay(10000);  // long delay after i is no longer close to j
  }
  else
  {
    delay(1000);   // short delay
  }
  
}
