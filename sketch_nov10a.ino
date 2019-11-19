#include <ESP8266WiFi.h>
#include <dht.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "7fb88ab6e63444d38979af41a477dd15";//For Emma's phone
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "TECHNO SPARK 2";
char pass[] = "4ac45899500";
#define BLYNK_PRINT Serial
#define DHTPIN 2          // What digital pin we're connected to
dht DHT;  //Create an object DHT
BlynkTimer timer;


// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
int readData = DHT.read11(DHTPIN);
  float h = DHT.humidity;
  float t = DHT.temperature; 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  if (WIFI_STA==WL_CONNECTED){
Serial.print("\nConnected to: "); Serial.print("\t");Serial.print(WiFi.localIP());}
Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}


