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

String prevColor = "Desconocido";
unsigned long cambioInicio = 0;
bool esperandoCambio = false;

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

  // Medir tiempo de cambio
  if (detectedColor != prevColor) {
    if (!esperandoCambio) {
      cambioInicio = millis();
      esperandoCambio = true;
    } else {
      unsigned long tiempoCambio = millis() - cambioInicio;
      Serial.print(">>> Tiempo de detección del cambio a ");
      Serial.print(detectedColor);
      Serial.print(": ");
      Serial.print(tiempoCambio);
      Serial.println(" ms");
      esperandoCambio = false;
    }
    prevColor = detectedColor;
  }

  imu.accelUpdate();
  imu.gyroUpdate();
  float az = imu.accelZ();
  float gz = imu.gyroZ();

  Serial.print("Distancia (cm): ");
  Serial.print(distanceCM, 2);
  Serial.print(" | Color: ");
  Serial.print(detectedColor);
  Serial.print(" (R: "); Serial.print(r);
  Serial.print(", G: "); Serial.print(g);
  Serial.print(", B: "); Serial.print(b);
  Serial.print(") | AcelZ: ");
  Serial.print(az, 2);
  Serial.print(" | GyroZ: ");
  Serial.println(gz, 2);

  delay(300);
}