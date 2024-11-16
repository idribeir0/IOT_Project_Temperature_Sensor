#include <DHT.h>
#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

//pinos do DHT11 e LEDs
#define DHTPIN 4           
#define DHTTYPE DHT11      
#define LED_GREEN 2        
#define LED_RED 5          

//wiFi
#define WLAN_SSID       "nome_wifi" //usuario deve incluir nome do wifi
#define WLAN_PASS       "senha_wifi" //usuario deve incluir a senha do wifi

//servidor MQTT
#define MQTT_SERVER     "io.adafruit.com"
#define MQTT_SERVERPORT 1883
#define MQTT_USERNAME   "user" //usuario deve incluir user do adafruit
#define MQTT_KEY        "senha_api" //usuario deve incluir key api do adafruit

//sensor DHT
DHT dht(DHTPIN, DHTTYPE);

//instancia
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_KEY);

//MQTT para temperatura e umidade
Adafruit_MQTT_Publish temperaturaPub = Adafruit_MQTT_Publish(&mqtt, MQTT_USERNAME "/feeds/temperatura");
Adafruit_MQTT_Publish umidadePub = Adafruit_MQTT_Publish(&mqtt, MQTT_USERNAME "/feeds/umidade");

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  connectWiFi();
  connectMQTT();
}

void loop() {
  //tempo resposta
  unsigned long startSensorTime = millis();
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  unsigned long endSensorTime = millis();
  unsigned long responseTimeSensor = endSensorTime - startSensorTime;

  //leitura
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Falha ao ler do sensor DHT!");
    return;
  }

  //resultado
  Serial.print("Umidade: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" °C");

  //tempo resposta sensor
  Serial.print("Tempo de resposta do sensor: ");
  Serial.print(responseTimeSensor);
  Serial.println(" ms");

  //tempo resposta atuador
  unsigned long startActuatorTime = millis();
  if (temperature < 28) {
    digitalWrite(LED_GREEN, LOW);  //acender o LED verde
    digitalWrite(LED_RED, HIGH);     //apagar o LED vermelho
  } else {
    digitalWrite(LED_GREEN, HIGH);   //apagar o LED verde
    digitalWrite(LED_RED, LOW);    //acender o LED vermelho
  }
  unsigned long endActuatorTime = millis();
  unsigned long responseTimeActuator = endActuatorTime - startActuatorTime;

  Serial.print("Tempo de resposta do atuador: ");
  Serial.print(responseTimeActuator);
  Serial.println(" ms");

  //reconecta MQTT
  if (!mqtt.connected()) {
    connectMQTT();
  }

  //tempo envio MQTT
  unsigned long startMQTTTime = millis();
  if (!temperaturaPub.publish(temperature)) {
    Serial.println("Falha ao publicar temperatura!");
  }
  if (!umidadePub.publish(humidity)) {
    Serial.println("Falha ao publicar umidade!");
  }
  unsigned long endMQTTTime = millis();
  unsigned long responseTimeMQTT = endMQTTTime - startMQTTTime;

  Serial.print("Tempo de envio via MQTT: ");
  Serial.print(responseTimeMQTT);
  Serial.println(" ms");

  delay(2000);
}

void connectWiFi() {
  Serial.print("Conectando ao WiFi...");
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Conectado ao WiFi!");
}

void connectMQTT() {
  Serial.print("Conectando ao MQTT...");
  while (mqtt.connect() != 0) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" Conectado ao MQTT!");
}
