#include <Wire.h>
#include <Zumo32U4.h>

#define BAUD_RATE 9600
#define SPEED 100

Zumo32U4Motors Motors; // https://pololu.github.io/zumo-32u4-arduino-library/class_zumo32_u4_motors.html
Zumo32U4Encoders Encoders; // Documentation: https://pololu.github.io/zumo-32u4-arduino-library/class_zumo32_u4_encoders.html

// You would think to call Encoders.init(), as you want to 'start it', but what is said in the documentation;
// "This function is called automatically whenever you call any other function in this class, so you should not normally need to call it in your code."
void setup() {
  Serial.begin(BAUD_RATE);
}

// Prints out the encoder values to the serial monitor.
// I wanted to use getCountsAndResetRight/getCountsAndResetLeft, however the functionality is nigh identical except it 'clears' the counts.
// The max Encoder count is 32767, this is why getCountsAndResetRight/getCountsAndResetLeft is recommended.
void PrintEncoders() {
  Serial.println(Encoders.getCountsLeft());
  Serial.println(Encoders.getCountsRight());
}

// Does a sequence of instructions that the Zumo32U4 has to do.
// I use setSpeeds, as it's identical to combining setLeftSpeed/setRightSpeed.
void loop() {
  PrintEncoders();
  Motors.setSpeeds(SPEED, SPEED); // Goes forward.
  delay(1000); // Waits one second.
  Motors.setSpeeds(0, 0); // Stops.
  delay(1000); // Waits one second.
  Motors.setSpeeds(-SPEED, -SPEED); // Goes Backwards.
  delay(1000); // Waits one second.
}
