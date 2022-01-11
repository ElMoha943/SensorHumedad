//Librerias
#include <DHT.h>

// Definimos el pin digital donde se conecta el sensor y el tipo de sensor
#define DHTPIN 2
#define DHTTYPE DHT11

// Definimos las valvulas
#define V1 7
#define V2 6
#define V3 5

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {

  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  
  // Inicializamos comunicación serie
  Serial.begin(9600);

  // Comenzamos el sensor DHT
  dht.begin();
}

void loop() {
    // Esperamos 5 segundos entre medidas
    delay(5000);
   
    float h = dht.readHumidity();
    float t = dht.readTemperature();
   
    // Comprobamos si ha habido algún error en la lectura
    if (isnan(h) || isnan(t)) {
      Serial.println("Error obteniendo los datos del sensor DHT11");
      return;
    }
   
    // Calcular el índice de calor en grados centígrados
    float hic = dht.computeHeatIndex(t, h, false);
   
    Serial.print("Humedad: \r\n");
    Serial.print(h);
    Serial.print(" %\t\r\n");
    Serial.print("Temperatura: \r\n");
    Serial.print(t);
    Serial.print(" *C \r\n");
    Serial.print("Índice de calor: \r\n");
    Serial.print(hic);
    Serial.print(" *C \r\n");

    if(h > 80) digitalWrite(V1, HIGH);
    else digitalWrite(V1, LOW);
    
    if(t > 30) digitalWrite(V2, HIGH);
    else digitalWrite(V2, LOW);

    if(hic > 30) digitalWrite(V3, HIGH);
    else digitalWrite(V3, LOW);
}
