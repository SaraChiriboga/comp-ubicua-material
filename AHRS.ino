#include <Arduino_LSM6DS3.h>

void setup() {
  Serial.begin(9600);
  while (!Serial); // Esperar a que se abra el monitor serial

  // Iniciar el sensor IMU integrado
  if (!IMU.begin()) {
    Serial.println("Error: No se pudo iniciar el sensor LSM6DS3.");
    while (1);
  }

  // (Opcional) Mensaje de confirmación, comentado para no ensuciar la trama de Unity
  // Serial.println("Sensor LSM6DS3 iniciado correctamente.");
}

void loop() {
  float ax, ay, az;
  float gx, gy, gz;

  // Verificar si hay datos disponibles de aceleración y giroscopio
  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
    
    // Leer los valores
    IMU.readAcceleration(ax, ay, az);
    IMU.readGyroscope(gx, gy, gz);

    // Enviar la trama con el formato estricto de la guía: 
    // Ax,Ay,Az,Gx,Gy,Gz con salto de línea al final
    
    Serial.print(ax);
    Serial.print(",");
    Serial.print(ay);
    Serial.print(",");
    Serial.print(az);
    Serial.print(",");
    Serial.print(gx);
    Serial.print(",");
    Serial.print(gy);
    Serial.print(",");
    Serial.println(gz); // El println final hace el salto de línea
  }
  
  // Un pequeño delay para mantener la tasa de refresco estable 
  // (La guía sugiere no saturar, 20ms da unos 50Hz)
  delay(200);
}