#include <ArduinoBLE.h>// libreria arduino BLE 
#include <Arduino_LSM6DS3.h>// libreria IMU 
 
BLEService accelerometerService("19b10000-e8f2-537e-4f6c-d104768a1214"); 
BLEStringCharacteristic firstCharacteristic("19b10010-e8f2-537e-4f6cd104768a1214",  BLERead | BLENotify, 50); // los clientes remotos podrán recibir 
String oldAcclerometerReading = "0"; 
long previousMillis = 0;   
 
void setup()  
{ 
  Serial.begin(9600);    //inicio comunicacion serial 
  while (!Serial); 
  pinMode(LED_BUILTIN, OUTPUT); // informar con el LED 13 si una central esta conectada 
  if (!BLE.begin())  
  { 
    Serial.println("Inicio BLE fallido!"); 
    while (1); 
  } 
  if (!IMU.begin()) 
  { 
    Serial.println("Fallo inicio de IMU!"); 
    while (1); 
  } 
  Serial.print("Frecuencia de Acelerometro = "); 
  Serial.print(IMU.accelerationSampleRate()); 
  Serial.println(" Hz"); 
  Serial.println(); 
 
  BLE.setLocalName("Placa MartiJohannTonySari"); 
  BLE.setAdvertisedService(accelerometerService); // agregar el UUID del servicio 
  accelerometerService.addCharacteristic(firstCharacteristic); // agregar la característica 
  BLE.addService(accelerometerService); // Agregar el servicio 
  firstCharacteristic.writeValue(oldAcclerometerReading); // establecer el valor inicial para esta característica 
  BLE.advertise(); 
  Serial.println("Dispositivo Bluetooth activo, esperando conexiones..."); 
}

 
void loop()  
{ 
  
  BLEDevice central = BLE.central(); //esperar una central BLE 
  if (central)  
  { 
    Serial.print("Conectado a la central: "); 
    Serial.println(central.address());//imprima la dirección BT de la 
central: 
    digitalWrite(LED_BUILTIN, HIGH);//encienda el LED para indicar la conexión: 
    while (central.connected()) //Mientras la central está conectada: 
    { 
    updateAcceleration(); 
    } 
    digitalWrite(LED_BUILTIN, LOW);//// cuando la central se desconecta, apaga el LED: 
    Serial.print("Desconectado de la central: "); 
    Serial.println(central.address()); 
  } 
} 
 
void updateAcceleration()  
{ 
  float x, y, z; 
  if (IMU.accelerationAvailable()) 
  { 
    IMU.readAcceleration(x, y, z); 
    String accelerometerData = 
String(x*9.8)+"|"+String(y*9.8)+"|"+String(z*9.8);//acelerometro en m/s2 
    Serial.println(accelerometerData); 
    firstCharacteristic.writeValue(accelerometerData); 
  } 
}