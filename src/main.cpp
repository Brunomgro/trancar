#include <WiFi.h>
#include <FirebaseESP32.h>

#define WIFI_SSID ""
#define WIFI_PASSWORD ""

const char *host = "";
const char *auth = "";
const char *name = "ALGORITMOS APLICADOS A PROJETOS";
const int led = 22;

FirebaseData fbdo;

int count = 0;


void generateUser(String name) {
    Firebase.setStringAsync(fbdo, "/database/users/" + name + "/car", "fox");
    Firebase.setStringAsync(fbdo, "/database/users/" + name + "/car", "");
    Firebase.setBoolAsync(fbdo, "/database/users/" + name + "/actions/lockCar", false);
    Firebase.setBoolAsync(fbdo, "/database/users/" + name + "/carState/locked", false);
    Firebase.setIntAsync(fbdo, "/database/users/" + name + "/carState/fuelLevel", 0);
    Firebase.setIntAsync(fbdo, "/database/users/" + name + "/carState/batteryLevel", 0);
    Firebase.setIntAsync(fbdo, "/database/users/" + name + "/id", 2);
}

void setup()
{
    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    Firebase.begin(host, auth);

    Firebase.reconnectWiFi(true);

    pinMode(led, OUTPUT);

    generateUser("rodrigo");
}

void loop() {
    boolean ligaled = false;

    Firebase.setIntAsync(fbdo, "/Todo/ContagemESP/Npessoas", count);
    Firebase.setStringAsync(fbdo, "/Todo/ContagemESP/title", name);
    Firebase.setStringAsync(fbdo, "/Todo/ContagemESP/myName", "Bruno Alves");
    Firebase.setStringAsync(fbdo, "/Todo/ContagemESP2/myName", "Rodrigo");
    Firebase.getBool(fbdo, "Todo/ligaLed", ligaled);

    if (ligaled) {
        digitalWrite(led, HIGH);
        Firebase.setBoolAsync(fbdo, "Todo/ligaLed", false);
    } else {
        digitalWrite(led, LOW);
        Firebase.setBoolAsync(fbdo, "Todo/ligaLed", true);
    }

    count++;
    delay(2000);
}
