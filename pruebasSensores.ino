#include <Adafruit_TCS34725.h>
#include <Wire.h>
#include <MPU9250_asukiaaa.h>

//cada variable separada por sensor
// HC-SR04
const int trigPin = 11;
const int echoPin = 5;

// Sensor RGB 
Adafruit_TCS34725 rgbSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// IMU
MPU9250_asukiaaa imu;


long duration;
float distanceCM;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // HC-SR04
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Sensor RGB
  if (rgbSensor.begin()) {
    Serial.println("Sensor RGB detectado.");
  } else {
    Serial.println("¡Error: no se detectó el sensor RGB!");
    while (1);
  }

  // IMU
  imu.setWire(&Wire);
  imu.beginAccel();
  imu.beginGyro();
  delay(200);

  Serial.println("Sistema iniciado.");
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCM = duration * 0.034 / 2;


  uint16_t r, g, b, c;
  rgbSensor.getRawData(&r, &g, &b, &c);

  String detectedColor = "Desconocido";
  if (r > g && r > b && r > 50) detectedColor = "Rojo";
  else if (g > r && g > b && g > 50) detectedColor = "Verde";
  else if (b > r && b > g && b > 50) detectedColor = "Azul";

  imu.accelUpdate();
  imu.gyroUpdate();
  float ax = imu.accelX();
  float ay = imu.accelY();
  float az = imu.accelZ();
  float gz = imu.gyroZ();

  // mostrar datos de sensores
  Serial.print("Distancia (cm): ");
  Serial.print(distanceCM, 2);
  Serial.print(" | Color: ");
  Serial.print(detectedColor);
  Serial.print(" (Rojo: "); Serial.print(r);
  Serial.print(", verder: "); Serial.print(g);
  Serial.print(", Azul: "); Serial.print(b);
  Serial.print(") | Aceleración (Z): ");
  Serial.print(az, 2);
  Serial.print(" | GyroZ: ");
  Serial.println(gz, 2);

  delay(300);  
}
