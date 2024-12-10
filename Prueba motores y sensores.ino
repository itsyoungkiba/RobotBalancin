// Pines de los motores paso a paso
#define DIR_MOTOR_IZQUIERDO 2
#define STEP_MOTOR_IZQUIERDO 3
#define DIR_MOTOR_DERECHO 4
#define STEP_MOTOR_DERECHO 5

// Pines de los sensores infrarrojos
#define SENSOR_IZQUIERDO 12
#define SENSOR_DERECHO 13

// Configuración de los pasos
const int stepsPerRevolution = 200; // Cambia según tu motor
int motorSpeed = 2000; // Velocidad del motor en microsegundos entre pasos (mayor valor = más lento)

void setup() {
  // Configuración de pines de los motores
  pinMode(DIR_MOTOR_IZQUIERDO, OUTPUT);
  pinMode(STEP_MOTOR_IZQUIERDO, OUTPUT);
  pinMode(DIR_MOTOR_DERECHO, OUTPUT);
  pinMode(STEP_MOTOR_DERECHO, OUTPUT);

  // Configuración de pines de los sensores
  pinMode(SENSOR_IZQUIERDO, INPUT);
  pinMode(SENSOR_DERECHO, INPUT);
}

void loop() {
  bool sensorIzquierdo = digitalRead(SENSOR_IZQUIERDO);
  bool sensorDerecho = digitalRead(SENSOR_DERECHO);

  if (!sensorIzquierdo && !sensorDerecho) {
    // Ambos sensores están sobre la línea (avanzar recto)
    avanzar();
  } else if (!sensorIzquierdo && sensorDerecho) {
    // Solo el sensor izquierdo está sobre la línea (girar a la izquierda)
    girarIzquierda();
  } else if (sensorIzquierdo && !sensorDerecho) {
    // Solo el sensor derecho está sobre la línea (girar a la derecha)
    girarDerecha();
  } else {
    // Ningún sensor está sobre la línea (detenerse o retroceder)
    detener();
  }
}

void avanzar() {
  digitalWrite(DIR_MOTOR_IZQUIERDO, HIGH);
  digitalWrite(DIR_MOTOR_DERECHO, HIGH);
  for (int i = 0; i < stepsPerRevolution; i++) {
    digitalWrite(STEP_MOTOR_IZQUIERDO, HIGH);
    digitalWrite(STEP_MOTOR_DERECHO, HIGH);
    delayMicroseconds(motorSpeed);
    digitalWrite(STEP_MOTOR_IZQUIERDO, LOW);
    digitalWrite(STEP_MOTOR_DERECHO, LOW);
    delayMicroseconds(motorSpeed);
  }
}

void girarIzquierda() {
  digitalWrite(DIR_MOTOR_IZQUIERDO, LOW);
  digitalWrite(DIR_MOTOR_DERECHO, HIGH);
  for (int i = 0; i < stepsPerRevolution / 2; i++) {
    digitalWrite(STEP_MOTOR_IZQUIERDO, HIGH);
    digitalWrite(STEP_MOTOR_DERECHO, HIGH);
    delayMicroseconds(motorSpeed);
    digitalWrite(STEP_MOTOR_IZQUIERDO, LOW);
    digitalWrite(STEP_MOTOR_DERECHO, LOW);
    delayMicroseconds(motorSpeed);
  }
}

void girarDerecha() {
  digitalWrite(DIR_MOTOR_IZQUIERDO, HIGH);
  digitalWrite(DIR_MOTOR_DERECHO, LOW);
  for (int i = 0; i < stepsPerRevolution / 2; i++) {
    digitalWrite(STEP_MOTOR_IZQUIERDO, HIGH);
    digitalWrite(STEP_MOTOR_DERECHO, HIGH);
    delayMicroseconds(motorSpeed);
    digitalWrite(STEP_MOTOR_IZQUIERDO, LOW);
    digitalWrite(STEP_MOTOR_DERECHO, LOW);
    delayMicroseconds(motorSpeed);
  }
}

void detener() {
  digitalWrite(STEP_MOTOR_IZQUIERDO, LOW);
  digitalWrite(STEP_MOTOR_DERECHO, LOW);
}

