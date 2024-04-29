#define BLYNK_TEMPLATE_ID "TMPL3DuSz8nRm"
#define BLYNK_TEMPLATE_NAME "Home Automation"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "NZZ3X8S1y3vpETVaXp91cpEHjCuQxJux";//Enter your Auth token
char ssid[] = "TARK1";//Enter your WIFI name
char pass[] = "12345678";//Enter your WIFI password

DHT dht(D3, DHT11); //(sensor pin,sensor type)
BlynkTimer timer;


#define relay1 D2
#define relay2 D1
#define LDR D0



void setup() {
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht.begin();

  timer.setInterval(100L, DHT11sensor);
  timer.setInterval(100L, light);
}



//Get the DHT11 sensor values
void DHT11sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V2, t);
  Blynk.virtualWrite(V3, h);

}

void light(){
  int LDRReading = digitalRead(LDR);
  Serial.print("LDRReading: ");
  Serial.println(LDRReading);
  Blynk.virtualWrite(V4,LDRReading);
 }



//Get buttons values
BLYNK_WRITE(V5) {
 bool RelayOne = param.asInt();
  if (RelayOne == 0) {
    digitalWrite(relay1, LOW);
  } else {
    digitalWrite(relay1, HIGH);
  }
}

//Get buttons values
BLYNK_WRITE(V6) {
 bool RelayTwo = param.asInt();
  if (RelayTwo == 0) {
    digitalWrite(relay2, LOW);
  } else {
    digitalWrite(relay2, HIGH);
  }
}

void loop() {
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer
}
