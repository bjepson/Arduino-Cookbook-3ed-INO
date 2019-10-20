/*
 * camera sketch
 * takes 20 pictures with a digital camera
 * using pin 4 to trigger focus
 * pin 3 to trigger the shutter
 */

int focus = 4;          // optocoupler attached to focus
int shutter = 3;        // optocoupler attached to shutter
long exposure = 250;    // exposure time in milliseconds
long interval = 10000;  // time between shots, in milliseconds

void setup()
{
  pinMode(focus, OUTPUT);
  pinMode(shutter, OUTPUT);
  for (int i=0; i<20; i++)  // camera will take 20 pictures
  {
    takePicture(exposure);       // takes picture
    delay(interval);             // wait to take the next picture
  }
}

void loop()
{
                  // once it's taken 20 pictures it is done,
                  // so loop is empty
                  // but loop still needs to be here or the
                  // sketch won't compile
}

void takePicture(long exposureTime)
{
  int wakeup = 10;      // camera will take some time to wake up and focus
                        // adjust this to suit your camera
                                            
  digitalWrite(focus, HIGH);     // wake the camera and focus
  delay(wakeup);                 // wait for it to wake up and focus
  digitalWrite(shutter, HIGH);   // open the shutter
  delay(exposureTime);           // wait for the exposure time
  digitalWrite(shutter, LOW);    // release shutter
  digitalWrite(focus, LOW);      // release the focus
}
