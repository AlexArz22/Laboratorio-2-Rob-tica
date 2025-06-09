#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <MPU6050_light.h>

// Pines de motor
const int IN1 = 3, IN2 = 4, ENA = 9;
const int IN3 = 7, IN4 = 6, ENB = 10;

// Pines del sensor ultrasónico
const int TRIG = 11;
const int ECHO = 5;

// sensor rgb
Adafruit_TCS34725 rgbSensor = Adafruit_TCS34725();
//sensor mpu
MPU6050 mpu(Wire);

// Variables de tiempo
unsigned long lastTime;

void setup() {
  Serial.begin(9600);

  // Motores
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);

  // Ultrasónico
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // IMU
  Wire.begin();
  mpu.begin();
  mpu.calcGyroOffsets();

  // RGB
  if (!rgbSensor.begin()) {
    Serial.println("Sensor RGB no detectado");
    while (1);
  }

  lastTime = millis();
}

void loop() {
  float distancia = medirDistancia();
  String colorDetectado = detectarColor();
  mpu.update();

  Serial.print("Distancia (cm): "); Serial.print(distancia, 2);
  Serial.print(" | Color: "); Serial.print(colorDetectado);
  Serial.print(" | GyroZ: "); Serial.println(mpu.getGyroZ(), 2);

  if (distancia < 10.0) {
    detener();
  } else {
    if (colorDetectado == "Rojo") {
      girarIzquierda();
    } else if (colorDetectado == "Verde") {
      avanzar();
    } else if (colorDetectado == "Azul") {
      girarDerecha();
    } else {
      detener();
    }
  }

  delay(100);
}

float medirDistancia() {
  digitalWrite(TRIG, LOW); delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duracion = pulseIn(ECHO, HIGH);
  float distancia = duracion * 0.034 / 2;
  return distancia;
}

String detectarColor() {
  uint16_t r, g, b, c;
  rgbSensor.getRawData(&r, &g, &b, &c);
  Serial.print("R: "); Serial.print(r);
  Serial.print(" G: "); Serial.print(g);
  Serial.print(" B: "); Serial.print(b);
  Serial.print(" C: "); Serial.println(c);
  //decidi separarlo por dia y noche ya que C es una variable que mide la cant de luz blanca
  //devido a que de noche la luz de un foco no genera suficiente luz blanca decidi separarlas 
  //noche
  if(c<15){
    if (r > g && r > b && r > 3) return "Rojo";
    else if (g > r && g > b && g > 3) return "Verde";
    else if (b > r && b > g && b > 3) return "Azul";
    else return "desconocido";
  }else {//dia
    if (r > g && r > b && r > 10) return "Rojo";
    else if (g > r && g > b && g > 10) return "Verde";
    else if (b > r && b > g && b > 10) return "Azul";
    else return "desconocido";
  }

}

// Movimiento
void avanzar() {
  digitalWrite(IN2, LOW); digitalWrite(IN1, HIGH);
  digitalWrite(IN4, LOW); digitalWrite(IN3, HIGH);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
}

void detener() {
  digitalWrite(IN2, LOW); digitalWrite(IN1, LOW);
  digitalWrite(IN4, LOW); digitalWrite(IN3, LOW);
}

void girarIzquierda() {
  digitalWrite(IN2, HIGH); digitalWrite(IN1, LOW);
  digitalWrite(IN4, LOW); digitalWrite(IN3, HIGH);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
}

void girarDerecha() {
  digitalWrite(IN2, LOW); digitalWrite(IN1, HIGH);
  digitalWrite(IN4, HIGH); digitalWrite(IN3, LOW);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
}
