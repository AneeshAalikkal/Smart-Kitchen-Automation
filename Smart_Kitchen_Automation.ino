#include <NewPing.h>

#define TRIG_PIN 2
#define ECHO_PIN 3
#define LDR_PIN A0
#define GAS_SENSOR_PIN A1

#define IR_SENSOR_1_PIN 11
#define IR_SENSOR_2_PIN 12
#define IR_SENSOR_3_PIN 13

#define LED_ULTRASONIC_10_20_PIN 4
#define LED_ULTRASONIC_21_30_PIN 5
#define LED_ULTRASONIC_31_40_PIN 6

#define LED_IR_SENSOR_1_PIN 7
#define LED_IR_SENSOR_2_PIN 8
#define LED_IR_SENSOR_3_PIN 9

#define BUZZER_PIN A2

int distance;
NewPing sonar(TRIG_PIN, ECHO_PIN);

const int DISTANCE_THRESHOLD_1 = 15;
const int DISTANCE_THRESHOLD_2 = 30;
const int DISTANCE_THRESHOLD_3 = 40;
const int GAS_THRESHOLD = 600;
const int LDR_THRESHOLD = 1;

void setup() {
  pinMode(LED_ULTRASONIC_10_20_PIN, OUTPUT);
  pinMode(LED_ULTRASONIC_21_30_PIN, OUTPUT);
  pinMode(LED_ULTRASONIC_31_40_PIN, OUTPUT);
  pinMode(LED_IR_SENSOR_1_PIN, OUTPUT);
  pinMode(LED_IR_SENSOR_2_PIN, OUTPUT);
  pinMode(LED_IR_SENSOR_3_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(IR_SENSOR_1_PIN, INPUT);
  pinMode(IR_SENSOR_2_PIN, INPUT);
  pinMode(IR_SENSOR_3_PIN, INPUT);

  Serial.begin(9600);
}

void loop() {
  int ldrValue = digitalRead(LDR_PIN);

  if (ldrValue == LDR_THRESHOLD) {
    delay(50);
    int distance = sonar.ping_cm();

    if (distance > 0 && distance <= DISTANCE_THRESHOLD_1) {
      analogWrite(LED_ULTRASONIC_10_20_PIN, 255);
      analogWrite(LED_ULTRASONIC_21_30_PIN, 0);
      analogWrite(LED_ULTRASONIC_31_40_PIN, 0);
    } else if (distance > DISTANCE_THRESHOLD_1 && distance <= DISTANCE_THRESHOLD_2) {
      analogWrite(LED_ULTRASONIC_10_20_PIN, 0);
      analogWrite(LED_ULTRASONIC_21_30_PIN, 255);
      analogWrite(LED_ULTRASONIC_31_40_PIN, 0);
    } else if (distance > DISTANCE_THRESHOLD_2 && distance <= DISTANCE_THRESHOLD_3) {
      analogWrite(LED_ULTRASONIC_10_20_PIN, 0);
      analogWrite(LED_ULTRASONIC_21_30_PIN, 0);
      analogWrite(LED_ULTRASONIC_31_40_PIN, 255);
    } else {
      analogWrite(LED_ULTRASONIC_10_20_PIN, 0);
      analogWrite(LED_ULTRASONIC_21_30_PIN, 0);
      analogWrite(LED_ULTRASONIC_31_40_PIN, 0);
    }
  } else {
    analogWrite(LED_ULTRASONIC_10_20_PIN, 0);
    analogWrite(LED_ULTRASONIC_21_30_PIN, 0);
    analogWrite(LED_ULTRASONIC_31_40_PIN, 0);
  }

  int irValue1 = digitalRead(IR_SENSOR_1_PIN);
  int irValue2 = digitalRead(IR_SENSOR_2_PIN);
  int irValue3 = digitalRead(IR_SENSOR_3_PIN);

  digitalWrite(LED_IR_SENSOR_1_PIN, irValue1 == LOW ? HIGH : LOW);
  digitalWrite(LED_IR_SENSOR_2_PIN, irValue2 == LOW ? HIGH : LOW);
  digitalWrite(LED_IR_SENSOR_3_PIN, irValue3 == LOW ? HIGH : LOW);

  int gasValue = analogRead(GAS_SENSOR_PIN);
  if (gasValue > GAS_THRESHOLD) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(100);
      digitalWrite(BUZZER_PIN, LOW);
      delay(100);
    }
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  Serial.print("LDR Value: ");
  Serial.print(ldrValue);
  Serial.print(", Gas Value: ");
  Serial.println(gasValue);
  Serial.println(distance);

  delay(500);
}
