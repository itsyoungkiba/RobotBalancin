#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

const int stepPin1 = 2; // Motor 1 STEP
const int dirPin1 = 3;  // Motor 1 DIR
const int stepPin2 = 4; // Motor 2 STEP
const int dirPin2 = 5;  // Motor 2 DIR

const int irLeftPin = A0;  // Sensor IR izquierdo
const int irRightPin = A1; // Sensor IR derecho

float setPoint = 0;        // Ángulo deseado para mantener equilibrio
float input, output;       // Variables para el PID
float Kp = 50, Ki = 0.5, Kd = 2; // Parámetros del PID

unsigned long previousMillis = 0;
const int interval = 10; // Intervalo de tiempo para actualizar el PID

void setup() {
  Serial.begin(115200);
  
  // Inicialización de motores
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  
  // Inicialización de I2C y MPU6050
  Wire.begin(); // Inicia la comunicación I2C
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 no conectado");
    while (1);
  }
  
  Serial.println("MPU6050 listo");
}

void loop() {
  // Leer ángulo del MPU6050
  int16_t ax, ay, az, gx, gy, gz; // Variables para datos del MPU6050
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  input = atan2(ax, az) * 180 / PI; // Convertir a ángulo en grados

  // Control PID
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    float error = setPoint - input;
    static float prevError = 0;
    static float integral = 0;

    integral += error * interval;
    float derivative = (error - prevError) / interval;

    output = Kp * error + Ki * integral + Kd * derivative;

    prevError = error;

    // Control de motores
    moveMotors(output);
  }

  // Lectura de sensores IR para seguir líneas (opcional)
  int irLeft = analogRead(irLeftPin);
  int irRight = analogRead(irRightPin);

  // Lógica para seguir líneas (puedes agregar aquí)
}

void moveMotors(float speed) {
  if (speed > 0) {
    digitalWrite(dirPin1, HIGH);
    digitalWrite(dirPin2, HIGH);
  } else {
    digitalWrite(dirPin1, LOW);
    digitalWrite(dirPin2, LOW);
  }
  speed = abs(speed);
  for (int i = 0; i < speed; i++) {
    digitalWrite(stepPin1, HIGH);
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
}
