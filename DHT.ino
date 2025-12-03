// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
// Este sketch de ejemplo prueba sensores DHT (DHT11/DHT22/DHT21) y muestra lecturas por Serial.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
// Requiere instalar las librerías indicadas para poder compilar y usar la clase DHT correctamente.

#include "DHT.h"  // Incluye la librería DHT de Adafruit, que provee la clase y métodos para leer el sensor.

// Definición del pin digital al que se conecta el pin de datos del DHT.
#define DHTPIN 15     // Pin digital conectado al sensor DHT.
// Nota para Feather HUZZAH ESP8266: usar pines 3, 4, 5, 12, 13 o 14.
// El pin 15 puede funcionar, pero el DHT debe desconectarse durante la carga del programa.
// Esto es por el comportamiento de arranque del ESP8266 en ciertos pines.

// Selección del tipo de sensor DHT.
// Descomenta el que estés usando y deja comentados los demás.
//#define DHTTYPE DHT11   // DHT 11 (sensor básico, menor precisión)
#define DHTTYPE DHT22   // DHT 22 (AM2302), AM2321 (mayor precisión y rango)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Conexiones físicas recomendadas:
// Conecta el pin 1 (izquierda) del sensor a +5V.
// NOTA: Si usas una placa con lógica de 3.3V (p. ej., Arduino Due), conecta el pin 1 a 3.3V en lugar de 5V.
// Conecta el pin 2 (datos) del sensor al pin definido por DHTPIN.
// Conecta el pin 3 (derecha) del sensor a GND (si tu sensor tiene 3 pines).
// Si tu sensor tiene 4 pines: conecta el pin 4 a GND y deja el pin 3 sin conectar.
// Coloca una resistencia de 10K entre el pin 2 (datos) y el pin 1 (alimentación) como pull-up.

// Inicialización del objeto DHT con el pin y el tipo de sensor configurados.
// En versiones antiguas de la librería, se podía pasar un tercer parámetro para ajustar tiempos en procesadores rápidos.
// Ya no es necesario: el algoritmo actual se autoajusta.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);           // Inicializa el puerto serial a 9600 baudios para depuración y salida de datos.
  Serial.println(F("DHTxx test!")); // Imprime un mensaje inicial. F() almacena la cadena en flash (PROGMEM) para ahorrar RAM.

  dht.begin();                  // Inicializa el sensor DHT (configura tiempos y prepara la lectura).
}

void loop() {
  // Espera unos segundos entre mediciones para respetar los tiempos del DHT.
  delay(2000);                  // 2 segundos: el DHT es un sensor relativamente lento y no debe leerse demasiado seguido.

  // Leer temperatura y humedad toma ~250 ms.
  // Las lecturas pueden ser hasta 2 segundos “antiguas” porque el sensor actualiza lentamente su valor interno.
  float h = dht.readHumidity();         // Lee la humedad relativa (%) como float.
  float t = dht.readTemperature();      // Lee temperatura en °C (por defecto).
  float f = dht.readTemperature(true);  // Lee temperatura en °F (parámetro true indica Fahrenheit).

  // Verifica si alguna lectura falló. dht.readXxx() retorna NAN si no pudo leer correctamente.
  if (isnan(h) || isnan(t) || isnan(f)) { // isnan() comprueba si el float es “Not A Number”.
    Serial.println(F("Failed to read from DHT sensor!")); // Reporta error y termina el ciclo actual.
    return; // Sale del loop actual para volver a intentar en la siguiente iteración.
  }

  // Calcula el índice de calor (sensación térmica) en °F usando temperatura en °F y humedad.
  float hif = dht.computeHeatIndex(f, h);
  // Calcula el índice de calor en °C (tercer parámetro false indica que la temperatura está en °C).
  float hic = dht.computeHeatIndex(t, h, false);

  // Ejemplo de salida por Serial:
  // Serial.print(F("Humidity: "));
  Serial.println(h);            // Imprime la humedad en una línea (valor en %).

  // ATENCIÓN: t + '\n' suma el código ASCII del salto de línea (10) al valor de temperatura;
  // no agrega una nueva línea al texto. Para imprimir nueva línea, usa Serial.println(t) o Serial.println().
  Serial.println(t + '\n');     // Imprime temperatura en °C, pero la operación + '\n' es probablemente no intencional.

  // Bloque comentado con salida detallada:
  /*
  Serial.print(F("°C "));
  Serial.print(f);              // Imprime temperatura en °F.
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);            // Imprime índice de calor en °C.
  Serial.print(F("°C "));
  Serial.print(hif);            // Imprime índice de calor en °F.
  Serial.println(F("°F"));
  */
}
