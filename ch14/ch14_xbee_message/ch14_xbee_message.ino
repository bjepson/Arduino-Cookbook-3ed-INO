/*
 * XBee Message sketch
 * Send a message to an XBee using its address
 */

// Uncomment only one of the following
#define MYSERIAL Serial // Uno, Nano, and other AVR boards
//#define MYSERIAL Serial1 // Nano Every, Uno WiFi R2, Leonardo, and ARM boards

bool configured;

bool configureRadio() 
{
  // put the radio in command mode:
  MYSERIAL.flush();
  MYSERIAL.print("+++");
  delay(100);

  String ok_response = "OK\r"; // the response we expect.

  // Read the text of the response into the response variable
  String response = String("");
  while (response.length() < ok_response.length()) 
  {
    if (MYSERIAL.available() > 0) 
    {
      response += (char) MYSERIAL.read();
    }
  }

  // If we got the right response, configure the radio and return true.
  if (response.equals(ok_response)) 
  {
    MYSERIAL.print("ATDH0013A200\r"); // destination high-REPLACE 0013A200
    delay(100);
    MYSERIAL.print("ATDL403B9E1E\r"); // destination low-REPLACE 403B9E1E
    delay(100);
    MYSERIAL.print("ATCN\r");     // back to data mode
    return true;
  } 
  else 
  {
    return false; // This indicates the response was incorrect.
  }
}

void setup () 
{
  MYSERIAL.begin(9600); // Begin serial
  delay(1000);
  configured = configureRadio();
}

void loop () 
{
  if (configured) 
  {
    MYSERIAL.print("Hello!");
    delay(3000);
  }
  else 
  {
    delay(30000);     // Wait 30 seconds
    configured = configureRadio(); // try again
  }
}
