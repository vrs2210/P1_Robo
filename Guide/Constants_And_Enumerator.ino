 // Using const will make the variable read only, therefore making it immutable.
const int FIRST_PIN = 3;
const int SECOND_PIN = 5;

enum Direction {FORWARD, BACKWARD, LEFT, RIGHT} // An enum is a user-defined data type that's just named constants.

Direction Facing = FORWARD;

// Runs when the board is turned on.
void setup() {
  // Recommended to initialize variables and pins in here.
  // We would assign FIRST_PIN and SECOND_PIN in here.
}

// Loops the code inside consecutively. 
void loop() {
  // Recommended to run the actual board instructions in here, like button presses or readings.
  // We would change the Facing variable to another based on the board's facing direction using the Direction Enum.
}
