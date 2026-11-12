#include <WiFi.h>


const char* WIFI_SSID = "Kivaplusvite";
const char* WIFI_PASS = "souponpochon";
const char* HOST      = "192.168.1.190";   // adresse du Mac
const uint16_t PORT   = 4242;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);                    // l'ESP est cliente du Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) { // attente de la connexion Wi-Fi
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nIP de la carte : ");
  Serial.println(WiFi.localIP());

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
}

void loop() {
  // (re)connexion au serveur si nécessaire
  if (!client.connected()) {
    Serial.println("Connexion au serveur...");
    if (!client.connect(HOST, PORT)) {    // socket() + connect()
      Serial.println("Echec, nouvel essai dans 2 s");
      delay(2000);
      return;
    }
    Serial.println("Connecte.");
  }

  if (client.available()) {                       // des octets sont arrivés
    String cmd = client.readStringUntil('\n');    // lit jusqu'au délimiteur
    cmd.trim();   // retire d'éventuels '\r'
    Serial.println(cmd);

    if (cmd == "RED")   {
      digitalWrite(D0, HIGH);
      digitalWrite(D1, LOW);
    }    
    else if (cmd == "GREEN") {
      digitalWrite(D1, HIGH);
      digitalWrite(D0, LOW);

    } 
  }
  // client.print("bonjour");
}
