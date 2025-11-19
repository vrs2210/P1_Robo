#include <Servo.h>
#include <NewPing.h>

#define MAX_ANGLE 90.0
#define MIN_ANGLE -90.0
#define SPEED 0.05
#define PERIOD 1000000 / SPEED
#define SERVO_PIN 6
#define BAUD_RATE 115200 // Usually I'd use 9600, but I don't want to.
#define INITIAL_ANGLE 90
#define TRIG_PIN 3
#define ECHO_PIN 5
#define MAX_DISTANCE_IN_CM 400

NewPing Sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE_IN_CM);
Servo Rotater;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(BAUD_RATE);
  Rotater.attach(SERVO_PIN);
  Rotater.write(INITIAL_ANGLE);
}

// Maps Value from range [Min1, Max1] to [Min2, Max2]
float MapToRange(float Value, float Min1, float Max1, float Min2, float Max2) {
  return (Value - Min1) * (Max2 - Min2) / (Max1 - Min1) + Min2;
}

// Calculates the spanning angle using a triangle wave function to achieve a linear rotation.
// Using sine would have the highest speed near the middle and slow down near the edges.
float CalculateSpanningAngle() {
  float PeriodInMicroseconds = 1000000.0f / SPEED;                              // period in milliseconds, SPEED = cycles/sec
  float Rising = fmod(micros(), PeriodInMicroseconds) / PeriodInMicroseconds;  // 0..1 over one period
  float Triangle = (Rising < 0.5) ? Rising * 2.0 : (1.0 - Rising) * 2.0;
  return MapToRange(Triangle, 0.0f, 1.0f, MIN_ANGLE, MAX_ANGLE);
}

// Runs every 'tick'
// Distance is acalcualted by using the NewPing library and converting the microseconds into centimeters, from there it writes to the Serial Monitor.
void loop() {
  Rotater.write(90.0 + CalculateSpanningAngle());

  int Distance = Sonar.ping_cm();
  if (Distance == NO_ECHO) {
    return;
  }

  Serial.print("Distance ");
  Serial.print(Distance);
  Serial.println("cm");
}
